# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/src/cmake-3.13.4/bin/cmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/src/cmake-3.13.4/bin/ccmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/jucilab/sylar/CMakeFiles /home/jucilab/sylar/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/jucilab/sylar/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named test_address

# Build rule for target.
test_address: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 test_address
.PHONY : test_address

# fast build rule for target.
test_address/fast:
	$(MAKE) -f CMakeFiles/test_address.dir/build.make CMakeFiles/test_address.dir/build
.PHONY : test_address/fast

#=============================================================================
# Target rules for targets named test_hook

# Build rule for target.
test_hook: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 test_hook
.PHONY : test_hook

# fast build rule for target.
test_hook/fast:
	$(MAKE) -f CMakeFiles/test_hook.dir/build.make CMakeFiles/test_hook.dir/build
.PHONY : test_hook/fast

#=============================================================================
# Target rules for targets named test_iomanager

# Build rule for target.
test_iomanager: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 test_iomanager
.PHONY : test_iomanager

# fast build rule for target.
test_iomanager/fast:
	$(MAKE) -f CMakeFiles/test_iomanager.dir/build.make CMakeFiles/test_iomanager.dir/build
.PHONY : test_iomanager/fast

#=============================================================================
# Target rules for targets named test_scheduler

# Build rule for target.
test_scheduler: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 test_scheduler
.PHONY : test_scheduler

# fast build rule for target.
test_scheduler/fast:
	$(MAKE) -f CMakeFiles/test_scheduler.dir/build.make CMakeFiles/test_scheduler.dir/build
.PHONY : test_scheduler/fast

#=============================================================================
# Target rules for targets named test

# Build rule for target.
test: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 test
.PHONY : test

# fast build rule for target.
test/fast:
	$(MAKE) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/build
.PHONY : test/fast

#=============================================================================
# Target rules for targets named sylar

# Build rule for target.
sylar: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 sylar
.PHONY : sylar

# fast build rule for target.
sylar/fast:
	$(MAKE) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/build
.PHONY : sylar/fast

#=============================================================================
# Target rules for targets named test_config

# Build rule for target.
test_config: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 test_config
.PHONY : test_config

# fast build rule for target.
test_config/fast:
	$(MAKE) -f CMakeFiles/test_config.dir/build.make CMakeFiles/test_config.dir/build
.PHONY : test_config/fast

#=============================================================================
# Target rules for targets named test_thread

# Build rule for target.
test_thread: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 test_thread
.PHONY : test_thread

# fast build rule for target.
test_thread/fast:
	$(MAKE) -f CMakeFiles/test_thread.dir/build.make CMakeFiles/test_thread.dir/build
.PHONY : test_thread/fast

#=============================================================================
# Target rules for targets named test_util

# Build rule for target.
test_util: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 test_util
.PHONY : test_util

# fast build rule for target.
test_util/fast:
	$(MAKE) -f CMakeFiles/test_util.dir/build.make CMakeFiles/test_util.dir/build
.PHONY : test_util/fast

#=============================================================================
# Target rules for targets named test_socket

# Build rule for target.
test_socket: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 test_socket
.PHONY : test_socket

# fast build rule for target.
test_socket/fast:
	$(MAKE) -f CMakeFiles/test_socket.dir/build.make CMakeFiles/test_socket.dir/build
.PHONY : test_socket/fast

#=============================================================================
# Target rules for targets named test_fiber

# Build rule for target.
test_fiber: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 test_fiber
.PHONY : test_fiber

# fast build rule for target.
test_fiber/fast:
	$(MAKE) -f CMakeFiles/test_fiber.dir/build.make CMakeFiles/test_fiber.dir/build
.PHONY : test_fiber/fast

src/address.o: src/address.cc.o

.PHONY : src/address.o

# target to build an object file
src/address.cc.o:
	$(MAKE) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/src/address.cc.o
.PHONY : src/address.cc.o

src/address.i: src/address.cc.i

.PHONY : src/address.i

# target to preprocess a source file
src/address.cc.i:
	$(MAKE) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/src/address.cc.i
.PHONY : src/address.cc.i

src/address.s: src/address.cc.s

.PHONY : src/address.s

# target to generate assembly for a file
src/address.cc.s:
	$(MAKE) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/src/address.cc.s
.PHONY : src/address.cc.s

