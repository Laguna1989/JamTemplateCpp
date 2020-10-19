# JamTemplateCppSFML

## Setup
 1. go to ext folder and extract sfml-zip
 2. create build directory "build" parallel to src
 3. open command line (win+r "cmd")
 4. navigate to the just created build folder
 5. type "cmake ../"
 6. For x86, use the win32 zip from the sfml website and use "cmake -A Win32 ../"
 
For mac os you have to install cmake and sfml via homebrew: `brew install cmake sfml`
If you use another package manager or want to install the dependencies yourself, you have to modify the paths in `CMakeLists.txt`.
