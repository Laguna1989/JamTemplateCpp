# JamTemplateCppSFML

## Setup
 1. go to ext folder and extract zip (more will come for other versions/IDEs)
 2. create build directory build parallel to src
 3. open command line (win+r "cmd")
 4. navigate to the just created build folder
 5. type "cmake ../"
 5.1 For x86, use "cmake -A Win32 ../"
 
For mac os you have to install cmake and sfml via homebrew: `brew install cmake sfml`
If you use another package manager or want to install the dependencies yourself, you have to modify the paths in `CMakeLists.txt`.
