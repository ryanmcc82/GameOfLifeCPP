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
CMAKE_SOURCE_DIR = /home/ryanmcc/GameOfLifeCPP

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ryanmcc/GameOfLifeCPP/build_phi

# Include any dependencies generated for this target.
include CMakeFiles/GOLCpp2D.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/GOLCpp2D.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/GOLCpp2D.dir/flags.make

CMakeFiles/GOLCpp2D.dir/GOLCpp2D.o: CMakeFiles/GOLCpp2D.dir/flags.make
CMakeFiles/GOLCpp2D.dir/GOLCpp2D.o: ../GOLCpp2D.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ryanmcc/GameOfLifeCPP/build_phi/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/GOLCpp2D.dir/GOLCpp2D.o"
	/share/apps/tools/intel/composer_xe_2015.3.187/bin/intel64/icpc   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/GOLCpp2D.dir/GOLCpp2D.o -c /home/ryanmcc/GameOfLifeCPP/GOLCpp2D.cpp

CMakeFiles/GOLCpp2D.dir/GOLCpp2D.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GOLCpp2D.dir/GOLCpp2D.i"
	/share/apps/tools/intel/composer_xe_2015.3.187/bin/intel64/icpc  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ryanmcc/GameOfLifeCPP/GOLCpp2D.cpp > CMakeFiles/GOLCpp2D.dir/GOLCpp2D.i

CMakeFiles/GOLCpp2D.dir/GOLCpp2D.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GOLCpp2D.dir/GOLCpp2D.s"
	/share/apps/tools/intel/composer_xe_2015.3.187/bin/intel64/icpc  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ryanmcc/GameOfLifeCPP/GOLCpp2D.cpp -o CMakeFiles/GOLCpp2D.dir/GOLCpp2D.s

CMakeFiles/GOLCpp2D.dir/GOLCpp2D.o.requires:
.PHONY : CMakeFiles/GOLCpp2D.dir/GOLCpp2D.o.requires

CMakeFiles/GOLCpp2D.dir/GOLCpp2D.o.provides: CMakeFiles/GOLCpp2D.dir/GOLCpp2D.o.requires
	$(MAKE) -f CMakeFiles/GOLCpp2D.dir/build.make CMakeFiles/GOLCpp2D.dir/GOLCpp2D.o.provides.build
.PHONY : CMakeFiles/GOLCpp2D.dir/GOLCpp2D.o.provides

CMakeFiles/GOLCpp2D.dir/GOLCpp2D.o.provides.build: CMakeFiles/GOLCpp2D.dir/GOLCpp2D.o

# Object files for target GOLCpp2D
GOLCpp2D_OBJECTS = \
"CMakeFiles/GOLCpp2D.dir/GOLCpp2D.o"

# External object files for target GOLCpp2D
GOLCpp2D_EXTERNAL_OBJECTS =

GOLCpp2D: CMakeFiles/GOLCpp2D.dir/GOLCpp2D.o
GOLCpp2D: CMakeFiles/GOLCpp2D.dir/build.make
GOLCpp2D: CMakeFiles/GOLCpp2D.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable GOLCpp2D"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/GOLCpp2D.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/GOLCpp2D.dir/build: GOLCpp2D
.PHONY : CMakeFiles/GOLCpp2D.dir/build

CMakeFiles/GOLCpp2D.dir/requires: CMakeFiles/GOLCpp2D.dir/GOLCpp2D.o.requires
.PHONY : CMakeFiles/GOLCpp2D.dir/requires

CMakeFiles/GOLCpp2D.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/GOLCpp2D.dir/cmake_clean.cmake
.PHONY : CMakeFiles/GOLCpp2D.dir/clean

CMakeFiles/GOLCpp2D.dir/depend:
	cd /home/ryanmcc/GameOfLifeCPP/build_phi && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ryanmcc/GameOfLifeCPP /home/ryanmcc/GameOfLifeCPP /home/ryanmcc/GameOfLifeCPP/build_phi /home/ryanmcc/GameOfLifeCPP/build_phi /home/ryanmcc/GameOfLifeCPP/build_phi/CMakeFiles/GOLCpp2D.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/GOLCpp2D.dir/depend

