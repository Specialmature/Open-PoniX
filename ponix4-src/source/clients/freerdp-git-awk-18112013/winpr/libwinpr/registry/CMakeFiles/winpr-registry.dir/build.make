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
CMAKE_SOURCE_DIR = /source/clients/freerdp-git-awk-18112013

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /source/clients/freerdp-git-awk-18112013

# Include any dependencies generated for this target.
include winpr/libwinpr/registry/CMakeFiles/winpr-registry.dir/depend.make

# Include the progress variables for this target.
include winpr/libwinpr/registry/CMakeFiles/winpr-registry.dir/progress.make

# Include the compile flags for this target's objects.
include winpr/libwinpr/registry/CMakeFiles/winpr-registry.dir/flags.make

winpr/libwinpr/registry/CMakeFiles/winpr-registry.dir/registry_reg.c.o: winpr/libwinpr/registry/CMakeFiles/winpr-registry.dir/flags.make
winpr/libwinpr/registry/CMakeFiles/winpr-registry.dir/registry_reg.c.o: winpr/libwinpr/registry/registry_reg.c
	$(CMAKE_COMMAND) -E cmake_progress_report /source/clients/freerdp-git-awk-18112013/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object winpr/libwinpr/registry/CMakeFiles/winpr-registry.dir/registry_reg.c.o"
	cd /source/clients/freerdp-git-awk-18112013/winpr/libwinpr/registry && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/winpr-registry.dir/registry_reg.c.o   -c /source/clients/freerdp-git-awk-18112013/winpr/libwinpr/registry/registry_reg.c

winpr/libwinpr/registry/CMakeFiles/winpr-registry.dir/registry_reg.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/winpr-registry.dir/registry_reg.c.i"
	cd /source/clients/freerdp-git-awk-18112013/winpr/libwinpr/registry && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -E /source/clients/freerdp-git-awk-18112013/winpr/libwinpr/registry/registry_reg.c > CMakeFiles/winpr-registry.dir/registry_reg.c.i

winpr/libwinpr/registry/CMakeFiles/winpr-registry.dir/registry_reg.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/winpr-registry.dir/registry_reg.c.s"
	cd /source/clients/freerdp-git-awk-18112013/winpr/libwinpr/registry && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -S /source/clients/freerdp-git-awk-18112013/winpr/libwinpr/registry/registry_reg.c -o CMakeFiles/winpr-registry.dir/registry_reg.c.s

winpr/libwinpr/registry/CMakeFiles/winpr-registry.dir/registry_reg.c.o.requires:
.PHONY : winpr/libwinpr/registry/CMakeFiles/winpr-registry.dir/registry_reg.c.o.requires

winpr/libwinpr/registry/CMakeFiles/winpr-registry.dir/registry_reg.c.o.provides: winpr/libwinpr/registry/CMakeFiles/winpr-registry.dir/registry_reg.c.o.requires
	$(MAKE) -f winpr/libwinpr/registry/CMakeFiles/winpr-registry.dir/build.make winpr/libwinpr/registry/CMakeFiles/winpr-registry.dir/registry_reg.c.o.provides.build
.PHONY : winpr/libwinpr/registry/CMakeFiles/winpr-registry.dir/registry_reg.c.o.provides

winpr/libwinpr/registry/CMakeFiles/winpr-registry.dir/registry_reg.c.o.provides.build: winpr/libwinpr/registry/CMakeFiles/winpr-registry.dir/registry_reg.c.o

winpr/libwinpr/registry/CMakeFiles/winpr-registry.dir/registry.c.o: winpr/libwinpr/registry/CMakeFiles/winpr-registry.dir/flags.make
winpr/libwinpr/registry/CMakeFiles/winpr-registry.dir/registry.c.o: winpr/libwinpr/registry/registry.c
	$(CMAKE_COMMAND) -E cmake_progress_report /source/clients/freerdp-git-awk-18112013/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object winpr/libwinpr/registry/CMakeFiles/winpr-registry.dir/registry.c.o"
	cd /source/clients/freerdp-git-awk-18112013/winpr/libwinpr/registry && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/winpr-registry.dir/registry.c.o   -c /source/clients/freerdp-git-awk-18112013/winpr/libwinpr/registry/registry.c

