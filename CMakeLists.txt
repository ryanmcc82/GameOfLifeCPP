cmake_minimum_required(VERSION 3.2)
project(GameOfLifeCppContinuous)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp")

set(SOURCE_FILES continuous.cpp)
add_executable(GameOfLifeCppContinuous ${SOURCE_FILES} continuous.cpp)


set(SOURCE_FILES1 GOFCpp.cpp)
add_executable(GOFCpp ${SOURCE_FILES1} GOFCpp.cpp)


set(SOURCE_FILES2 unparallel.cpp)
add_executable(unparallel ${SOURCE_FILES2} unparallel.cpp)

set(SOURCE_FILES3 GOLCppReduction.cpp)
add_executable(GOLCppReduction ${SOURCE_FILES3} GOLCppReduction.cpp)


set(SOURCE_FILES4 GOLCpp2D.cpp)
add_executable(GOLCpp2D ${SOURCE_FILES4} GOLCpp2D.cpp)