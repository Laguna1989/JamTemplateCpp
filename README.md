# JamTemplateCpp

[![Build Status](https://github.com/Laguna1989/JamTemplateCpp/actions/workflows/test_verification.yml/badge.svg)](https://github.com/Laguna1989/JamTemplateCpp/actions/workflows/unittests.yml)
[![codecov](https://codecov.io/github/Laguna1989/JamTemplateCpp/branch/master/graph/badge.svg?token=9XBS3E6UWC)](https://codecov.io/github/Laguna1989/JamTemplateCpp)

## About

This is the JamTemplate for kickstarting your gamejam entry. It will compile C++17 code for native (Win, Linux) and
web (webassembly) games. Internally it uses [SFML](https://www.sfml-dev.org/) and [SDL](https://www.libsdl.org/).

Some games created with this JamTemplate are

* [Funky Trip](https://runvs.io/Games/funkytrip) (Native & Web, Alakajam 14 2022)
* [Gemga](https://runvs.io/Games/gemga) (Native & Web, FrankenGameJam 2021)
* [Quasar Rush](https://runvs.io/Games/quasarrush) (Native & Web, A Game By Its Cover 2021)
* [Space Turtles](https://runvs.io/Games/spaceturtles) (Native, MultiplayerKajam 2021)
* [Tricky Tractor](https://runvs.io/Games/trickytractor) (Native, FrankenGameJam 2020)
* [Burning Glyphs](https://runvs.io/Games/burningglyphs) (Web, 7DFPS 2020)
* [Grounded](https://runvs.io/Games/grounded) (Native, FrankenGameJam 2019)

and some more at [my game portfolio](https://runvs.io/Games).

## Setup

### Windows & Visual studio (code)

1. create build directory `build` at root level
2. open command line (win+r `cmd`)
3. navigate to the just created build folder
4. type `cmake ../`

### Clion

1. open project folder in clion

Hint: There is a file template available in the `.idea` folder that will make take away some of the boilerplate code
during creation of Gameobject classes.

### Windows 32 bit

There should be no need for a 32 bit executable anymore. However, if strictly required, perform the steps from above
except:

1. Get the win32 zip from the [sfml website](https://www.sfml-dev.org/)
2. `cmake -A Win32 ../`

### Web

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
adjust the deployment script or place them in the assets folder.

## Cmake options

All of those options can be set to ON or OFF via the cmake commandline

* `JT_ENABLE_UNITTESTS` - Enables gtest and the unit tests
* `JT_ENABLE_DEMOS` - Enables the demos (small example programs which showcase a specific theme)
* `JT_ENABLE_WEB` - Webbuild
* `USE_SFML` - If `ON`, SFML will be used, if `OFF`, SDL will be used (SDL works best on linux)
* `JT_ENABLE_AUDIO_TESTS` - Some of the tests rely on a working audio setup, which seemingly cannot be faked easily.
  This switch disables those specific tests, in case no audio is available on the respective machine.
* `JT_ENABLE_CLANG_TIDY` - Enable clang tidy checker

e.g. calling `cmake ../ -DJT_ENABLE_UNITTESTS=ON -DENABLE_DEMOS=ON`

## Code Coverage

Code Coverage is reported via [CodeCov](https://app.codecov.io/gh/Laguna1989/JamTemplateCpp/)

A local run (without the artifacts) can be executed on Windows
via [OpenCppCoverage](https://github.com/OpenCppCoverage/OpenCppCoverage):

```
OpenCppCoverage.exe --sources C:\projects\JamTemplateCpp\* --excluded_sources C:\projects\JamTemplateCpp\test\* --excluded_sources C:\projects\JamTemplateCpp\ext\* --excluded_sources C:\projects\JamTemplateCpp\cmake-build-debug\* .\cmake-build-debug\test\unit\jt_test\jt_tests.exe
```

## Performance benchmark

Please check the performance benchmark [report](https://laguna1989.github.io/JamTemplateCpp/dev/bench/index.html).

## gamejam setup recommended steps

* Use this repo as a template
* Clone the new repository
* remove the folders
    * `test`
    * `assets/test`
    * `.github/workflows/` everything except `deploy.yml`
* Changes in `CMakeLists.txt`:
    * Set the project name
    * Remove or comment the line `add_subdirectory(test)`
* Change js filename in `index.html`
* Set most cmake variables to `OFF` in `config/cmake/cache_variables.cmake`
* Import a new palette into `impl/gamelib/game_properties.cpp`, e.g. from [this website](https://lospec.com/palette-list) (
  save as gpl and paste file content)
* Change `impl/gamelib/game_properties.hpp` settings as needed (window size, jam, author and date)
