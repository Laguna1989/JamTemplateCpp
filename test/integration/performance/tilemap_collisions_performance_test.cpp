#include <tilemap/tilemap_cache.hpp>
#include <tilemap/tilemap_collisions.hpp>
#include <tilemap/tileson_loader.hpp>
#include <benchmark/benchmark.h>

namespace {
jt::TilemapCache cache;
}

static void BM_RefineTilemapCollisions(benchmark::State& state)
{
    jt::tilemap::TilesonLoader loader { cache, "assets/performance/test_level.json" };
    auto const collisions = loader.loadCollisionsFromLayer("ground1");
    for (auto _ : state) {
        auto newCollisions = collisions;
        newCollisions.refineColliders(16.0f);
    }
}

BENCHMARK(BM_RefineTilemapCollisions)->Unit(benchmark::kMillisecond);
