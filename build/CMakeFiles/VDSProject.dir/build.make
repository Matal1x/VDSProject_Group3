# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /home/wsl/VDSProject_Group3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/wsl/VDSProject_Group3/build

# Include any dependencies generated for this target.
include CMakeFiles/VDSProject.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/VDSProject.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/VDSProject.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/VDSProject.dir/flags.make

CMakeFiles/VDSProject.dir/src/main.cpp.o: CMakeFiles/VDSProject.dir/flags.make
CMakeFiles/VDSProject.dir/src/main.cpp.o: ../src/main.cpp
CMakeFiles/VDSProject.dir/src/main.cpp.o: CMakeFiles/VDSProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wsl/VDSProject_Group3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/VDSProject.dir/src/main.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/VDSProject.dir/src/main.cpp.o -MF CMakeFiles/VDSProject.dir/src/main.cpp.o.d -o CMakeFiles/VDSProject.dir/src/main.cpp.o -c /home/wsl/VDSProject_Group3/src/main.cpp

CMakeFiles/VDSProject.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/VDSProject.dir/src/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wsl/VDSProject_Group3/src/main.cpp > CMakeFiles/VDSProject.dir/src/main.cpp.i

CMakeFiles/VDSProject.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/VDSProject.dir/src/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wsl/VDSProject_Group3/src/main.cpp -o CMakeFiles/VDSProject.dir/src/main.cpp.s

# Object files for target VDSProject
VDSProject_OBJECTS = \
"CMakeFiles/VDSProject.dir/src/main.cpp.o"

# External object files for target VDSProject
VDSProject_EXTERNAL_OBJECTS =

VDSProject: CMakeFiles/VDSProject.dir/src/main.cpp.o
VDSProject: CMakeFiles/VDSProject.dir/build.make
VDSProject: src/libManager.a
VDSProject: CMakeFiles/VDSProject.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/wsl/VDSProject_Group3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable VDSProject"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/VDSProject.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/VDSProject.dir/build: VDSProject
.PHONY : CMakeFiles/VDSProject.dir/build

CMakeFiles/VDSProject.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/VDSProject.dir/cmake_clean.cmake
.PHONY : CMakeFiles/VDSProject.dir/clean

CMakeFiles/VDSProject.dir/depend:
	cd /home/wsl/VDSProject_Group3/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wsl/VDSProject_Group3 /home/wsl/VDSProject_Group3 /home/wsl/VDSProject_Group3/build /home/wsl/VDSProject_Group3/build /home/wsl/VDSProject_Group3/build/CMakeFiles/VDSProject.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/VDSProject.dir/depend