src/bytearray.o: src/bytearray.cc.o

.PHONY : src/bytearray.o

# target to build an object file
src/bytearray.cc.o:
	$(MAKE) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/src/bytearray.cc.o
.PHONY : src/bytearray.cc.o

src/bytearray.i: src/bytearray.cc.i

.PHONY : src/bytearray.i

# target to preprocess a source file
src/bytearray.cc.i:
	$(MAKE) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/src/bytearray.cc.i
.PHONY : src/bytearray.cc.i

src/bytearray.s: src/bytearray.cc.s

.PHONY : src/bytearray.s

# target to generate assembly for a file
src/bytearray.cc.s:
	$(MAKE) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/src/bytearray.cc.s
.PHONY : src/bytearray.cc.s

src/config.o: src/config.cc.o

.PHONY : src/config.o

# target to build an object file
src/config.cc.o:
	$(MAKE) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/src/config.cc.o
.PHONY : src/config.cc.o

src/config.i: src/config.cc.i

.PHONY : src/config.i

# target to preprocess a source file
src/config.cc.i:
	$(MAKE) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/src/config.cc.i
.PHONY : src/config.cc.i

src/config.s: src/config.cc.s

.PHONY : src/config.s

# target to generate assembly for a file
src/config.cc.s:
	$(MAKE) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/src/config.cc.s
.PHONY : src/config.cc.s

src/fd_manager.o: src/fd_manager.cc.o

.PHONY : src/fd_manager.o

# target to build an object file
src/fd_manager.cc.o:
	$(MAKE) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/src/fd_manager.cc.o
.PHONY : src/fd_manager.cc.o

src/fd_manager.i: src/fd_manager.cc.i

.PHONY : src/fd_manager.i

# target to preprocess a source file
src/fd_manager.cc.i:
	$(MAKE) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/src/fd_manager.cc.i
.PHONY : src/fd_manager.cc.i

src/fd_manager.s: src/fd_manager.cc.s

.PHONY : src/fd_manager.s

# target to generate assembly for a file
src/fd_manager.cc.s:
	$(MAKE) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/src/fd_manager.cc.s
.PHONY : src/fd_manager.cc.s

src/fiber.o: src/fiber.cc.o

.PHONY : src/fiber.o

# target to build an object file
src/fiber.cc.o:
	$(MAKE) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/src/fiber.cc.o
.PHONY : src/fiber.cc.o

src/fiber.i: src/fiber.cc.i

.PHONY : src/fiber.i

# target to preprocess a source file
src/fiber.cc.i:
	$(MAKE) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/src/fiber.cc.i
.PHONY : src/fiber.cc.i

src/fiber.s: src/fiber.cc.s

.PHONY : src/fiber.s

# target to generate assembly for a file
src/fiber.cc.s:
	$(MAKE) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/src/fiber.cc.s
.PHONY : src/fiber.cc.s

src/hook.o: src/hook.cc.o

.PHONY : src/hook.o

# target to build an object file
src/hook.cc.o:
	$(MAKE) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/src/hook.cc.o
.PHONY : src/hook.cc.o

src/hook.i: src/hook.cc.i

.PHONY : src/hook.i

# target to preprocess a source file
src/hook.cc.i:
	$(MAKE) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/src/hook.cc.i
.PHONY : src/hook.cc.i

src/hook.s: src/hook.cc.s

.PHONY : src/hook.s

# target to generate assembly for a file
src/hook.cc.s:
	$(MAKE) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/src/hook.cc.s
.PHONY : src/hook.cc.s

src/iomanager.o: src/iomanager.cc.o

.PHONY : src/iomanager.o

# target to build an object file
src/iomanager.cc.o:
	$(MAKE) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/src/iomanager.cc.o
.PHONY : src/iomanager.cc.o

src/iomanager.i: src/iomanager.cc.i

.PHONY : src/iomanager.i

# target to preprocess a source file
src/iomanager.cc.i:
	$(MAKE) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/src/iomanager.cc.i
.PHONY : src/iomanager.cc.i

src/iomanager.s: src/iomanager.cc.s

.PHONY : src/iomanager.s

# target to generate assembly for a file
src/iomanager.cc.s:
	$(MAKE) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/src/iomanager.cc.s
.PHONY : src/iomanager.cc.s

src/log.o: src/log.cc.o

.PHONY : src/log.o

