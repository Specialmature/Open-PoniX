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
CMAKE_SOURCE_DIR = /source/clients/freerdp-git-11032013

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /source/clients/freerdp-git-11032013

# Include any dependencies generated for this target.
include winpr/libwinpr/error/CMakeFiles/winpr-error.dir/depend.make

# Include the progress variables for this target.
include winpr/libwinpr/error/CMakeFiles/winpr-error.dir/progress.make

# Include the compile flags for this target's objects.
include winpr/libwinpr/error/CMakeFiles/winpr-error.dir/flags.make

winpr/libwinpr/error/CMakeFiles/winpr-error.dir/error.c.o: winpr/libwinpr/error/CMakeFiles/winpr-error.dir/flags.make
winpr/libwinpr/error/CMakeFiles/winpr-error.dir/error.c.o: winpr/libwinpr/error/error.c
	$(CMAKE_COMMAND) -E cmake_progress_report /source/clients/freerdp-git-11032013/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object winpr/libwinpr/error/CMakeFiles/winpr-error.dir/error.c.o"
	cd /source/clients/freerdp-git-11032013/winpr/libwinpr/error && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/winpr-error.dir/error.c.o   -c /source/clients/freerdp-git-11032013/winpr/libwinpr/error/error.c

winpr/libwinpr/error/CMakeFiles/winpr-error.dir/error.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/winpr-error.dir/error.c.i"
	cd /source/clients/freerdp-git-11032013/winpr/libwinpr/error && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -E /source/clients/freerdp-git-11032013/winpr/libwinpr/error/error.c > CMakeFiles/winpr-error.dir/error.c.i

winpr/libwinpr/error/CMakeFiles/winpr-error.dir/error.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/winpr-error.dir/error.c.s"
	cd /source/clients/freerdp-git-11032013/winpr/libwinpr/error && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -S /source/clients/freerdp-git-11032013/winpr/libwinpr/error/error.c -o CMakeFiles/winpr-error.dir/error.c.s

winpr/libwinpr/error/CMakeFiles/winpr-error.dir/error.c.o.requires:
.PHONY : winpr/libwinpr/error/CMakeFiles/winpr-error.dir/error.c.o.requires

winpr/libwinpr/error/CMakeFiles/winpr-error.dir/error.c.o.provides: winpr/libwinpr/error/CMakeFiles/winpr-error.dir/error.c.o.requires
	$(MAKE) -f winpr/libwinpr/error/CMakeFiles/winpr-error.dir/build.make winpr/libwinpr/error/CMakeFiles/winpr-error.dir/error.c.o.provides.build
.PHONY : winpr/libwinpr/error/CMakeFiles/winpr-error.dir/error.c.o.provides

winpr/libwinpr/error/CMakeFiles/winpr-error.dir/error.c.o.provides.build: winpr/libwinpr/error/CMakeFiles/winpr-error.dir/error.c.o

winpr-error: winpr/libwinpr/error/CMakeFiles/winpr-error.dir/error.c.o
winpr-error: winpr/libwinpr/error/CMakeFiles/winpr-error.dir/build.make
.PHONY : winpr-error

# Rule to build all files generated by this target.
winpr/libwinpr/error/CMakeFiles/winpr-error.dir/build: winpr-error
.PHONY : winpr/libwinpr/error/CMakeFiles/winpr-error.dir/build

winpr/libwinpr/error/CMakeFiles/winpr-error.dir/requires: winpr/libwinpr/error/CMakeFiles/winpr-error.dir/error.c.o.requires
.PHONY : winpr/libwinpr/error/CMakeFiles/winpr-error.dir/requires

winpr/libwinpr/error/CMakeFiles/winpr-error.dir/clean:
	cd /source/clients/freerdp-git-11032013/winpr/libwinpr/error && $(CMAKE_COMMAND) -P CMakeFiles/winpr-error.dir/cmake_clean.cmake
.PHONY : winpr/libwinpr/error/CMakeFiles/winpr-error.dir/clean

winpr/libwinpr/error/CMakeFiles/winpr-error.dir/depend:
	cd /source/clients/freerdp-git-11032013 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /source/clients/freerdp-git-11032013 /source/clients/freerdp-git-11032013/winpr/libwinpr/error /source/clients/freerdp-git-11032013 /source/clients/freerdp-git-11032013/winpr/libwinpr/error /source/clients/freerdp-git-11032013/winpr/libwinpr/error/CMakeFiles/winpr-error.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : winpr/libwinpr/error/CMakeFiles/winpr-error.dir/depend

