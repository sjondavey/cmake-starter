cmake_minimum_required(VERSION 3.16) # Helps to have this repeated in case you want this to be the root of seperate project

set(MC_LIBRARY ${PROJECT_NAME_STR}_lib)

set(MC_LIB_HDR 
    formula/Black76Formula.h
    )


set(MC_LIB_SRC 
    formula/Black76Formula.cpp
    )

# Making use of the target_sources(...) to add sources and headers rather than listing them in the add_library(...) macro. 
# target_sources allows sources to be declared as PRIVATE (necessary to build), INTERFACE (not required for build, 
# only use NOTE that headers are not needed for the build) and  PUBLIC (necessary of build and use). This control is 
# not possible in the add_library(...) macro
if(MSVC)
        add_library(${MC_LIBRARY} STATIC)
else()
        add_library(${MC_LIBRARY} SHARED)
endif()
target_sources(${MC_LIBRARY}
                PRIVATE ${MC_LIB_SRC}
                INTERFACE ${MC_LIB_HDR}) # Header not required for build, therefore 


