# Performance Findings

Investigation date: 2026-08-29. Baseline commit: `ecbec1e1`.

This document records a performance investigation of the JamTemplate library. Findings are
grouped by expected impact. Items marked **measured** were verified with the benchmark suite;
all others are reasoned from the code and are explicitly *not* benchmarked.

## Contents

- [Measurement setup](#measurement-setup)
- [Tier 1 - large, measured or structural](#tier-1---large-measured-or-structural)
- [Tier 2 - significant in specific workloads](#tier-2---significant-in-specific-workloads)
- [Tier 3 - cheap fixes, small individual wins](#tier-3---cheap-fixes-small-individual-wins)
- [Build configuration risks](#build-configuration-risks)
- [Suggested order](#suggested-order)
- [What was not measured](#what-was-not-measured)

## Measurement setup

Release build, Tracy and debug logging disabled:

```
cmake -S . -B build-rel -G Ninja \
  -DCMAKE_BUILD_TYPE=Release \
  -DJT_ENABLE_PERFORMANCETESTS=ON \
  -DJT_ENABLE_UNITTESTS=OFF \
  -DJT_ENABLE_DEMOS=OFF \
  -DJT_ENABLE_TRACY=OFF \
  -DJT_ENABLE_DEBUG=OFF \
  -DBENCHMARK_ENABLE_GTEST_TESTS=OFF \
  -DBENCHMARK_ENABLE_TESTING=OFF
cmake --build build-rel --parallel --target jt_performance
cd build-rel/test/integration/performance && ./jt_performance --benchmark_min_time=1
```

Baseline (24-core machine, CPU scaling enabled, so numbers are noisy in absolute terms but
usable for before/after comparison):

| Benchmark | Time |
| --- | --- |
| `BM_UpdateDrawablePositions` | 2.22 ms |
| `BM_GamestateWithTweeningShapes` | 3.08 ms |
| `BM_UpdateSpatialObjectGrid` | 0.319 ms |
| `BM_GetAllCommands` | 0.337 ms |
| `BM_UpdateObjectGroup` | 0.072 ms |
| `BM_RefineTilemapCollisions` | 0.094 ms |
| `BM_StartGame` | 0.003 ms |

### Blocker: the performance target does not configure on CMake 4.x

`test/integration/performance/CMakeLists.txt:4` pins `googlebenchmark` to `v1.6.0`, which fetches
a `googletest` whose `cmake_minimum_required` is below 3.5. CMake 4 removed that compatibility, so
configuration fails with:

```
CMake Error at CMakeLists.txt:1 (cmake_minimum_required):
  Compatibility with CMake < 3.5 has been removed from CMake.
```

Workaround used above: `-DBENCHMARK_ENABLE_GTEST_TESTS=OFF -DBENCHMARK_ENABLE_TESTING=OFF`.
Proper fix: bump the `GIT_TAG`. As it stands, `JT_ENABLE_PERFORMANCETESTS=ON` is broken for
anyone on a current CMake.

## Tier 1 - large, measured or structural

### 1. `Animation::doUpdate` updates every sprite of every animation, every frame (measured: 3.4x)

`impl/jamtemplate/common/animation.cpp:366`

```cpp
// update all sprites
for (auto& kvp : m_frames) {
    for (auto& sprite : kvp.second) {
        sprite->update(elapsed);
    }
}
```

Only `m_frames[m_currentAnimName][m_currentIdx]` is ever drawn. Replacing this loop with a single
`currentSprite->update(elapsed)` and rebuilding gives:

**`BM_UpdateDrawablePositions`: 2.22 ms -> 0.654 ms (3.4x)**

That benchmark uses only *one* animation of 12 frames. A typical entity with idle/walk/attack/hurt
updates 40-60 sprites per frame instead of 1, so the real-world win is larger.

The same function performs five `std::map<std::string, ...>` lookups per update
(`m_frames.at(m_currentAnimName)`, `m_time[m_currentAnimName]`) and `doDraw` performs two more.
Cache an iterator or pointer to the current frame vector, invalidated in `play()`.

> **Caveat.** Shake and flash timers currently tick on all sprites. The correct fix is to keep that
> state on the `Animation` itself (it already inherits the `ShakeImpl` / `FlashImpl` mixins) and
> push it to the current sprite only - not simply to delete the loop as was done for the
> measurement above.

### 2. SDL: render-target switch per drawable defeats SDL2 batching

`impl/jamtemplate/sdl/render_target_lib.cpp:14`

```cpp
std::shared_ptr<jt::RenderTargetLayer> jt::RenderTarget::get(int z)
{
    SDL_SetRenderTarget(m_renderer.get(), m_textures[z].get());
    return m_renderer;
}
```

`DrawableImpl::draw` calls this once per drawable per frame. Objects are drawn in insertion order,
not z order, so with 3 layers and 500 sprites you issue up to 500 `SDL_SetRenderTarget` calls.
SDL2's render batching flushes on every target change, producing ~500 draw batches instead of ~3.

Additionally `m_textures[z]` uses `std::map::operator[]`, which is a tree lookup that silently
inserts a null texture for an unknown `z`.

**Fix:** bucket drawables by z and draw layer by layer, or - cheaper - cache the currently bound z
and skip the SDL call when it is unchanged. Use `find` instead of `operator[]`.

### 3. SDL: `SDL_RenderPresent` is called once per z-layer

`impl/jamtemplate/sdl/gfx_impl.cpp:49-58`

```cpp
for (auto& kvp : m_target->m_textures) {
    SDL_RenderCopyEx(...);
    m_window.display();
    SDL_RenderPresent(m_target->m_renderer.get());
}
```

With N layers this performs N buffer swaps per frame. The renderer is not created with
`SDL_RENDERER_PRESENTVSYNC`, so this does not divide the frame rate, but each present is a GPU
sync point.

**Fix:** move `m_window.display()` and `SDL_RenderPresent` out of the loop.

### 4. `TileLayer::doDraw` is expensive per tile and scans all tiles

`impl/jamtemplate/common/tilemap/tile_layer.cpp:63-80`

- `isTileVisible` is evaluated by walking **every** tile, so a 200x200 map costs 40 000 iterations
  per layer per frame in order to draw ~300 tiles. Precompute row/column ranges from the camera
  rect, or index tiles by cell.
- Per visible tile: six bounds-checked `m_tileSetSprites.at(id)` calls (hoist to a reference), a
  `setScale` that re-runs `setOriginInternal`, and a full `update(0.0f)` through the
  flash/shake/flicker mixins. Scale and blend mode only need setting when they change.

## Tier 2 - significant in specific workloads

### 5. Pathfinder is O(V^2) with a heap allocation per pop

`impl/jamtemplate/common/pathfinder/pathfinder.cpp:21-51`

`findClosestNodeTo` linear-scans the open list, then **rebuilds the entire vector** to remove a
single element, calling `.lock()` on every node a second time. Nodes are also pushed without
deduplication, so the list grows past V.

**Fix:** a `std::priority_queue` - and a real A* heuristic, since the distance-to-goal is already
being computed - turns this into O(E log V). For any grid larger than roughly 50x50 this is the
difference between a visible hitch and a non-event.

### 6. `SpatialObjectGrid` allocates heavily and grows without bound

`impl/jamtemplate/common/spatial_object_grid.hpp`

- `getObjectsAround` allocates the offsets vector per query and does `contains()` followed by
  `at()` - two `std::map` lookups per cell. Use an `unordered_map` with a hashed `CellIndex` and a
  single `find`.
- `doUpdate` allocates two vectors per cell, plus - inside `remove_intersection`
  (`impl/jamtemplate/common/system_helper.hpp:47`) - an `unordered_set` **and** an
  `unordered_multiset`, per cell, per frame.
- `m_allObjects` (line 105) is only ever read by `empty()`, is never pruned, and `push_back` is
  called again for every object that changes cell. It grows without bound for the lifetime of the
  grid.

### 7. Fonts are loaded once per `Text` object

`impl/jamtemplate/common/drawable_helpers.cpp:29`

`dh::createText` calls `loadFont` every time. On SFML that is `sf::Font::loadFromFile` (disk I/O,
parse, and a private glyph atlas per instance); on SDL a `TTF_OpenFont`. A HUD with 30 labels loads
the same TTF 30 times and keeps 30 atlases.

**Fix:** a font cache keyed on `(path, size)`. Wins in both load time and memory.

### 8. SDL `Text::setText` has no early-out and measures by rasterizing

`impl/jamtemplate/sdl/text.cpp:31`

`setText` unconditionally calls `recreateTextTexture`, which allocates a render-target texture and
rasterizes every line. `getSizeForLine` (`impl/jamtemplate/sdl/text.cpp:180`) creates a full surface
**and** texture just to read back width and height - `TTF_SizeText` does this without touching the
GPU.

The common pattern `setText(std::to_string(score))` every frame therefore pays the whole cost every
frame.

**Fix:** add `if (m_text == text) { return; }`, and use `TTF_SizeText` for measurement.

### 9. SFML: a `jt::Sprite` is heap-allocated per z-layer per frame

`impl/jamtemplate/sfml/gfx_impl.cpp:75` - `std::make_unique<jt::Sprite>()` inside `drawOneZLayer`,
which runs once per layer per frame in the presentation path.

**Fix:** make it a cached member.

### 10. The web build never gets the optimization the native build gets

- `CMakeLists.txt:48` hardcodes `-O2` for `JT_ENABLE_WEB`, appended *after* the `-O3` that
  `CMAKE_BUILD_TYPE=Release` supplies, so `-O2` wins.
- `.github/workflows/deploy.yml:128` builds the web target **without**
  `JT_ENABLE_LTO_OPTIMIZATION`.

The wasm target runs on the weakest hardware and is the least optimized of all shipped targets.

**Worth trying:** `-O3` plus `-flto` plus `--closure 1`, and dropping `ALLOW_MEMORY_GROWTH=1` given
that 256 MB is already reserved (growth adds a per-access cost in some emscripten configurations).

## Tier 3 - cheap fixes, small individual wins

These are individually small. Treat them as a single cleanup sweep, not as a performance project -
none of them will move a benchmark noticeably on its own.

| Finding | Location |
| --- | --- |
| `std::erase_if(m_objects, [](auto go){...})` copies a `shared_ptr` per object per frame | `impl/jamtemplate/common/game_object_collection.cpp:34` |
| `std::erase_if(m_data, [](std::weak_ptr<T> wptr){...})` - same, on the weak count | `impl/jamtemplate/common/object_group.hpp:48` |
| `CircleTest(std::shared_ptr, std::shared_ptr)` takes both by value, and `getSize`/`getCenter` copy again - roughly 6 atomic refcount operations per collision test, inside an N^2 loop. `getSize` also calls `getGlobalBounds()` twice | `impl/jamtemplate/common/collision.hpp:76` |
| `doGetOutlineOffsets()` returns `std::vector<Vector2f>` **by value** on every outline draw (34 elements at width 2) - return `const&` | `impl/jamtemplate/common/graphics/outline_impl.cpp:35` |
| `DrawableImpl::draw` and every `doDraw` / `doDrawShadow` / `doDrawOutline` / `doDrawFlash` take `shared_ptr` by value - should be `const&` throughout | `impl/jamtemplate/common/graphics/drawable_impl.hpp`, all backends |
| `forall([this](auto t){ ... })` copies a `shared_ptr` per layer | `impl/jamtemplate/sfml/gfx_impl.cpp:52` |
| `Clouds::drawLayer(shared_ptr, shared_ptr)` by value, called 3x per frame | `impl/jamtemplate/common/screeneffects/clouds.cpp:59` |
| Keyboard: `getAllKeys()` **allocates a vector** and is called twice per frame in `updateCommands`; state lives in 8 separate `std::map<KeyCode, bool>`. Measured **10.1 us/frame idle** on this desktop - small here, but wasm indirect calls and tree walks cost several times more. A `std::array` indexed by key code removes it entirely | `impl/jamtemplate/common/input/keyboard/keyboard_input.cpp:90,108` |
| `m_logger.verbose("...", {"jt"})` constructs a `std::vector<std::string>` temporary at the call site every frame even though the body is `#ifdef`-ed out - the argument is still built. Guard with a macro or an inline level check | `impl/jamtemplate/common/game_base.cpp:26,101,120` |
| `InfoScreen::doUpdate` copies 2 x 256 floats per frame even when the overlay is hidden | `impl/jamtemplate/common/log/info_screen.cpp:22-32` |

## Build configuration risks

These are hazards rather than performance wins, but they live in the same code.

`CMakeLists.txt:36`:

```cmake
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -flto=auto -fwhole-program -g0 -march=native -mtune=native")
```

- **`-march=native` in a release path is dangerous.** `.github/workflows/deploy.yml:26` builds the
  shipped Windows and Linux binaries with `JT_ENABLE_LTO_OPTIMIZATION=ON` on a GitHub runner. The
  binary is tuned to whatever CPU that runner happened to have and will `SIGILL` on any user CPU
  lacking those instructions. Use an explicit baseline such as `-march=x86-64-v2`.
- **`-fwhole-program` alongside `-flto` across a multi-TU static library is not what that flag is
  for** and can produce wrong code. `-flto` alone is the correct choice here.

## Suggested order

1. **Animation update** (#1) - measured 3.4x, self-contained, biggest single win.
2. **SDL z-layer batching and single present** (#2, #3) - structural, affects every SDL and web frame.
3. **Tilemap draw path** (#4) - decides whether large maps are viable.
4. **Fix `-march=native`** - not a speedup, but a shipping-crash risk.
5. **Pathfinder priority queue** (#5) - large, but only if games actually use it.
6. **Tier 3 as a single sweep** - individually small, collectively a few percent, and nearly all are
   mechanical `const&` changes.

Two counterpoints worth keeping in mind:

- The Tier 3 `shared_ptr`-by-value sweep is tempting because it is easy, but it will not move any
  benchmark noticeably on its own. Do it as cleanup, not as a performance project.
- Resist LTO and `-O3` tuning until #1-#3 are done. Algorithmic factors of 3-10x are sitting there,
  and compiler flags will not find them.

## What was not measured

Findings #2, #3, #4, #5 and #10 are reasoned from the code, not benchmarked, because the existing
suite has no coverage for the render path, tilemaps, or pathfinding. Adding benchmarks for those
three areas would be a prerequisite to tracking regressions in them.

Findings #1 (3.4x on `BM_UpdateDrawablePositions`) and the keyboard entry in Tier 3
(10.1 us/frame idle) were measured directly.
