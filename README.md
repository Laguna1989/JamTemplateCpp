# JamTemplateCppSFML

[![Build Status](https://github.com/Laguna1989/JamTemplateCpp/actions/workflows/test_verification.yml/badge.svg)](https://github.com/Laguna1989/JamTemplateCpp/actions/workflows/unittests.yml) [![Coverage Status](https://coveralls.io/repos/github/Laguna1989/JamTemplateCpp/badge.svg)](https://coveralls.io/github/Laguna1989/JamTemplateCpp)

## About

This is the JamTemplate for kickstarting your gamejam entry. It will compile C++17 code for native (Win, Linux) and
web (webassembly) games. Internally it uses [SFML](https://www.sfml-dev.org/) and [SDL](https://www.libsdl.org/).

Some games created with this JamTemplate are

* [Gemga](https://runvs.io/Games/gemga) (Web & Native, FrankenGameJam 2021)
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

### Windows 32 bit

There should be no need for a 32 bit executable anymore. However, if strictly required, perform the steps from above
except:

1. Get the win32 zip from the [sfml website](https://www.sfml-dev.org/)
2. `cmake -A Win32 ../`

### Web

I run it with [WSL2](https://docs.microsoft.com/de-de/windows/wsl/compare-versions), but every system capable of
running [wegassembly](https://webassembly.org/) / [emscripten](https://emscripten.org/) should work.

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

However, as MacOS seems to be pretty picky with installed libraries and packaging an executable is a pain, it is highly
recommended using the Web build to show your game to your Mac friends.

## Cmake options

All of those options can be set to ON or OFF via the cmake commandline

* `JT_ENABLE_UNITTESTS` - Enables gtest and the unit tests
* `JT_ENABLE_DEMOS` - Enables the demos (small example programs which showcase a specific theme)
* `JT_ENABLE_WEB` - Webbuild
* `USE_SFML` - If `ON`, SFML will be used, if `OFF`, SDL will be used (SDL works best on linux)
* `JT_ENABLE_COVERAGE` - Compile with the flags set for the coverage run
* `JT_ENABLE_AUDIO_TESTS` - Some of the tests rely on a working audio setup, which seemingly cannot be faked easily.
  This switch disables those specific tests, in case no audio is available on the respective machine.
* `JT_ENABLE_CLANG_TIDY` - Enable clang tidy checker

e.g. calling `cmake ../ -DJT_ENABLE_UNITTESTS=ON -DENABLE_DEMOS=ON`

## Code Coverage

Code Coverage can is reported via [coveralls](https://coveralls.io/github/Laguna1989/JamTemplateCpp).

Unfortunately there seem to be some artifacts, which lead to a lower than actual coverage.

A local run (Without the artifacts) can be executed
via [OpenCppCoverage](https://github.com/OpenCppCoverage/OpenCppCoverage). The command :

```
OpenCppCoverage.exe --sources C:\projects\JamTemplateCpp\* --excluded_sources C:\projects\JamTemplateCpp\test\* --excluded_sources C:\projects\JamTemplateCpp\ext\* --excluded_sources C:\projects\JamTemplateCpp\cmake-build-debug\* .\cmake-build-debug\test\unit\jt_test\jt_tests.exe
```

## Performance benchmark

Please check the performance benchmark [report](https://laguna1989.github.io/JamTemplateCpp/dev/bench/index.html).
