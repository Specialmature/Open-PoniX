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
CMAKE_SOURCE_DIR = /source/clients/FreeRDP-1.1.0-beta1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /source/clients/FreeRDP-1.1.0-beta1

# Include any dependencies generated for this target.
include libfreerdp/rail/CMakeFiles/freerdp-rail.dir/depend.make

# Include the progress variables for this target.
include libfreerdp/rail/CMakeFiles/freerdp-rail.dir/progress.make

# Include the compile flags for this target's objects.
include libfreerdp/rail/CMakeFiles/freerdp-rail.dir/flags.make

libfreerdp/rail/CMakeFiles/freerdp-rail.dir/window_list.c.o: libfreerdp/rail/CMakeFiles/freerdp-rail.dir/flags.make
libfreerdp/rail/CMakeFiles/freerdp-rail.dir/window_list.c.o: libfreerdp/rail/window_list.c
	$(CMAKE_COMMAND) -E cmake_progress_report /source/clients/FreeRDP-1.1.0-beta1/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object libfreerdp/rail/CMakeFiles/freerdp-rail.dir/window_list.c.o"
	cd /source/clients/FreeRDP-1.1.0-beta1/libfreerdp/rail && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/freerdp-rail.dir/window_list.c.o   -c /source/clients/FreeRDP-1.1.0-beta1/libfreerdp/rail/window_list.c

libfreerdp/rail/CMakeFiles/freerdp-rail.dir/window_list.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/freerdp-rail.dir/window_list.c.i"
	cd /source/clients/FreeRDP-1.1.0-beta1/libfreerdp/rail && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -E /source/clients/FreeRDP-1.1.0-beta1/libfreerdp/rail/window_list.c > CMakeFiles/freerdp-rail.dir/window_list.c.i

libfreerdp/rail/CMakeFiles/freerdp-rail.dir/window_list.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/freerdp-rail.dir/window_list.c.s"
	cd /source/clients/FreeRDP-1.1.0-beta1/libfreerdp/rail && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -S /source/clients/FreeRDP-1.1.0-beta1/libfreerdp/rail/window_list.c -o CMakeFiles/freerdp-rail.dir/window_list.c.s

libfreerdp/rail/CMakeFiles/freerdp-rail.dir/window_list.c.o.requires:
.PHONY : libfreerdp/rail/CMakeFiles/freerdp-rail.dir/window_list.c.o.requires

libfreerdp/rail/CMakeFiles/freerdp-rail.dir/window_list.c.o.provides: libfreerdp/rail/CMakeFiles/freerdp-rail.dir/window_list.c.o.requires
	$(MAKE) -f libfreerdp/rail/CMakeFiles/freerdp-rail.dir/build.make libfreerdp/rail/CMakeFiles/freerdp-rail.dir/window_list.c.o.provides.build
.PHONY : libfreerdp/rail/CMakeFiles/freerdp-rail.dir/window_list.c.o.provides

libfreerdp/rail/CMakeFiles/freerdp-rail.dir/window_list.c.o.provides.build: libfreerdp/rail/CMakeFiles/freerdp-rail.dir/window_list.c.o

libfreerdp/rail/CMakeFiles/freerdp-rail.dir/window.c.o: libfreerdp/rail/CMakeFiles/freerdp-rail.dir/flags.make
libfreerdp/rail/CMakeFiles/freerdp-rail.dir/window.c.o: libfreerdp/rail/window.c
	$(CMAKE_COMMAND) -E cmake_progress_report /source/clients/FreeRDP-1.1.0-beta1/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object libfreerdp/rail/CMakeFiles/freerdp-rail.dir/window.c.o"
	cd /source/clients/FreeRDP-1.1.0-beta1/libfreerdp/rail && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/freerdp-rail.dir/window.c.o   -c /source/clients/FreeRDP-1.1.0-beta1/libfreerdp/rail/window.c

libfreerdp/rail/CMakeFiles/freerdp-rail.dir/window.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/freerdp-rail.dir/window.c.i"
	cd /source/clients/FreeRDP-1.1.0-beta1/libfreerdp/rail && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -E /source/clients/FreeRDP-1.1.0-beta1/libfreerdp/rail/window.c > CMakeFiles/freerdp-rail.dir/window.c.i

