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


# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_COMMAND = /usr/src/cmake-3.13.4/bin/cmake

# The command to remove a file.
RM = /usr/src/cmake-3.13.4/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jucilab/sylar

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jucilab/sylar

# Include any dependencies generated for this target.
include CMakeFiles/sylar.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/sylar.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/sylar.dir/flags.make

CMakeFiles/sylar.dir/src/log.cc.o: CMakeFiles/sylar.dir/flags.make
CMakeFiles/sylar.dir/src/log.cc.o: src/log.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jucilab/sylar/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/sylar.dir/src/log.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sylar.dir/src/log.cc.o -c /home/jucilab/sylar/src/log.cc

CMakeFiles/sylar.dir/src/log.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sylar.dir/src/log.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jucilab/sylar/src/log.cc > CMakeFiles/sylar.dir/src/log.cc.i

CMakeFiles/sylar.dir/src/log.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sylar.dir/src/log.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jucilab/sylar/src/log.cc -o CMakeFiles/sylar.dir/src/log.cc.s

CMakeFiles/sylar.dir/src/util.cc.o: CMakeFiles/sylar.dir/flags.make
CMakeFiles/sylar.dir/src/util.cc.o: src/util.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jucilab/sylar/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/sylar.dir/src/util.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sylar.dir/src/util.cc.o -c /home/jucilab/sylar/src/util.cc

CMakeFiles/sylar.dir/src/util.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sylar.dir/src/util.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jucilab/sylar/src/util.cc > CMakeFiles/sylar.dir/src/util.cc.i

CMakeFiles/sylar.dir/src/util.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sylar.dir/src/util.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jucilab/sylar/src/util.cc -o CMakeFiles/sylar.dir/src/util.cc.s

CMakeFiles/sylar.dir/src/config.cc.o: CMakeFiles/sylar.dir/flags.make
CMakeFiles/sylar.dir/src/config.cc.o: src/config.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jucilab/sylar/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/sylar.dir/src/config.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sylar.dir/src/config.cc.o -c /home/jucilab/sylar/src/config.cc

CMakeFiles/sylar.dir/src/config.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sylar.dir/src/config.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jucilab/sylar/src/config.cc > CMakeFiles/sylar.dir/src/config.cc.i

CMakeFiles/sylar.dir/src/config.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sylar.dir/src/config.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jucilab/sylar/src/config.cc -o CMakeFiles/sylar.dir/src/config.cc.s

CMakeFiles/sylar.dir/src/thread.cc.o: CMakeFiles/sylar.dir/flags.make
CMakeFiles/sylar.dir/src/thread.cc.o: src/thread.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jucilab/sylar/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/sylar.dir/src/thread.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sylar.dir/src/thread.cc.o -c /home/jucilab/sylar/src/thread.cc

CMakeFiles/sylar.dir/src/thread.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sylar.dir/src/thread.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jucilab/sylar/src/thread.cc > CMakeFiles/sylar.dir/src/thread.cc.i

CMakeFiles/sylar.dir/src/thread.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sylar.dir/src/thread.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jucilab/sylar/src/thread.cc -o CMakeFiles/sylar.dir/src/thread.cc.s

# Object files for target sylar
sylar_OBJECTS = \
"CMakeFiles/sylar.dir/src/log.cc.o" \
"CMakeFiles/sylar.dir/src/util.cc.o" \
"CMakeFiles/sylar.dir/src/config.cc.o" \
"CMakeFiles/sylar.dir/src/thread.cc.o"

# External object files for target sylar
sylar_EXTERNAL_OBJECTS =

lib/libsylar.so: CMakeFiles/sylar.dir/src/log.cc.o
lib/libsylar.so: CMakeFiles/sylar.dir/src/util.cc.o
lib/libsylar.so: CMakeFiles/sylar.dir/src/config.cc.o
lib/libsylar.so: CMakeFiles/sylar.dir/src/thread.cc.o
lib/libsylar.so: CMakeFiles/sylar.dir/build.make
lib/libsylar.so: CMakeFiles/sylar.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jucilab/sylar/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX shared library lib/libsylar.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sylar.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/sylar.dir/build: lib/libsylar.so

.PHONY : CMakeFiles/sylar.dir/build

CMakeFiles/sylar.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/sylar.dir/cmake_clean.cmake
.PHONY : CMakeFiles/sylar.dir/clean

CMakeFiles/sylar.dir/depend:
	cd /home/jucilab/sylar && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jucilab/sylar /home/jucilab/sylar /home/jucilab/sylar /home/jucilab/sylar /home/jucilab/sylar/CMakeFiles/sylar.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/sylar.dir/depend

