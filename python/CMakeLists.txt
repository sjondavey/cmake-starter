cmake_minimum_required(VERSION 3.16) # Helps to have this repeated in case you want this to be the root of seperate project

set(PYTON_INTERFACE ${PROJECT_NAME_STR})

# https://pybind11.readthedocs.io/en/stable/compiling.html#pybind11-add-module
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    #set(PYBIND11_PYTHON_VERSION 3.8 CACHE STRING "") - it may now be that I do not need to worry that PYBIND11_PYTHON_VERSION is a cache variable
    set(PYBIND11_PYTHON_VERSION 3.8)
endif()
find_package(pybind11 CONFIG REQUIRED)

set(PYTHON_SRC 
    PythonInterface.cpp
    )

pybind11_add_module(${PYTON_INTERFACE} ${PYTHON_SRC})

# The key is to keep the 'PRIVATE' setting in target_link_libraries(...). 'PRIVATE' indicates that we are setting the build 
# requirements between this <target> (montecarlo) and the dependency (our library file). For reference, usage requirements  
# use the keyword 'INTERFACE'. Both build and usage requirements are implied with the keyword 'PUBLIC'. You should not ommit
# one of these keywords, even though the macro allows you to do so - it may behave erratically
target_link_libraries(${PYTON_INTERFACE} PRIVATE ${PROJECT_NAME_STR}_lib)






