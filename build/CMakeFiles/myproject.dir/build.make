# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.26.0/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.26.0/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/muslimitsuhide/2023_1_OND

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/muslimitsuhide/2023_1_OND/build

# Include any dependencies generated for this target.
include CMakeFiles/myproject.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/myproject.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/myproject.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/myproject.dir/flags.make

CMakeFiles/myproject.dir/lib/server/src/server.cpp.o: CMakeFiles/myproject.dir/flags.make
CMakeFiles/myproject.dir/lib/server/src/server.cpp.o: /Users/muslimitsuhide/2023_1_OND/lib/server/src/server.cpp
CMakeFiles/myproject.dir/lib/server/src/server.cpp.o: CMakeFiles/myproject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/muslimitsuhide/2023_1_OND/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/myproject.dir/lib/server/src/server.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/myproject.dir/lib/server/src/server.cpp.o -MF CMakeFiles/myproject.dir/lib/server/src/server.cpp.o.d -o CMakeFiles/myproject.dir/lib/server/src/server.cpp.o -c /Users/muslimitsuhide/2023_1_OND/lib/server/src/server.cpp

CMakeFiles/myproject.dir/lib/server/src/server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/myproject.dir/lib/server/src/server.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/muslimitsuhide/2023_1_OND/lib/server/src/server.cpp > CMakeFiles/myproject.dir/lib/server/src/server.cpp.i

CMakeFiles/myproject.dir/lib/server/src/server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/myproject.dir/lib/server/src/server.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/muslimitsuhide/2023_1_OND/lib/server/src/server.cpp -o CMakeFiles/myproject.dir/lib/server/src/server.cpp.s

# Object files for target myproject
myproject_OBJECTS = \
"CMakeFiles/myproject.dir/lib/server/src/server.cpp.o"

# External object files for target myproject
myproject_EXTERNAL_OBJECTS =

myproject: CMakeFiles/myproject.dir/lib/server/src/server.cpp.o
myproject: CMakeFiles/myproject.dir/build.make
myproject: CMakeFiles/myproject.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/muslimitsuhide/2023_1_OND/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable myproject"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/myproject.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/myproject.dir/build: myproject
.PHONY : CMakeFiles/myproject.dir/build

CMakeFiles/myproject.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/myproject.dir/cmake_clean.cmake
.PHONY : CMakeFiles/myproject.dir/clean

CMakeFiles/myproject.dir/depend:
	cd /Users/muslimitsuhide/2023_1_OND/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/muslimitsuhide/2023_1_OND /Users/muslimitsuhide/2023_1_OND /Users/muslimitsuhide/2023_1_OND/build /Users/muslimitsuhide/2023_1_OND/build /Users/muslimitsuhide/2023_1_OND/build/CMakeFiles/myproject.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/myproject.dir/depend