# target to build an object file
src/log.cc.o:
	$(MAKE) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/src/log.cc.o
.PHONY : src/log.cc.o

src/log.i: src/log.cc.i

.PHONY : src/log.i

# target to preprocess a source file
src/log.cc.i:
	$(MAKE) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/src/log.cc.i
.PHONY : src/log.cc.i

src/log.s: src/log.cc.s

.PHONY : src/log.s

# target to generate assembly for a file
src/log.cc.s:
	$(MAKE) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/src/log.cc.s
.PHONY : src/log.cc.s

src/scheduler.o: src/scheduler.cc.o

.PHONY : src/scheduler.o

# target to build an object file
src/scheduler.cc.o:
	$(MAKE) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/src/scheduler.cc.o
.PHONY : src/scheduler.cc.o

src/scheduler.i: src/scheduler.cc.i

.PHONY : src/scheduler.i

# target to preprocess a source file
src/scheduler.cc.i:
	$(MAKE) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/src/scheduler.cc.i
.PHONY : src/scheduler.cc.i

src/scheduler.s: src/scheduler.cc.s

.PHONY : src/scheduler.s

# target to generate assembly for a file
src/scheduler.cc.s:
	$(MAKE) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/src/scheduler.cc.s
.PHONY : src/scheduler.cc.s

src/socket.o: src/socket.cc.o

.PHONY : src/socket.o

# target to build an object file
src/socket.cc.o:
	$(MAKE) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/src/socket.cc.o
.PHONY : src/socket.cc.o

src/socket.i: src/socket.cc.i

.PHONY : src/socket.i

# target to preprocess a source file
src/socket.cc.i:
	$(MAKE) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/src/socket.cc.i
.PHONY : src/socket.cc.i

src/socket.s: src/socket.cc.s

.PHONY : src/socket.s

# target to generate assembly for a file
src/socket.cc.s:
	$(MAKE) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/src/socket.cc.s
.PHONY : src/socket.cc.s

src/thread.o: src/thread.cc.o

.PHONY : src/thread.o

# target to build an object file
src/thread.cc.o:
	$(MAKE) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/src/thread.cc.o
.PHONY : src/thread.cc.o

src/thread.i: src/thread.cc.i

.PHONY : src/thread.i

# target to preprocess a source file
src/thread.cc.i:
	$(MAKE) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/src/thread.cc.i
.PHONY : src/thread.cc.i

src/thread.s: src/thread.cc.s

.PHONY : src/thread.s

# target to generate assembly for a file
src/thread.cc.s:
	$(MAKE) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/src/thread.cc.s
.PHONY : src/thread.cc.s

src/timer.o: src/timer.cc.o

.PHONY : src/timer.o

# target to build an object file
src/timer.cc.o:
	$(MAKE) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/src/timer.cc.o
.PHONY : src/timer.cc.o

src/timer.i: src/timer.cc.i

.PHONY : src/timer.i

# target to preprocess a source file
src/timer.cc.i:
	$(MAKE) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/src/timer.cc.i
.PHONY : src/timer.cc.i

src/timer.s: src/timer.cc.s

.PHONY : src/timer.s

# target to generate assembly for a file
src/timer.cc.s:
	$(MAKE) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/src/timer.cc.s
.PHONY : src/timer.cc.s

src/util.o: src/util.cc.o

.PHONY : src/util.o

# target to build an object file
src/util.cc.o:
	$(MAKE) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/src/util.cc.o
.PHONY : src/util.cc.o

src/util.i: src/util.cc.i

.PHONY : src/util.i

# target to preprocess a source file
src/util.cc.i:
	$(MAKE) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/src/util.cc.i
.PHONY : src/util.cc.i

src/util.s: src/util.cc.s

.PHONY : src/util.s

# target to generate assembly for a file
src/util.cc.s:
	$(MAKE) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/src/util.cc.s
.PHONY : src/util.cc.s

tests/test.o: tests/test.cc.o

.PHONY : tests/test.o

# target to build an object file
tests/test.cc.o:
	$(MAKE) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/tests/test.cc.o
.PHONY : tests/test.cc.o

tests/test.i: tests/test.cc.i

.PHONY : tests/test.i

# target to preprocess a source file
tests/test.cc.i:
	$(MAKE) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/tests/test.cc.i
