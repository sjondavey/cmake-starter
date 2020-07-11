cmake_minimum_required(VERSION 3.16)

# Project config outside of CMake just in case I want to interact with it automatically e.g. 
# get the build process to auto increment the version number
include (${CMAKE_CURRENT_LIST_DIR}/project-meta-info.in)
# Variables set in project-meta-info.in
project(${PROJECT_NAME_STR} 
        VERSION ${project_version}    
        DESCRIPTION ${project_description}
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17) # I have not used these features yet but wanted this here anyway
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Boost: Get all the stuff you need once, don't load different packages in the sub-projects individual CMakeLists.txt
set(BOOST_VERSION 1.73.0) # I have not used these features yet but wanted this here anyway
# From: https://cmake.org/cmake/help/git-master/module/FindBoost.html
set(Boost_USE_STATIC_LIBS        ON)  # only find static libs
set(Boost_USE_DEBUG_LIBS         OFF) # ignore debug libs and
set(Boost_USE_RELEASE_LIBS       ON)  # only find release libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME     OFF)
# TODO: I cannot get find_package(...) to work in CONFIG mode with vcpkg. I am able to get the default modelue mode
# to work so I'm sticking with that
find_package(Boost ${BOOST_VERSION} REQUIRED) # I'm using the header only math package so am not providing COMPONENTS here

if (Boost_FOUND)
  # TODO: I wanted to use Deniz Bahadir's approach (mentioned in README) but just could not get it to work
  #       so I defaulted to some less than 'modern' cmake becasue I could get that to work
  # set_target_property(Boost::boost # Boost::boost for the header only libraries
  #                     PROPERTIES GLOBAL TRUE)   
  include_directories(${Boost_INCLUDE_DIRS})
else()
   MESSAGE("BOOST not found")
endif()


# Find other CMakeList.txt 
add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(app)
add_subdirectory(python)


# Notes:
# Good Overall refernces for CMake projects:
# https://stackoverflow.com/questions/40227333/cmake-setup-multiple-projects-and-dependiencies-between-them/40242257#40242257

# include_directories vs. target_include_directories (https://stackoverflow.com/questions/31969547/what-is-the-difference-between-include-directories-and-target-include-directorie)
# include_directories(x/y): accessible for all the files in the source-tree
# target_include_directories(t x/y): accessible for a specific target when compile