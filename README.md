# Mila [![Build Status](https://travis-ci.org/ltowarek/Mila.svg?branch=master)](https://travis-ci.org/ltowarek/Mila)
Mila is a OpenCL benchmark tool

## Projects
Currently Mila has 3 projects which produce stable results:

1. [BBP](bbp)
1. [Mean shift](mean_shift)
1. [N-body](n_body)

## Dependencies
Mila needs the following dependencies to work correctly:

1. OpenCL device with the latest driver installed;
1. CMake 3.4+;
1. The remaining dependencies will be downloaded during `git clone --recursive` step.

## Build
To successfully build all Mila projects run the following commands:

### Linux
    git clone --recursive https://github.com/ltowarek/Mila
    cd Mila
    mkdir build
    cd build
    cmake ..
    make
    ctest (optional)

### Windows
    git clone --recursive https://github.com/ltowarek/Mila
    cd Mila
    mkdir build
    cd build
    cmake .. -G "Visual Studio 14 Win64"
    Open Mila.sln in Visual Studio 14 and build all projects
    ctest (optional)

Note: If you are seeing linker errors during compilation then please change the runtime library in GTest projects to match
this in Mila projects.

## Issues and feature requests
Feel free to report all bugs and feature requests in [YouTrack](http://mila.myjetbrains.com/youtrack/issues)