.PHONY : tests/test.cc.i

tests/test.s: tests/test.cc.s

.PHONY : tests/test.s

# target to generate assembly for a file
tests/test.cc.s:
	$(MAKE) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/tests/test.cc.s
.PHONY : tests/test.cc.s

tests/test_address.o: tests/test_address.cc.o

.PHONY : tests/test_address.o

# target to build an object file
tests/test_address.cc.o:
	$(MAKE) -f CMakeFiles/test_address.dir/build.make CMakeFiles/test_address.dir/tests/test_address.cc.o
.PHONY : tests/test_address.cc.o

tests/test_address.i: tests/test_address.cc.i

.PHONY : tests/test_address.i

# target to preprocess a source file
tests/test_address.cc.i:
	$(MAKE) -f CMakeFiles/test_address.dir/build.make CMakeFiles/test_address.dir/tests/test_address.cc.i
.PHONY : tests/test_address.cc.i

tests/test_address.s: tests/test_address.cc.s

.PHONY : tests/test_address.s

# target to generate assembly for a file
tests/test_address.cc.s:
	$(MAKE) -f CMakeFiles/test_address.dir/build.make CMakeFiles/test_address.dir/tests/test_address.cc.s
.PHONY : tests/test_address.cc.s

tests/test_config.o: tests/test_config.cc.o

.PHONY : tests/test_config.o

# target to build an object file
tests/test_config.cc.o:
	$(MAKE) -f CMakeFiles/test_config.dir/build.make CMakeFiles/test_config.dir/tests/test_config.cc.o
.PHONY : tests/test_config.cc.o

tests/test_config.i: tests/test_config.cc.i

.PHONY : tests/test_config.i

# target to preprocess a source file
tests/test_config.cc.i:
	$(MAKE) -f CMakeFiles/test_config.dir/build.make CMakeFiles/test_config.dir/tests/test_config.cc.i
.PHONY : tests/test_config.cc.i

tests/test_config.s: tests/test_config.cc.s

.PHONY : tests/test_config.s

# target to generate assembly for a file
tests/test_config.cc.s:
	$(MAKE) -f CMakeFiles/test_config.dir/build.make CMakeFiles/test_config.dir/tests/test_config.cc.s
.PHONY : tests/test_config.cc.s

tests/test_fiber.o: tests/test_fiber.cc.o

.PHONY : tests/test_fiber.o

# target to build an object file
tests/test_fiber.cc.o:
	$(MAKE) -f CMakeFiles/test_fiber.dir/build.make CMakeFiles/test_fiber.dir/tests/test_fiber.cc.o
.PHONY : tests/test_fiber.cc.o

tests/test_fiber.i: tests/test_fiber.cc.i

.PHONY : tests/test_fiber.i

# target to preprocess a source file
tests/test_fiber.cc.i:
	$(MAKE) -f CMakeFiles/test_fiber.dir/build.make CMakeFiles/test_fiber.dir/tests/test_fiber.cc.i
.PHONY : tests/test_fiber.cc.i

tests/test_fiber.s: tests/test_fiber.cc.s

.PHONY : tests/test_fiber.s

# target to generate assembly for a file
tests/test_fiber.cc.s:
	$(MAKE) -f CMakeFiles/test_fiber.dir/build.make CMakeFiles/test_fiber.dir/tests/test_fiber.cc.s
.PHONY : tests/test_fiber.cc.s

tests/test_hook.o: tests/test_hook.cc.o

.PHONY : tests/test_hook.o

# target to build an object file
tests/test_hook.cc.o:
	$(MAKE) -f CMakeFiles/test_hook.dir/build.make CMakeFiles/test_hook.dir/tests/test_hook.cc.o
.PHONY : tests/test_hook.cc.o

tests/test_hook.i: tests/test_hook.cc.i

.PHONY : tests/test_hook.i

# target to preprocess a source file
tests/test_hook.cc.i:
	$(MAKE) -f CMakeFiles/test_hook.dir/build.make CMakeFiles/test_hook.dir/tests/test_hook.cc.i
.PHONY : tests/test_hook.cc.i

tests/test_hook.s: tests/test_hook.cc.s

.PHONY : tests/test_hook.s

# target to generate assembly for a file
tests/test_hook.cc.s:
	$(MAKE) -f CMakeFiles/test_hook.dir/build.make CMakeFiles/test_hook.dir/tests/test_hook.cc.s
