# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/klevisresuli/Documents/second year/vds_project/VDSProject_Group3"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/klevisresuli/Documents/second year/vds_project/VDSProject_Group3"

# Include any dependencies generated for this target.
include src/test/CMakeFiles/VDSProject_test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/test/CMakeFiles/VDSProject_test.dir/compiler_depend.make

# Include the progress variables for this target.
include src/test/CMakeFiles/VDSProject_test.dir/progress.make

# Include the compile flags for this target's objects.
include src/test/CMakeFiles/VDSProject_test.dir/flags.make

src/test/CMakeFiles/VDSProject_test.dir/main_test.cpp.o: src/test/CMakeFiles/VDSProject_test.dir/flags.make
src/test/CMakeFiles/VDSProject_test.dir/main_test.cpp.o: src/test/main_test.cpp
src/test/CMakeFiles/VDSProject_test.dir/main_test.cpp.o: src/test/CMakeFiles/VDSProject_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/klevisresuli/Documents/second year/vds_project/VDSProject_Group3/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/test/CMakeFiles/VDSProject_test.dir/main_test.cpp.o"
	cd "/home/klevisresuli/Documents/second year/vds_project/VDSProject_Group3/src/test" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/test/CMakeFiles/VDSProject_test.dir/main_test.cpp.o -MF CMakeFiles/VDSProject_test.dir/main_test.cpp.o.d -o CMakeFiles/VDSProject_test.dir/main_test.cpp.o -c "/home/klevisresuli/Documents/second year/vds_project/VDSProject_Group3/src/test/main_test.cpp"

src/test/CMakeFiles/VDSProject_test.dir/main_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/VDSProject_test.dir/main_test.cpp.i"
	cd "/home/klevisresuli/Documents/second year/vds_project/VDSProject_Group3/src/test" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/klevisresuli/Documents/second year/vds_project/VDSProject_Group3/src/test/main_test.cpp" > CMakeFiles/VDSProject_test.dir/main_test.cpp.i

src/test/CMakeFiles/VDSProject_test.dir/main_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/VDSProject_test.dir/main_test.cpp.s"
	cd "/home/klevisresuli/Documents/second year/vds_project/VDSProject_Group3/src/test" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/klevisresuli/Documents/second year/vds_project/VDSProject_Group3/src/test/main_test.cpp" -o CMakeFiles/VDSProject_test.dir/main_test.cpp.s

# Object files for target VDSProject_test
VDSProject_test_OBJECTS = \
"CMakeFiles/VDSProject_test.dir/main_test.cpp.o"

# External object files for target VDSProject_test
VDSProject_test_EXTERNAL_OBJECTS =

src/test/VDSProject_test: src/test/CMakeFiles/VDSProject_test.dir/main_test.cpp.o
src/test/VDSProject_test: src/test/CMakeFiles/VDSProject_test.dir/build.make
src/test/VDSProject_test: src/libManager.a
src/test/VDSProject_test: lib/libgtest.a
src/test/VDSProject_test: lib/libgtest_main.a
src/test/VDSProject_test: lib/libgtest.a
src/test/VDSProject_test: src/test/CMakeFiles/VDSProject_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/klevisresuli/Documents/second year/vds_project/VDSProject_Group3/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable VDSProject_test"
	cd "/home/klevisresuli/Documents/second year/vds_project/VDSProject_Group3/src/test" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/VDSProject_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/test/CMakeFiles/VDSProject_test.dir/build: src/test/VDSProject_test
.PHONY : src/test/CMakeFiles/VDSProject_test.dir/build

src/test/CMakeFiles/VDSProject_test.dir/clean:
	cd "/home/klevisresuli/Documents/second year/vds_project/VDSProject_Group3/src/test" && $(CMAKE_COMMAND) -P CMakeFiles/VDSProject_test.dir/cmake_clean.cmake
.PHONY : src/test/CMakeFiles/VDSProject_test.dir/clean

src/test/CMakeFiles/VDSProject_test.dir/depend:
	cd "/home/klevisresuli/Documents/second year/vds_project/VDSProject_Group3" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/klevisresuli/Documents/second year/vds_project/VDSProject_Group3" "/home/klevisresuli/Documents/second year/vds_project/VDSProject_Group3/src/test" "/home/klevisresuli/Documents/second year/vds_project/VDSProject_Group3" "/home/klevisresuli/Documents/second year/vds_project/VDSProject_Group3/src/test" "/home/klevisresuli/Documents/second year/vds_project/VDSProject_Group3/src/test/CMakeFiles/VDSProject_test.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : src/test/CMakeFiles/VDSProject_test.dir/depend

