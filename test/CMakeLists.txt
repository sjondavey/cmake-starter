cmake_minimum_required(VERSION 3.16) # Helps to have this repeated in case you want this to be the root of seperate project

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
set(MC_UNIT_TESTS ${PROJECT_NAME_STR}_tests)

set(MC_LIB_TEST_SRC 
    test_main.cpp
    Black76FormulaTest.cpp
    )

add_executable(${MC_UNIT_TESTS} ${MC_LIB_TEST_SRC})

# The keyword 'PRIVATE' indicates that we are setting the build requirements between this <target> (monte_carlo_derivaitves_tests) 
# and the dependency (our library file). Use 'INTERFACE' for usage requirements and 'PUBLIC' for both build and usage requirements.
# You should not ommit one of these keywords, even though the macro allows you to do so - it may behave erratically
target_link_libraries(${MC_UNIT_TESTS} PRIVATE ${PROJECT_NAME_STR}_lib)

enable_testing()
add_test(DemoTest ${MC_UNIT_TESTS})