libfreerdp/rail/CMakeFiles/freerdp-rail.dir/window.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/freerdp-rail.dir/window.c.s"
	cd /source/clients/FreeRDP-1.1.0-beta1/libfreerdp/rail && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -S /source/clients/FreeRDP-1.1.0-beta1/libfreerdp/rail/window.c -o CMakeFiles/freerdp-rail.dir/window.c.s

libfreerdp/rail/CMakeFiles/freerdp-rail.dir/window.c.o.requires:
.PHONY : libfreerdp/rail/CMakeFiles/freerdp-rail.dir/window.c.o.requires

libfreerdp/rail/CMakeFiles/freerdp-rail.dir/window.c.o.provides: libfreerdp/rail/CMakeFiles/freerdp-rail.dir/window.c.o.requires
	$(MAKE) -f libfreerdp/rail/CMakeFiles/freerdp-rail.dir/build.make libfreerdp/rail/CMakeFiles/freerdp-rail.dir/window.c.o.provides.build
.PHONY : libfreerdp/rail/CMakeFiles/freerdp-rail.dir/window.c.o.provides

libfreerdp/rail/CMakeFiles/freerdp-rail.dir/window.c.o.provides.build: libfreerdp/rail/CMakeFiles/freerdp-rail.dir/window.c.o

libfreerdp/rail/CMakeFiles/freerdp-rail.dir/icon.c.o: libfreerdp/rail/CMakeFiles/freerdp-rail.dir/flags.make
libfreerdp/rail/CMakeFiles/freerdp-rail.dir/icon.c.o: libfreerdp/rail/icon.c
	$(CMAKE_COMMAND) -E cmake_progress_report /source/clients/FreeRDP-1.1.0-beta1/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object libfreerdp/rail/CMakeFiles/freerdp-rail.dir/icon.c.o"
	cd /source/clients/FreeRDP-1.1.0-beta1/libfreerdp/rail && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/freerdp-rail.dir/icon.c.o   -c /source/clients/FreeRDP-1.1.0-beta1/libfreerdp/rail/icon.c

libfreerdp/rail/CMakeFiles/freerdp-rail.dir/icon.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/freerdp-rail.dir/icon.c.i"
	cd /source/clients/FreeRDP-1.1.0-beta1/libfreerdp/rail && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -E /source/clients/FreeRDP-1.1.0-beta1/libfreerdp/rail/icon.c > CMakeFiles/freerdp-rail.dir/icon.c.i

libfreerdp/rail/CMakeFiles/freerdp-rail.dir/icon.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/freerdp-rail.dir/icon.c.s"
	cd /source/clients/FreeRDP-1.1.0-beta1/libfreerdp/rail && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -S /source/clients/FreeRDP-1.1.0-beta1/libfreerdp/rail/icon.c -o CMakeFiles/freerdp-rail.dir/icon.c.s

libfreerdp/rail/CMakeFiles/freerdp-rail.dir/icon.c.o.requires:
.PHONY : libfreerdp/rail/CMakeFiles/freerdp-rail.dir/icon.c.o.requires

libfreerdp/rail/CMakeFiles/freerdp-rail.dir/icon.c.o.provides: libfreerdp/rail/CMakeFiles/freerdp-rail.dir/icon.c.o.requires
	$(MAKE) -f libfreerdp/rail/CMakeFiles/freerdp-rail.dir/build.make libfreerdp/rail/CMakeFiles/freerdp-rail.dir/icon.c.o.provides.build
.PHONY : libfreerdp/rail/CMakeFiles/freerdp-rail.dir/icon.c.o.provides

libfreerdp/rail/CMakeFiles/freerdp-rail.dir/icon.c.o.provides.build: libfreerdp/rail/CMakeFiles/freerdp-rail.dir/icon.c.o

libfreerdp/rail/CMakeFiles/freerdp-rail.dir/rail.c.o: libfreerdp/rail/CMakeFiles/freerdp-rail.dir/flags.make
libfreerdp/rail/CMakeFiles/freerdp-rail.dir/rail.c.o: libfreerdp/rail/rail.c
	$(CMAKE_COMMAND) -E cmake_progress_report /source/clients/FreeRDP-1.1.0-beta1/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object libfreerdp/rail/CMakeFiles/freerdp-rail.dir/rail.c.o"
	cd /source/clients/FreeRDP-1.1.0-beta1/libfreerdp/rail && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/freerdp-rail.dir/rail.c.o   -c /source/clients/FreeRDP-1.1.0-beta1/libfreerdp/rail/rail.c

