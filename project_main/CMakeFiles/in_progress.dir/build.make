# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Documents/TDP005/project_main

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Documents/TDP005/project_main

# Include any dependencies generated for this target.
include CMakeFiles/in_progress.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/in_progress.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/in_progress.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/in_progress.dir/flags.make

CMakeFiles/in_progress.dir/in_progress.o: CMakeFiles/in_progress.dir/flags.make
CMakeFiles/in_progress.dir/in_progress.o: in_progress.cc
CMakeFiles/in_progress.dir/in_progress.o: CMakeFiles/in_progress.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Documents/TDP005/project_main/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/in_progress.dir/in_progress.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/in_progress.dir/in_progress.o -MF CMakeFiles/in_progress.dir/in_progress.o.d -o CMakeFiles/in_progress.dir/in_progress.o -c /Documents/TDP005/project_main/in_progress.cc

CMakeFiles/in_progress.dir/in_progress.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/in_progress.dir/in_progress.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Documents/TDP005/project_main/in_progress.cc > CMakeFiles/in_progress.dir/in_progress.i

CMakeFiles/in_progress.dir/in_progress.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/in_progress.dir/in_progress.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Documents/TDP005/project_main/in_progress.cc -o CMakeFiles/in_progress.dir/in_progress.s

# Object files for target in_progress
in_progress_OBJECTS = \
"CMakeFiles/in_progress.dir/in_progress.o"

# External object files for target in_progress
in_progress_EXTERNAL_OBJECTS =

in_progress: CMakeFiles/in_progress.dir/in_progress.o
in_progress: CMakeFiles/in_progress.dir/build.make
in_progress: /usr/lib/x86_64-linux-gnu/libsfml-network.so.2.5.1
in_progress: /usr/lib/x86_64-linux-gnu/libsfml-graphics.so.2.5.1
in_progress: /usr/lib/x86_64-linux-gnu/libsfml-window.so.2.5.1
in_progress: /usr/lib/x86_64-linux-gnu/libsfml-system.so.2.5.1
in_progress: CMakeFiles/in_progress.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Documents/TDP005/project_main/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable in_progress"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/in_progress.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/in_progress.dir/build: in_progress
.PHONY : CMakeFiles/in_progress.dir/build

CMakeFiles/in_progress.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/in_progress.dir/cmake_clean.cmake
.PHONY : CMakeFiles/in_progress.dir/clean

CMakeFiles/in_progress.dir/depend:
	cd /Documents/TDP005/project_main && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Documents/TDP005/project_main /Documents/TDP005/project_main /Documents/TDP005/project_main /Documents/TDP005/project_main /Documents/TDP005/project_main/CMakeFiles/in_progress.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/in_progress.dir/depend

