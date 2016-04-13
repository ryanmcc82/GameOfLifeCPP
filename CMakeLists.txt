cmake_minimum_required(VERSION 2.3)
project(GameOfLifeCppContinuous)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp")

set(SOURCE_FILES continuous.cpp)
add_executable(GameOfLifeCppContinuous ${SOURCE_FILES} continuous.cpp)


set(SOURCE_FILES1 GOFCpp.cpp)
add_executable(GOFCpp ${SOURCE_FILES1} GOFCpp.cpp)


set(SOURCE_FILES2 unparallel.cpp)
add_executable(unparallel ${SOURCE_FILES2} unparallel.cpp)


set(SOURCE_FILES2 GOLCppReduction.cpp)
add_executable(GOLCppReduction ${SOURCE_FILES2} GOLCppReduction.cpp)
