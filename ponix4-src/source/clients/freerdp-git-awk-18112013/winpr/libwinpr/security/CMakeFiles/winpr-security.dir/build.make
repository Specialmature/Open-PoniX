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
include winpr/libwinpr/security/CMakeFiles/winpr-security.dir/depend.make

# Include the progress variables for this target.
include winpr/libwinpr/security/CMakeFiles/winpr-security.dir/progress.make

# Include the compile flags for this target's objects.
include winpr/libwinpr/security/CMakeFiles/winpr-security.dir/flags.make

winpr/libwinpr/security/CMakeFiles/winpr-security.dir/security.c.o: winpr/libwinpr/security/CMakeFiles/winpr-security.dir/flags.make
winpr/libwinpr/security/CMakeFiles/winpr-security.dir/security.c.o: winpr/libwinpr/security/security.c
	$(CMAKE_COMMAND) -E cmake_progress_report /source/clients/freerdp-git-awk-18112013/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object winpr/libwinpr/security/CMakeFiles/winpr-security.dir/security.c.o"
	cd /source/clients/freerdp-git-awk-18112013/winpr/libwinpr/security && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/winpr-security.dir/security.c.o   -c /source/clients/freerdp-git-awk-18112013/winpr/libwinpr/security/security.c

winpr/libwinpr/security/CMakeFiles/winpr-security.dir/security.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/winpr-security.dir/security.c.i"
	cd /source/clients/freerdp-git-awk-18112013/winpr/libwinpr/security && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -E /source/clients/freerdp-git-awk-18112013/winpr/libwinpr/security/security.c > CMakeFiles/winpr-security.dir/security.c.i

winpr/libwinpr/security/CMakeFiles/winpr-security.dir/security.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/winpr-security.dir/security.c.s"
	cd /source/clients/freerdp-git-awk-18112013/winpr/libwinpr/security && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -S /source/clients/freerdp-git-awk-18112013/winpr/libwinpr/security/security.c -o CMakeFiles/winpr-security.dir/security.c.s

winpr/libwinpr/security/CMakeFiles/winpr-security.dir/security.c.o.requires:
.PHONY : winpr/libwinpr/security/CMakeFiles/winpr-security.dir/security.c.o.requires

winpr/libwinpr/security/CMakeFiles/winpr-security.dir/security.c.o.provides: winpr/libwinpr/security/CMakeFiles/winpr-security.dir/security.c.o.requires
	$(MAKE) -f winpr/libwinpr/security/CMakeFiles/winpr-security.dir/build.make winpr/libwinpr/security/CMakeFiles/winpr-security.dir/security.c.o.provides.build
.PHONY : winpr/libwinpr/security/CMakeFiles/winpr-security.dir/security.c.o.provides

winpr/libwinpr/security/CMakeFiles/winpr-security.dir/security.c.o.provides.build: winpr/libwinpr/security/CMakeFiles/winpr-security.dir/security.c.o

winpr-security: winpr/libwinpr/security/CMakeFiles/winpr-security.dir/security.c.o
winpr-security: winpr/libwinpr/security/CMakeFiles/winpr-security.dir/build.make
.PHONY : winpr-security

# Rule to build all files generated by this target.
winpr/libwinpr/security/CMakeFiles/winpr-security.dir/build: winpr-security
.PHONY : winpr/libwinpr/security/CMakeFiles/winpr-security.dir/build

winpr/libwinpr/security/CMakeFiles/winpr-security.dir/requires: winpr/libwinpr/security/CMakeFiles/winpr-security.dir/security.c.o.requires
.PHONY : winpr/libwinpr/security/CMakeFiles/winpr-security.dir/requires

winpr/libwinpr/security/CMakeFiles/winpr-security.dir/clean:
	cd /source/clients/freerdp-git-awk-18112013/winpr/libwinpr/security && $(CMAKE_COMMAND) -P CMakeFiles/winpr-security.dir/cmake_clean.cmake
.PHONY : winpr/libwinpr/security/CMakeFiles/winpr-security.dir/clean

winpr/libwinpr/security/CMakeFiles/winpr-security.dir/depend:
	cd /source/clients/freerdp-git-awk-18112013 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /source/clients/freerdp-git-awk-18112013 /source/clients/freerdp-git-awk-18112013/winpr/libwinpr/security /source/clients/freerdp-git-awk-18112013 /source/clients/freerdp-git-awk-18112013/winpr/libwinpr/security /source/clients/freerdp-git-awk-18112013/winpr/libwinpr/security/CMakeFiles/winpr-security.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : winpr/libwinpr/security/CMakeFiles/winpr-security.dir/depend

