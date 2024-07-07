# JamTemplateCpp

[![Build Status](https://github.com/Laguna1989/JamTemplateCpp/actions/workflows/test_verification.yml/badge.svg)](https://github.com/Laguna1989/JamTemplateCpp/actions/workflows/unittests.yml)
[![codecov](https://codecov.io/github/Laguna1989/JamTemplateCpp/branch/master/graph/badge.svg?token=9XBS3E6UWC)](https://codecov.io/github/Laguna1989/JamTemplateCpp)

## About

This is the JamTemplate for kickstarting your gamejam entry. It will compile C++20 code for native (Win, Linux) and
web (webassembly) games. Internally it uses [SFML](https://www.sfml-dev.org/), [SDL](https://www.libsdl.org/) and
[OpenALpp](https://github.com/Laguna1989/OpenALpp).

Some games created with this JamTemplate are

* [Fruit Lovin Monkey Pirates](https://runvs.io/Games/fruitlovinmonkeypirates) (Action Sailing Game, Native & Web,
  FrankenGameJam 2023)
* [Medibellum](https://runvs.io/Games/medibellum) (Multiplayer Autobattler Game, Native, Kajam-13 2023)
* [Mines of Gloria](https://runvs.io/Games/minesofgloria) (Incremental Clicker Game, Native & Web, ClickerJam Spring
  2023)
* [Tworld](https://runvs.io/Games/tworld) (Jump and Run, Native & Web, FrankenGameJam 2022)
* [Funky Trip](https://runvs.io/Games/funkytrip) (Top Down ARPG, Native & Web, Alakajam 14 2022)
* [Gemga](https://runvs.io/Games/gemga) (Puzzler, Native & Web, FrankenGameJam 2021)
* [Quasar Rush](https://runvs.io/Games/quasarrush) (Physics based puzzle game, Native & Web, A Game By Its Cover 2021)
* [Space Turtles](https://runvs.io/Games/spaceturtles) (Multiplayer SHMUP, Native, MultiplayerKajam 2021)
* [Tricky Tractor](https://runvs.io/Games/trickytractor) (Puzzler, Native, FrankenGameJam 2020)
* [Burning Glyphs](https://runvs.io/Games/burningglyphs) (FPS, Web, 7DFPS 2020)
* [Grounded](https://runvs.io/Games/grounded) (2 Player Couch Battle, Native, FrankenGameJam 2019)

and more at [my game portfolio](https://runvs.io/Games).

## Setup

### Visual Studio

1. create build directory `build` at root level
2. open command line (win+r `cmd`)
3. navigate to the just created build folder
4. type `cmake ../`
5. Open generated solution file with Visual Studio

### Clion (Win, Linux)

1. open project folder in clion

### Building for Web

I run it with [WSL2](https://docs.microsoft.com/de-de/windows/wsl/compare-versions), but every system capable of
running [webassembly](https://webassembly.org/) / [emscripten](https://emscripten.org/) should work.

Preconditions:

* have emscripten set up on your machine: See
  the [Getting started](https://emscripten.org/docs/getting_started/index.html) page

Setup

1. `emcmake cmake -DJT_ENABLE_WEB=ON ../`
2. on the first run `emmake make` (do **not** pass `-j`, otherwise emscripten will get stuck with pulling libraries)
3. on consecutive runs: `emmake make -j`
3. `http-server .` to start a webserver locally. (needs to be installed separately)
4. open browser on `http://127.0.0.1:8080/` to test locally

### Mac

For mac os you have to install cmake and sfml via homebrew: `brew install cmake sfml`
If you use another package manager or want to install the dependencies yourself, you have to modify the paths
in `CMakeLists.txt`.

## Deployment

Automatic creation of the files is automated via github actions. If a release is created with semantic versioning (
e.g. `v1.2.3`), a deployment build is triggered, which builds the game executable for windows, linux, mac and web and
attaches the zipped files to the release once the build is finished. The archives can directly be uploaded
on [itch](itch.io), [gamejolt](https://gamejolt.com/) or any other website.

Note: Only the game executable and the `assets` folder is included in the archive. If more files are required, either
adjust the deployment script (`.github/workflows/deploy.yml`) or place them in the `assets` folder.

## CMake options

The options can be set to ON or OFF via the cmake commandline or cmake-gui:

* `JT_ENABLE_UNITTESTS` - Enables gtest and the unit tests
* `JT_ENABLE_PERFORMANCETESTS` Enables the performance tests
* `JT_ENABLE_DEMOS` - Enables the demos (small example programs which showcase a specific theme)
* `JT_ENABLE_WEB` - Webbuild
* `USE_SFML` - If `ON`, SFML will be used, if `OFF`, SDL will be used (SDL works best on linux)
* `JT_ENABLE_AUDIO_TESTS` - Some of the tests rely on a working audio setup, which seemingly cannot be faked easily.
  This switch disables those specific tests, in case no audio is available on the respective machine.
* `JT_ENABLE_CLANG_TIDY` - Enable clang tidy checker
* `JT_ENABLE_LTO_OPTIMIZATION` - Enable Link time optimization. This gives higher runtime performance for the cost of
  increased build and link times.

e.g. calling `cmake ../ -DJT_ENABLE_UNITTESTS=ON -DENABLE_DEMOS=ON`

## Code Coverage

Code Coverage is reported via [CodeCov](https://app.codecov.io/gh/Laguna1989/JamTemplateCpp/)

A local run (without the artifacts) can be executed e.g. on Windows
via [OpenCppCoverage](https://github.com/OpenCppCoverage/OpenCppCoverage):

```
OpenCppCoverage.exe --sources C:\projects\JamTemplateCpp\* --excluded_sources C:\projects\JamTemplateCpp\test\* --excluded_sources C:\projects\JamTemplateCpp\ext\* --excluded_sources C:\projects\JamTemplateCpp\cmake-build-debug\* .\cmake-build-debug\test\unit\jt_test\jt_tests.exe
```

## Performance benchmark

Please check the performance benchmark [report](https://laguna1989.github.io/JamTemplateCpp/dev/bench/index.html).

## 1hgj setup (recommended steps)

* Use this repo as a template
* Clone the new repository
* Remove the folders
    * `test`
    * `assets/test`
    * `.github/workflows/` everything except `deploy.yml`
* Changes in `CMakeLists.txt`:
    * Set the project name
    * Remove or comment the line `add_subdirectory(test)`
* Change js filename in `index.html`
* Set most cmake variables to `OFF` in `config/cmake/cache_variables.cmake`
* Import a new palette into `impl/gamelib/game_properties.cpp`, e.g.
  from [this website](https://lospec.com/palette-list) (
  save as gpl and paste file content)
* Change `impl/gamelib/game_properties.hpp` settings as needed (window size, jam, author and date)

# Starting on Linux

FMod cannot be linked statically in the indie tier. Thus you need to provide the so while loading. Linux does not look
in the local path by default. To fix this, you can add the following variable when starting the exe

```
LD_LIBRARY_PATH=<path_to_build_dir>impl/game
```
