# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/kevinv/Documents/MAP_CoSim_20/example/slave

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kevinv/Documents/MAP_CoSim_20/example/slave/build

# Include any dependencies generated for this target.
include FMI4cpp/examples/CMakeFiles/fmu_test.dir/depend.make

# Include the progress variables for this target.
include FMI4cpp/examples/CMakeFiles/fmu_test.dir/progress.make

# Include the compile flags for this target's objects.
include FMI4cpp/examples/CMakeFiles/fmu_test.dir/flags.make

FMI4cpp/examples/CMakeFiles/fmu_test.dir/fmu_test.cpp.o: FMI4cpp/examples/CMakeFiles/fmu_test.dir/flags.make
FMI4cpp/examples/CMakeFiles/fmu_test.dir/fmu_test.cpp.o: ../FMI4cpp/examples/fmu_test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kevinv/Documents/MAP_CoSim_20/example/slave/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object FMI4cpp/examples/CMakeFiles/fmu_test.dir/fmu_test.cpp.o"
	cd /home/kevinv/Documents/MAP_CoSim_20/example/slave/build/FMI4cpp/examples && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/fmu_test.dir/fmu_test.cpp.o -c /home/kevinv/Documents/MAP_CoSim_20/example/slave/FMI4cpp/examples/fmu_test.cpp

FMI4cpp/examples/CMakeFiles/fmu_test.dir/fmu_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/fmu_test.dir/fmu_test.cpp.i"
	cd /home/kevinv/Documents/MAP_CoSim_20/example/slave/build/FMI4cpp/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kevinv/Documents/MAP_CoSim_20/example/slave/FMI4cpp/examples/fmu_test.cpp > CMakeFiles/fmu_test.dir/fmu_test.cpp.i

FMI4cpp/examples/CMakeFiles/fmu_test.dir/fmu_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/fmu_test.dir/fmu_test.cpp.s"
	cd /home/kevinv/Documents/MAP_CoSim_20/example/slave/build/FMI4cpp/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kevinv/Documents/MAP_CoSim_20/example/slave/FMI4cpp/examples/fmu_test.cpp -o CMakeFiles/fmu_test.dir/fmu_test.cpp.s

# Object files for target fmu_test
fmu_test_OBJECTS = \
"CMakeFiles/fmu_test.dir/fmu_test.cpp.o"

# External object files for target fmu_test
fmu_test_EXTERNAL_OBJECTS =

FMI4cpp/examples/fmu_test: FMI4cpp/examples/CMakeFiles/fmu_test.dir/fmu_test.cpp.o
FMI4cpp/examples/fmu_test: FMI4cpp/examples/CMakeFiles/fmu_test.dir/build.make
FMI4cpp/examples/fmu_test: FMI4cpp/src/libfmi4cpp.so
FMI4cpp/examples/fmu_test: /usr/lib/x86_64-linux-gnu/libzip.so
FMI4cpp/examples/fmu_test: FMI4cpp/examples/CMakeFiles/fmu_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kevinv/Documents/MAP_CoSim_20/example/slave/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable fmu_test"
	cd /home/kevinv/Documents/MAP_CoSim_20/example/slave/build/FMI4cpp/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/fmu_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
FMI4cpp/examples/CMakeFiles/fmu_test.dir/build: FMI4cpp/examples/fmu_test

.PHONY : FMI4cpp/examples/CMakeFiles/fmu_test.dir/build

FMI4cpp/examples/CMakeFiles/fmu_test.dir/clean:
	cd /home/kevinv/Documents/MAP_CoSim_20/example/slave/build/FMI4cpp/examples && $(CMAKE_COMMAND) -P CMakeFiles/fmu_test.dir/cmake_clean.cmake
.PHONY : FMI4cpp/examples/CMakeFiles/fmu_test.dir/clean

FMI4cpp/examples/CMakeFiles/fmu_test.dir/depend:
	cd /home/kevinv/Documents/MAP_CoSim_20/example/slave/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kevinv/Documents/MAP_CoSim_20/example/slave /home/kevinv/Documents/MAP_CoSim_20/example/slave/FMI4cpp/examples /home/kevinv/Documents/MAP_CoSim_20/example/slave/build /home/kevinv/Documents/MAP_CoSim_20/example/slave/build/FMI4cpp/examples /home/kevinv/Documents/MAP_CoSim_20/example/slave/build/FMI4cpp/examples/CMakeFiles/fmu_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : FMI4cpp/examples/CMakeFiles/fmu_test.dir/depend