winpr/libwinpr/registry/CMakeFiles/winpr-registry.dir/registry.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/winpr-registry.dir/registry.c.i"
	cd /source/clients/freerdp-git-awk-18112013/winpr/libwinpr/registry && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -E /source/clients/freerdp-git-awk-18112013/winpr/libwinpr/registry/registry.c > CMakeFiles/winpr-registry.dir/registry.c.i

winpr/libwinpr/registry/CMakeFiles/winpr-registry.dir/registry.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/winpr-registry.dir/registry.c.s"
	cd /source/clients/freerdp-git-awk-18112013/winpr/libwinpr/registry && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -S /source/clients/freerdp-git-awk-18112013/winpr/libwinpr/registry/registry.c -o CMakeFiles/winpr-registry.dir/registry.c.s

winpr/libwinpr/registry/CMakeFiles/winpr-registry.dir/registry.c.o.requires:
.PHONY : winpr/libwinpr/registry/CMakeFiles/winpr-registry.dir/registry.c.o.requires

winpr/libwinpr/registry/CMakeFiles/winpr-registry.dir/registry.c.o.provides: winpr/libwinpr/registry/CMakeFiles/winpr-registry.dir/registry.c.o.requires
	$(MAKE) -f winpr/libwinpr/registry/CMakeFiles/winpr-registry.dir/build.make winpr/libwinpr/registry/CMakeFiles/winpr-registry.dir/registry.c.o.provides.build
.PHONY : winpr/libwinpr/registry/CMakeFiles/winpr-registry.dir/registry.c.o.provides

winpr/libwinpr/registry/CMakeFiles/winpr-registry.dir/registry.c.o.provides.build: winpr/libwinpr/registry/CMakeFiles/winpr-registry.dir/registry.c.o

winpr-registry: winpr/libwinpr/registry/CMakeFiles/winpr-registry.dir/registry_reg.c.o
winpr-registry: winpr/libwinpr/registry/CMakeFiles/winpr-registry.dir/registry.c.o
winpr-registry: winpr/libwinpr/registry/CMakeFiles/winpr-registry.dir/build.make
.PHONY : winpr-registry

# Rule to build all files generated by this target.
winpr/libwinpr/registry/CMakeFiles/winpr-registry.dir/build: winpr-registry
.PHONY : winpr/libwinpr/registry/CMakeFiles/winpr-registry.dir/build

winpr/libwinpr/registry/CMakeFiles/winpr-registry.dir/requires: winpr/libwinpr/registry/CMakeFiles/winpr-registry.dir/registry_reg.c.o.requires
winpr/libwinpr/registry/CMakeFiles/winpr-registry.dir/requires: winpr/libwinpr/registry/CMakeFiles/winpr-registry.dir/registry.c.o.requires
.PHONY : winpr/libwinpr/registry/CMakeFiles/winpr-registry.dir/requires

winpr/libwinpr/registry/CMakeFiles/winpr-registry.dir/clean:
	cd /source/clients/freerdp-git-awk-18112013/winpr/libwinpr/registry && $(CMAKE_COMMAND) -P CMakeFiles/winpr-registry.dir/cmake_clean.cmake
.PHONY : winpr/libwinpr/registry/CMakeFiles/winpr-registry.dir/clean

winpr/libwinpr/registry/CMakeFiles/winpr-registry.dir/depend:
	cd /source/clients/freerdp-git-awk-18112013 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /source/clients/freerdp-git-awk-18112013 /source/clients/freerdp-git-awk-18112013/winpr/libwinpr/registry /source/clients/freerdp-git-awk-18112013 /source/clients/freerdp-git-awk-18112013/winpr/libwinpr/registry /source/clients/freerdp-git-awk-18112013/winpr/libwinpr/registry/CMakeFiles/winpr-registry.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : winpr/libwinpr/registry/CMakeFiles/winpr-registry.dir/depend

