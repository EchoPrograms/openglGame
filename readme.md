# Building 
### Build Requirements
 - CMake
 - make
 - C and C++ compiler
 - OpenGL libraries

### Build Instructions
  1. Create a `build` directory (must be named exactly `build`)
  2. Run `cmake ..` from the `build` dir
  3. Run `make` from the `build` dir

### Linux Scripts
The `linuxScripts` directory contains helper scripts for the project. They 
are all meant to be run from the `linuxScripts directory,` and will return 
there after execution.
- `linuxBuild.sh`:
  - Navigates to the `build` dir, runs `make`, then executes the program
- `updateShaders.sh`: 
  - Copies the `res` directory to the `build/bin` directory.
  - Navigates to the `build` dir, runs `make`, then executes the program
  - **if no c/cpp code has been changed, shaders will not update when running linux build**

# Running
After building, navigate to `build/bin`, and run the `opengl` executable.
Execution must be relative to the `res` directory which is copied to `build/bin`
during the build process.

Execution has only been tested on Linux, but is theoretically supported on 
Windows and MacOS.

Execution through WSL on windows has also been tested.

