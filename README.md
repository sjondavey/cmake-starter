
Non-trivial starter project making use of Modern CMake to create a cross platform (Windows 10 / Ubuntu 20) C++ library which tests (Catch2), exposed via a command line application and as a python module (Pybind11). 

The CMake layout is modelled after the excellent talk 'Oh No! More Modern CMake' by Deniz Bahadir at 'Meeting C++ 2019' which is found here: https://www.youtube.com/watch?v=y9kSr5enrSk. NOTE: I was not able to get all the relevant features in the talk to work so I have reverted to some non-modern CMake features. Hopefully I can fix these in time but this is all new to me and everything takes a long time to work though. I'm banking what I have! It feels to me like some of the issues may be because I am using vcpkg (2020.02.04-nohash on Windows)

The project structure is:
.
├── app/                                # Folder for all source files for the command line executable
│   ├── main.cpp                        # Main entry of the application
│   └── CMakeLists.txt                  # Compile script for command line application
├── bin/                                # Folder for built application binary
│   ├── cmake_starter_demo              # Built application executable (Windows adds debug / release directories)
│   └── cmake_starter_tests             # Built testing executable  
├── python/                             # Folder for the python bindings for the library
│   ├── PythonInterface.cpp             # pybind11 interface for formula - as formula and object
│   └── CMakeLists.txt                  # Compile script for python interface
├── src/                                # Folder for all source files for the main library
│   ├── formula/                        # Folder for pricing formula
│   │   ├── Black76Formula.h            # Header file for one pricing formula
│   │   └── Black76Formula.cpp          # implementation of pricing formula
│   └── CMakeLists.txt                  # Compile script for base library
├── test/                               # Test folder for all unit tests
│   ├── test_main.cpp                   # Definitions for Catch2 framework
│   ├── Black76FormulaTest.cpp          # Tests for the pricing formula
│   └── CMakeLists.txt                  # Compile script for unit tests
└── CMakeLists.txt                      # Main compile script

This project was me starting over (> 8 years of not writing C++ code). I am not a developer and, even historically, worried more about the algorithms
than building 'good' projects. I am older now and understand that good projects are important. I started this to try to build a good project. It is 
a work in progress. This was much more detailed and time consuming than I expected. 

There are lots of compromises here. Places where I could not get a good solution working in a reasonable amount of time. Hopefully I (or you!) will return 
and fix these in time. I really do want to get to coding (algorithms) now. 

Here are my chosen tools - and why (it is really important to understand the why before choosing tools)
Language: C++
Why: I listened to Lex Fridman's podcast where he interviewed Bjarne Stroustrup. I wanted to be a better man than I currently am! It's not a good answer to why but it is the only one I have. I could have just done this in Python but I'm trying to convince myself that I will require execution speed. 

Environnement: Visual Studio Code
Why: Previously I built Excel Add-Ins (trying to emulate quantlib.org - those guys are smart). It was all for Windows and Visual Studio was the only real option. This time I wanted something to write something for multiple platforms (ultimately docker) so I wanted one tool that I could use in Windows and Ubuntu while I was worming up. VSCode took some time to get into (setting.json and launch.json all assume you know what you are doing - I did not). In the end, I'm really happy with VSCode. The experience in Windows and Ubuntu is identical (for me and at this stage - I'm touching wood that it continues). I use the C++ and CMake extensions. 

Package Management: vcpkg
Why: Historically I didn't use a tool, just did things manually. Because I was working now cross platform, that approach would not be sufficient. To be honest vcpkg was the first thing I tried. It just works (although I have an uncomfortable feeling that there are surprises waiting for me in the weeds!). For now, I'm only using it because it feels like the path of least resistance. If I have issues later, I may have to think about this. That is a problem for a future day.

Build Utility: CMake
Why: I genuinely don't know what I'm doing here. It's been a very steep learning curve. I'm surprised C++ developers are not a more grumpy lot! My difficulties with CMake are the reason for this project. Despite this, I could not find an alternative.

Testing: Catch2
Why: I started using the boost testing framework. I had previous experience with it. I found however that I was just spending too much time trying to get link and build simultaneously from Windows and Ubuntu. Out of frustration I tried Catch2. Because it is header only, it just works. As my code volume increases I may have to spend more time tinkering but as a cross platform tool, it seems excellent. 

Python Interface: Pybind11
Why: Like with testing, I had assumed all the Boost stuff would just work and I would not look elsewhere. I was wrong. Again it was the cross-platform stuff that made it hard for me. I guess the real issue here is my lack of familiarity with Linux development but as I found myself heading off into the weeds for the umpteenth time I decided to go header only. So far I am not regretting this.

