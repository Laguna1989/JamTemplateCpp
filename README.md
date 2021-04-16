# JamTemplateCppSFML
[![Build Status](https://travis-ci.com/Laguna1989/JamTemplateCpp.svg?branch=master)](https://travis-ci.com/github/Laguna1989/JamTemplateCpp)

## About
This is my JamTemplate for C++17. It will compile C++ code for native (Win, Linux) and web (webassembly) games .

Some games created with this JamTemplate are
 * [Burning Glyphs](https://runvs.io/Games/burningglyphs) (Web, 7DFPS 2020)
 * [Tricky Tracktor](https://runvs.io/Games/trickytractor) (Native, FrankenGameJam 2021)
 * [Grounded](https://runvs.io/Games/grounded) (Native, FrankenGameJam 2020)

and some more at https://runvs.io/Games.

## Setup
### Windows
 1. go to ext folder and extract sfml-zip
 2. create build directory "build" parallel to src
 3. open command line (win+r "cmd")
 4. navigate to the just created build folder
 5. type `cmake ../`

### Windows 32 bit
There should be no need for a 32 bit executable anymore. However if strictly required: 
Perform the steps from above except:
 * 1) Get the win32 zip from the [sfml website](https://www.sfml-dev.org/)
 * 5) `cmake -A Win32 ../`

### Web
I run it with WSL, but every system capable of running wegassembly/emscripten should work.
 1.  `emcmake cmake -DENABLE_WEB=ON ../`
 2. on the first run `emmake make` (do **not** pass `-j`, otherwise emscripten will get hickups with pulling libraries)
 3. on consecutive runs: `emmake make -j`
 3. `http-server .` to start a webserver locally. 
 4. open browser on `http://127.0.0.1:8080/` to test locally

### Mac
For mac os you have to install cmake and sfml via homebrew: `brew install cmake sfml`
If you use another package manager or want to install the dependencies yourself, you have to modify the paths in `CMakeLists.txt`.

## Cmake options
All of those options can be set to ON or OFF via the cmake commandline
 * ENABLE_UNITTESTS
 * ENABLE_STRESSTEST
 * ENABLE_WEB

e.g. calling `cmake ../ -DENABLE_UNITTESTS=ON -DENABLE_STRESSTEST=ON`

## Code Coverage report
Code coverage helper command for future references:
```
OpenCppCoverage.exe --sources C:\projects\JamTemplateCpp\* --excluded_sources C:\projects\JamTemplateCpp\src\UnitTests\* --excluded_sources C:\projects\JamTemplateCpp\src\StressTest\* --excluded_sources C:\projects\JamTemplateCpp\ext\*  -- build\Debug\UnitTests.exe
```