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
CMAKE_SOURCE_DIR = /source/clients/freerdp-git-11032013-bmiklautz-numpadpatch

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /source/clients/freerdp-git-11032013-bmiklautz-numpadpatch

# Include any dependencies generated for this target.
include winpr/libwinpr/path/CMakeFiles/winpr-path.dir/depend.make

# Include the progress variables for this target.
include winpr/libwinpr/path/CMakeFiles/winpr-path.dir/progress.make

# Include the compile flags for this target's objects.
include winpr/libwinpr/path/CMakeFiles/winpr-path.dir/flags.make

winpr/libwinpr/path/CMakeFiles/winpr-path.dir/path.c.o: winpr/libwinpr/path/CMakeFiles/winpr-path.dir/flags.make
winpr/libwinpr/path/CMakeFiles/winpr-path.dir/path.c.o: winpr/libwinpr/path/path.c
	$(CMAKE_COMMAND) -E cmake_progress_report /source/clients/freerdp-git-11032013-bmiklautz-numpadpatch/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object winpr/libwinpr/path/CMakeFiles/winpr-path.dir/path.c.o"
	cd /source/clients/freerdp-git-11032013-bmiklautz-numpadpatch/winpr/libwinpr/path && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/winpr-path.dir/path.c.o   -c /source/clients/freerdp-git-11032013-bmiklautz-numpadpatch/winpr/libwinpr/path/path.c

winpr/libwinpr/path/CMakeFiles/winpr-path.dir/path.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/winpr-path.dir/path.c.i"
	cd /source/clients/freerdp-git-11032013-bmiklautz-numpadpatch/winpr/libwinpr/path && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -E /source/clients/freerdp-git-11032013-bmiklautz-numpadpatch/winpr/libwinpr/path/path.c > CMakeFiles/winpr-path.dir/path.c.i

winpr/libwinpr/path/CMakeFiles/winpr-path.dir/path.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/winpr-path.dir/path.c.s"
	cd /source/clients/freerdp-git-11032013-bmiklautz-numpadpatch/winpr/libwinpr/path && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -S /source/clients/freerdp-git-11032013-bmiklautz-numpadpatch/winpr/libwinpr/path/path.c -o CMakeFiles/winpr-path.dir/path.c.s

winpr/libwinpr/path/CMakeFiles/winpr-path.dir/path.c.o.requires:
.PHONY : winpr/libwinpr/path/CMakeFiles/winpr-path.dir/path.c.o.requires

winpr/libwinpr/path/CMakeFiles/winpr-path.dir/path.c.o.provides: winpr/libwinpr/path/CMakeFiles/winpr-path.dir/path.c.o.requires
	$(MAKE) -f winpr/libwinpr/path/CMakeFiles/winpr-path.dir/build.make winpr/libwinpr/path/CMakeFiles/winpr-path.dir/path.c.o.provides.build
.PHONY : winpr/libwinpr/path/CMakeFiles/winpr-path.dir/path.c.o.provides

winpr/libwinpr/path/CMakeFiles/winpr-path.dir/path.c.o.provides.build: winpr/libwinpr/path/CMakeFiles/winpr-path.dir/path.c.o

# Object files for target winpr-path
winpr__path_OBJECTS = \
"CMakeFiles/winpr-path.dir/path.c.o"

# External object files for target winpr-path
winpr__path_EXTERNAL_OBJECTS =

winpr/libwinpr/path/libwinpr-path.so.0.1.0: winpr/libwinpr/path/CMakeFiles/winpr-path.dir/path.c.o
winpr/libwinpr/path/libwinpr-path.so.0.1.0: winpr/libwinpr/path/CMakeFiles/winpr-path.dir/build.make
winpr/libwinpr/path/libwinpr-path.so.0.1.0: winpr/libwinpr/crt/libwinpr-crt.so.0.1.0
winpr/libwinpr/path/libwinpr-path.so.0.1.0: winpr/libwinpr/heap/libwinpr-heap.so.0.1.0
winpr/libwinpr/path/libwinpr-path.so.0.1.0: winpr/libwinpr/path/CMakeFiles/winpr-path.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C shared library libwinpr-path.so"
	cd /source/clients/freerdp-git-11032013-bmiklautz-numpadpatch/winpr/libwinpr/path && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/winpr-path.dir/link.txt --verbose=$(VERBOSE)
	cd /source/clients/freerdp-git-11032013-bmiklautz-numpadpatch/winpr/libwinpr/path && $(CMAKE_COMMAND) -E cmake_symlink_library libwinpr-path.so.0.1.0 libwinpr-path.so.0.1 libwinpr-path.so

winpr/libwinpr/path/libwinpr-path.so.0.1: winpr/libwinpr/path/libwinpr-path.so.0.1.0

winpr/libwinpr/path/libwinpr-path.so: winpr/libwinpr/path/libwinpr-path.so.0.1.0

# Rule to build all files generated by this target.
winpr/libwinpr/path/CMakeFiles/winpr-path.dir/build: winpr/libwinpr/path/libwinpr-path.so
.PHONY : winpr/libwinpr/path/CMakeFiles/winpr-path.dir/build

winpr/libwinpr/path/CMakeFiles/winpr-path.dir/requires: winpr/libwinpr/path/CMakeFiles/winpr-path.dir/path.c.o.requires
.PHONY : winpr/libwinpr/path/CMakeFiles/winpr-path.dir/requires

winpr/libwinpr/path/CMakeFiles/winpr-path.dir/clean:
	cd /source/clients/freerdp-git-11032013-bmiklautz-numpadpatch/winpr/libwinpr/path && $(CMAKE_COMMAND) -P CMakeFiles/winpr-path.dir/cmake_clean.cmake
.PHONY : winpr/libwinpr/path/CMakeFiles/winpr-path.dir/clean

winpr/libwinpr/path/CMakeFiles/winpr-path.dir/depend:
	cd /source/clients/freerdp-git-11032013-bmiklautz-numpadpatch && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /source/clients/freerdp-git-11032013-bmiklautz-numpadpatch /source/clients/freerdp-git-11032013-bmiklautz-numpadpatch/winpr/libwinpr/path /source/clients/freerdp-git-11032013-bmiklautz-numpadpatch /source/clients/freerdp-git-11032013-bmiklautz-numpadpatch/winpr/libwinpr/path /source/clients/freerdp-git-11032013-bmiklautz-numpadpatch/winpr/libwinpr/path/CMakeFiles/winpr-path.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : winpr/libwinpr/path/CMakeFiles/winpr-path.dir/depend