.PHONY : tests/test_hook.cc.s

tests/test_iomanager.o: tests/test_iomanager.cc.o

.PHONY : tests/test_iomanager.o

# target to build an object file
tests/test_iomanager.cc.o:
	$(MAKE) -f CMakeFiles/test_iomanager.dir/build.make CMakeFiles/test_iomanager.dir/tests/test_iomanager.cc.o
.PHONY : tests/test_iomanager.cc.o

tests/test_iomanager.i: tests/test_iomanager.cc.i

.PHONY : tests/test_iomanager.i

# target to preprocess a source file
tests/test_iomanager.cc.i:
	$(MAKE) -f CMakeFiles/test_iomanager.dir/build.make CMakeFiles/test_iomanager.dir/tests/test_iomanager.cc.i
.PHONY : tests/test_iomanager.cc.i

tests/test_iomanager.s: tests/test_iomanager.cc.s

.PHONY : tests/test_iomanager.s

# target to generate assembly for a file
tests/test_iomanager.cc.s:
	$(MAKE) -f CMakeFiles/test_iomanager.dir/build.make CMakeFiles/test_iomanager.dir/tests/test_iomanager.cc.s
.PHONY : tests/test_iomanager.cc.s

tests/test_scheduler.o: tests/test_scheduler.cc.o

.PHONY : tests/test_scheduler.o

# target to build an object file
tests/test_scheduler.cc.o:
	$(MAKE) -f CMakeFiles/test_scheduler.dir/build.make CMakeFiles/test_scheduler.dir/tests/test_scheduler.cc.o
.PHONY : tests/test_scheduler.cc.o

tests/test_scheduler.i: tests/test_scheduler.cc.i

.PHONY : tests/test_scheduler.i

# target to preprocess a source file
tests/test_scheduler.cc.i:
	$(MAKE) -f CMakeFiles/test_scheduler.dir/build.make CMakeFiles/test_scheduler.dir/tests/test_scheduler.cc.i
.PHONY : tests/test_scheduler.cc.i

tests/test_scheduler.s: tests/test_scheduler.cc.s

.PHONY : tests/test_scheduler.s

# target to generate assembly for a file
tests/test_scheduler.cc.s:
	$(MAKE) -f CMakeFiles/test_scheduler.dir/build.make CMakeFiles/test_scheduler.dir/tests/test_scheduler.cc.s
.PHONY : tests/test_scheduler.cc.s

tests/test_socket.o: tests/test_socket.cc.o

.PHONY : tests/test_socket.o

# target to build an object file
tests/test_socket.cc.o:
	$(MAKE) -f CMakeFiles/test_socket.dir/build.make CMakeFiles/test_socket.dir/tests/test_socket.cc.o
.PHONY : tests/test_socket.cc.o

tests/test_socket.i: tests/test_socket.cc.i

.PHONY : tests/test_socket.i

# target to preprocess a source file
tests/test_socket.cc.i:
	$(MAKE) -f CMakeFiles/test_socket.dir/build.make CMakeFiles/test_socket.dir/tests/test_socket.cc.i
.PHONY : tests/test_socket.cc.i

tests/test_socket.s: tests/test_socket.cc.s

.PHONY : tests/test_socket.s

# target to generate assembly for a file
tests/test_socket.cc.s:
	$(MAKE) -f CMakeFiles/test_socket.dir/build.make CMakeFiles/test_socket.dir/tests/test_socket.cc.s
.PHONY : tests/test_socket.cc.s

tests/test_thread.o: tests/test_thread.cc.o

.PHONY : tests/test_thread.o

# target to build an object file
tests/test_thread.cc.o:
	$(MAKE) -f CMakeFiles/test_thread.dir/build.make CMakeFiles/test_thread.dir/tests/test_thread.cc.o
.PHONY : tests/test_thread.cc.o

tests/test_thread.i: tests/test_thread.cc.i

.PHONY : tests/test_thread.i

# target to preprocess a source file
tests/test_thread.cc.i:
	$(MAKE) -f CMakeFiles/test_thread.dir/build.make CMakeFiles/test_thread.dir/tests/test_thread.cc.i
.PHONY : tests/test_thread.cc.i

tests/test_thread.s: tests/test_thread.cc.s

.PHONY : tests/test_thread.s