libfreerdp/rail/CMakeFiles/freerdp-rail.dir/rail.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/freerdp-rail.dir/rail.c.i"
	cd /source/clients/FreeRDP-1.1.0-beta1/libfreerdp/rail && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -E /source/clients/FreeRDP-1.1.0-beta1/libfreerdp/rail/rail.c > CMakeFiles/freerdp-rail.dir/rail.c.i

libfreerdp/rail/CMakeFiles/freerdp-rail.dir/rail.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/freerdp-rail.dir/rail.c.s"
	cd /source/clients/FreeRDP-1.1.0-beta1/libfreerdp/rail && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -S /source/clients/FreeRDP-1.1.0-beta1/libfreerdp/rail/rail.c -o CMakeFiles/freerdp-rail.dir/rail.c.s

libfreerdp/rail/CMakeFiles/freerdp-rail.dir/rail.c.o.requires:
.PHONY : libfreerdp/rail/CMakeFiles/freerdp-rail.dir/rail.c.o.requires

libfreerdp/rail/CMakeFiles/freerdp-rail.dir/rail.c.o.provides: libfreerdp/rail/CMakeFiles/freerdp-rail.dir/rail.c.o.requires
	$(MAKE) -f libfreerdp/rail/CMakeFiles/freerdp-rail.dir/build.make libfreerdp/rail/CMakeFiles/freerdp-rail.dir/rail.c.o.provides.build
.PHONY : libfreerdp/rail/CMakeFiles/freerdp-rail.dir/rail.c.o.provides

libfreerdp/rail/CMakeFiles/freerdp-rail.dir/rail.c.o.provides.build: libfreerdp/rail/CMakeFiles/freerdp-rail.dir/rail.c.o

freerdp-rail: libfreerdp/rail/CMakeFiles/freerdp-rail.dir/window_list.c.o
freerdp-rail: libfreerdp/rail/CMakeFiles/freerdp-rail.dir/window.c.o
freerdp-rail: libfreerdp/rail/CMakeFiles/freerdp-rail.dir/icon.c.o
freerdp-rail: libfreerdp/rail/CMakeFiles/freerdp-rail.dir/rail.c.o
freerdp-rail: libfreerdp/rail/CMakeFiles/freerdp-rail.dir/build.make
.PHONY : freerdp-rail

# Rule to build all files generated by this target.
libfreerdp/rail/CMakeFiles/freerdp-rail.dir/build: freerdp-rail
.PHONY : libfreerdp/rail/CMakeFiles/freerdp-rail.dir/build

libfreerdp/rail/CMakeFiles/freerdp-rail.dir/requires: libfreerdp/rail/CMakeFiles/freerdp-rail.dir/window_list.c.o.requires
libfreerdp/rail/CMakeFiles/freerdp-rail.dir/requires: libfreerdp/rail/CMakeFiles/freerdp-rail.dir/window.c.o.requires
libfreerdp/rail/CMakeFiles/freerdp-rail.dir/requires: libfreerdp/rail/CMakeFiles/freerdp-rail.dir/icon.c.o.requires
libfreerdp/rail/CMakeFiles/freerdp-rail.dir/requires: libfreerdp/rail/CMakeFiles/freerdp-rail.dir/rail.c.o.requires
.PHONY : libfreerdp/rail/CMakeFiles/freerdp-rail.dir/requires

libfreerdp/rail/CMakeFiles/freerdp-rail.dir/clean:
	cd /source/clients/FreeRDP-1.1.0-beta1/libfreerdp/rail && $(CMAKE_COMMAND) -P CMakeFiles/freerdp-rail.dir/cmake_clean.cmake
.PHONY : libfreerdp/rail/CMakeFiles/freerdp-rail.dir/clean

libfreerdp/rail/CMakeFiles/freerdp-rail.dir/depend:
	cd /source/clients/FreeRDP-1.1.0-beta1 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /source/clients/FreeRDP-1.1.0-beta1 /source/clients/FreeRDP-1.1.0-beta1/libfreerdp/rail /source/clients/FreeRDP-1.1.0-beta1 /source/clients/FreeRDP-1.1.0-beta1/libfreerdp/rail /source/clients/FreeRDP-1.1.0-beta1/libfreerdp/rail/CMakeFiles/freerdp-rail.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : libfreerdp/rail/CMakeFiles/freerdp-rail.dir/depend

