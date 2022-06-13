
# What is this?
Non-trivial starter project using CMake to create a cross platform (Windows 10 / Ubuntu 20) C++ library with tests (Catch2), exposed via a command line application and as a python module (Pybind11). 

I aspired to use ['Oh No! More Modern CMake'](https://www.youtube.com/watch?v=y9kSr5enrSk) by Deniz Bahadir at 'Meeting C++ 2019' the basis for this. I fell short. Hopefully I can fix these in time. 

The project structure is:
```
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
```

## Calling the library from Python
I used [Pybind11](https://github.com/pybind/pybind11) for the Python interface. This worked well out the box on my Windows machine (only one installed version of Python) but gave me some issues in Ununtu which had multiple versions of Python installed (see the notes). It also took me longer than I'm happy to admit that the [documents state very clearly](https://pybind11.readthedocs.io/en/stable/basics.html) that you need to install python-dev or python3-dev packages which are not on Ubuntu by default.

The project builds an equivalent of `cmake_starter.cp37-win_amd64.pyd` in Windows under the build directory. If you launch a Python from the command line in this directory they the tools is accessed as
```python
import cmake_starter as formula
help(formula.call_value)
formula.call_value(100,110,0.2,0.98)
help(formula.Black76Call)
call = formula.Black76Call(100,110,0.2,0.98)
call.delta()
```
#### NOTES
I struggled a bit with the Linux build and [inconsistent versions](https://stackoverflow.com/questions/62773837/cmake-and-pybind11-using-inconsistent-python-versions) on my machine which came with 2.7 and 3.8 by default. I ended up with a solution here that I don't like, having to hard code the version of python for the GNU compiler works, but is clumsy. 


## Background - the what and why

This project was me starting over (> 8 years of not writing C++ code). I am not a developer and, even historically, worried more about the algorithms
than building 'good' projects. I am older now and understand that good projects are important. I started this to try to build a good project. It is 
a work in progress. This was much more detailed and time consuming than I expected. 

There are lots of compromises here. Places where I could not get a good solution working in a reasonable amount of time. Hopefully I (or you!) will return 
and fix these in time. I really do want to get to coding (algorithms) now. 

Here are my chosen tools - and why (it is really important to understand the why before choosing tools)

### Language: C++ 
Why: I listened to Lex Fridman's [podcast](https://www.youtube.com/watch?v=uTxRF5ag27A) interview Bjarne Stroustrup. It made me wanted to be a better man! It's not a good answer to why but it is the only one I have. I could have just done this in Python but I'm trying to convince myself that I will require execution speed. I am going to write a Monte Carlo engine next just to justify my comment about execution speed! 

### Environnement: Visual Studio Code
Why: Previously I built Excel Add-Ins (trying to emulate the very goo [quantlib.org](https://www.quantlib.org/) and in particular their excel addin). It was all for Windows and Visual Studio was the only real option. This time I wanted to write something for multiple platforms (ultimately docker to run parallel simulations using infrastructure) so I wanted one tool that I could use in Windows and Ubuntu while I was warming up. VSCode took some time to get into (setting.json and launch.json all assume you know what you are doing - I did not). In the end, I'm really happy with VSCode. The experience in Windows and Ubuntu is identical (for me and at this stage - I'm touching wood that it continues). I use the C++ and CMake extensions. 

### Package Management: vcpkg
Why: Historically I didn't use a tool, just did things manually. Because I was working now cross platform, that approach would not be sufficient. vcpkg was the first thing I tried. So far, it just works (although I have an uncomfortable feeling that there are surprises waiting for me in the weeds!). If I have issues later, I may have to think about this. I hope this is not a problem for a future day.

### Build Utility: CMake
Why: I genuinely don't know what I'm doing here. It's been a very steep learning curve. I'm surprised C++ developers are not a more grumpy lot! My difficulties with CMake are the reason for this project. Despite all the difficulties, I could not find a low effort alternative.

### Testing: Catch2
Why: I started using the boost testing framework. I had previous experience with it. I found however that I was just fighting links and builds across Windows and Ubuntu. Out of frustration I tried Catch2. Because it is header only, it just works. As my code volume increases I may have to spend more time tinkering but as a cross platform tool, it allows you to hit the ground running.

### Python Interface: Pybind11
Why: Like with testing, I had assumed all the Boost stuff would just work and I would not look elsewhere. I was wrong. See for example [here](https://stackoverflow.com/questions/62623528/cmake-find-packageboost-components-python-fails-but-other-boost-packages-work) and [here](https://stackoverflow.com/questions/62716602/cmake-target-link-libraries-for-boost-python-does-not-find-the-lib-but-the-vari). Again it was the cross-platform stuff that made it hard for me. I guess the real issue here is my lack of familiarity with Linux development but as I found myself heading off into the weeds for the umpteenth time I decided to go header only. So far I am not regretting this.