# target to generate assembly for a file
tests/test_thread.cc.s:
	$(MAKE) -f CMakeFiles/test_thread.dir/build.make CMakeFiles/test_thread.dir/tests/test_thread.cc.s
.PHONY : tests/test_thread.cc.s

tests/test_util.o: tests/test_util.cc.o

.PHONY : tests/test_util.o

# target to build an object file
tests/test_util.cc.o:
	$(MAKE) -f CMakeFiles/test_util.dir/build.make CMakeFiles/test_util.dir/tests/test_util.cc.o
.PHONY : tests/test_util.cc.o

tests/test_util.i: tests/test_util.cc.i

.PHONY : tests/test_util.i

# target to preprocess a source file
tests/test_util.cc.i:
	$(MAKE) -f CMakeFiles/test_util.dir/build.make CMakeFiles/test_util.dir/tests/test_util.cc.i
.PHONY : tests/test_util.cc.i

tests/test_util.s: tests/test_util.cc.s

.PHONY : tests/test_util.s

# target to generate assembly for a file
tests/test_util.cc.s:
	$(MAKE) -f CMakeFiles/test_util.dir/build.make CMakeFiles/test_util.dir/tests/test_util.cc.s
.PHONY : tests/test_util.cc.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... edit_cache"
	@echo "... test_address"
	@echo "... test_hook"
	@echo "... test_iomanager"
	@echo "... test_scheduler"
	@echo "... test"
	@echo "... sylar"
	@echo "... test_config"
	@echo "... test_thread"
	@echo "... test_util"
	@echo "... test_socket"
	@echo "... test_fiber"
	@echo "... src/address.o"
	@echo "... src/address.i"
	@echo "... src/address.s"
	@echo "... src/bytearray.o"
	@echo "... src/bytearray.i"
	@echo "... src/bytearray.s"
	@echo "... src/config.o"
	@echo "... src/config.i"
	@echo "... src/config.s"
	@echo "... src/fd_manager.o"
	@echo "... src/fd_manager.i"
	@echo "... src/fd_manager.s"
	@echo "... src/fiber.o"
	@echo "... src/fiber.i"
	@echo "... src/fiber.s"
	@echo "... src/hook.o"
	@echo "... src/hook.i"
	@echo "... src/hook.s"
	@echo "... src/iomanager.o"
	@echo "... src/iomanager.i"
	@echo "... src/iomanager.s"
	@echo "... src/log.o"
	@echo "... src/log.i"
	@echo "... src/log.s"
	@echo "... src/scheduler.o"
	@echo "... src/scheduler.i"
	@echo "... src/scheduler.s"
	@echo "... src/socket.o"
	@echo "... src/socket.i"
	@echo "... src/socket.s"
	@echo "... src/thread.o"
	@echo "... src/thread.i"
	@echo "... src/thread.s"
	@echo "... src/timer.o"
	@echo "... src/timer.i"
	@echo "... src/timer.s"
	@echo "... src/util.o"
	@echo "... src/util.i"
	@echo "... src/util.s"
	@echo "... tests/test.o"
	@echo "... tests/test.i"
	@echo "... tests/test.s"
	@echo "... tests/test_address.o"
	@echo "... tests/test_address.i"
	@echo "... tests/test_address.s"
	@echo "... tests/test_config.o"
	@echo "... tests/test_config.i"
	@echo "... tests/test_config.s"
	@echo "... tests/test_fiber.o"
	@echo "... tests/test_fiber.i"
	@echo "... tests/test_fiber.s"
	@echo "... tests/test_hook.o"
	@echo "... tests/test_hook.i"
	@echo "... tests/test_hook.s"
	@echo "... tests/test_iomanager.o"
	@echo "... tests/test_iomanager.i"
	@echo "... tests/test_iomanager.s"
	@echo "... tests/test_scheduler.o"
	@echo "... tests/test_scheduler.i"
	@echo "... tests/test_scheduler.s"
	@echo "... tests/test_socket.o"
	@echo "... tests/test_socket.i"
	@echo "... tests/test_socket.s"
	@echo "... tests/test_thread.o"
	@echo "... tests/test_thread.i"
	@echo "... tests/test_thread.s"
	@echo "... tests/test_util.o"
	@echo "... tests/test_util.i"
	@echo "... tests/test_util.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

