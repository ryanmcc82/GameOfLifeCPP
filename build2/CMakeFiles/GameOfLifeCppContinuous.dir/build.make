# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ryanmcc/GoL2/GameOfLifeCPP

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ryanmcc/GoL2/GameOfLifeCPP/build2

# Include any dependencies generated for this target.
include CMakeFiles/GameOfLifeCppContinuous.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/GameOfLifeCppContinuous.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/GameOfLifeCppContinuous.dir/flags.make

CMakeFiles/GameOfLifeCppContinuous.dir/continuous.o: CMakeFiles/GameOfLifeCppContinuous.dir/flags.make
CMakeFiles/GameOfLifeCppContinuous.dir/continuous.o: ../continuous.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ryanmcc/GoL2/GameOfLifeCPP/build2/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/GameOfLifeCppContinuous.dir/continuous.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/GameOfLifeCppContinuous.dir/continuous.o -c /home/ryanmcc/GoL2/GameOfLifeCPP/continuous.cpp

CMakeFiles/GameOfLifeCppContinuous.dir/continuous.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GameOfLifeCppContinuous.dir/continuous.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ryanmcc/GoL2/GameOfLifeCPP/continuous.cpp > CMakeFiles/GameOfLifeCppContinuous.dir/continuous.i

CMakeFiles/GameOfLifeCppContinuous.dir/continuous.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GameOfLifeCppContinuous.dir/continuous.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ryanmcc/GoL2/GameOfLifeCPP/continuous.cpp -o CMakeFiles/GameOfLifeCppContinuous.dir/continuous.s

CMakeFiles/GameOfLifeCppContinuous.dir/continuous.o.requires:
.PHONY : CMakeFiles/GameOfLifeCppContinuous.dir/continuous.o.requires

CMakeFiles/GameOfLifeCppContinuous.dir/continuous.o.provides: CMakeFiles/GameOfLifeCppContinuous.dir/continuous.o.requires
	$(MAKE) -f CMakeFiles/GameOfLifeCppContinuous.dir/build.make CMakeFiles/GameOfLifeCppContinuous.dir/continuous.o.provides.build
.PHONY : CMakeFiles/GameOfLifeCppContinuous.dir/continuous.o.provides

CMakeFiles/GameOfLifeCppContinuous.dir/continuous.o.provides.build: CMakeFiles/GameOfLifeCppContinuous.dir/continuous.o

# Object files for target GameOfLifeCppContinuous
GameOfLifeCppContinuous_OBJECTS = \
"CMakeFiles/GameOfLifeCppContinuous.dir/continuous.o"

# External object files for target GameOfLifeCppContinuous
GameOfLifeCppContinuous_EXTERNAL_OBJECTS =

GameOfLifeCppContinuous: CMakeFiles/GameOfLifeCppContinuous.dir/continuous.o
GameOfLifeCppContinuous: CMakeFiles/GameOfLifeCppContinuous.dir/build.make
GameOfLifeCppContinuous: CMakeFiles/GameOfLifeCppContinuous.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable GameOfLifeCppContinuous"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/GameOfLifeCppContinuous.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/GameOfLifeCppContinuous.dir/build: GameOfLifeCppContinuous
.PHONY : CMakeFiles/GameOfLifeCppContinuous.dir/build

CMakeFiles/GameOfLifeCppContinuous.dir/requires: CMakeFiles/GameOfLifeCppContinuous.dir/continuous.o.requires
.PHONY : CMakeFiles/GameOfLifeCppContinuous.dir/requires

CMakeFiles/GameOfLifeCppContinuous.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/GameOfLifeCppContinuous.dir/cmake_clean.cmake
.PHONY : CMakeFiles/GameOfLifeCppContinuous.dir/clean

CMakeFiles/GameOfLifeCppContinuous.dir/depend:
	cd /home/ryanmcc/GoL2/GameOfLifeCPP/build2 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ryanmcc/GoL2/GameOfLifeCPP /home/ryanmcc/GoL2/GameOfLifeCPP /home/ryanmcc/GoL2/GameOfLifeCPP/build2 /home/ryanmcc/GoL2/GameOfLifeCPP/build2 /home/ryanmcc/GoL2/GameOfLifeCPP/build2/CMakeFiles/GameOfLifeCppContinuous.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/GameOfLifeCppContinuous.dir/depend
