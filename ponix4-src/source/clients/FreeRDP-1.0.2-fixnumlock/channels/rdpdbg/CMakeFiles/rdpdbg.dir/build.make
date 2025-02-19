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
CMAKE_SOURCE_DIR = /source/clients/FreeRDP-1.0.2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /source/clients/FreeRDP-1.0.2

# Include any dependencies generated for this target.
include channels/rdpdbg/CMakeFiles/rdpdbg.dir/depend.make

# Include the progress variables for this target.
include channels/rdpdbg/CMakeFiles/rdpdbg.dir/progress.make

# Include the compile flags for this target's objects.
include channels/rdpdbg/CMakeFiles/rdpdbg.dir/flags.make

channels/rdpdbg/CMakeFiles/rdpdbg.dir/rdpdbg_main.c.o: channels/rdpdbg/CMakeFiles/rdpdbg.dir/flags.make
channels/rdpdbg/CMakeFiles/rdpdbg.dir/rdpdbg_main.c.o: channels/rdpdbg/rdpdbg_main.c
	$(CMAKE_COMMAND) -E cmake_progress_report /source/clients/FreeRDP-1.0.2/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object channels/rdpdbg/CMakeFiles/rdpdbg.dir/rdpdbg_main.c.o"
	cd /source/clients/FreeRDP-1.0.2/channels/rdpdbg && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/rdpdbg.dir/rdpdbg_main.c.o   -c /source/clients/FreeRDP-1.0.2/channels/rdpdbg/rdpdbg_main.c

channels/rdpdbg/CMakeFiles/rdpdbg.dir/rdpdbg_main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/rdpdbg.dir/rdpdbg_main.c.i"
	cd /source/clients/FreeRDP-1.0.2/channels/rdpdbg && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -E /source/clients/FreeRDP-1.0.2/channels/rdpdbg/rdpdbg_main.c > CMakeFiles/rdpdbg.dir/rdpdbg_main.c.i

channels/rdpdbg/CMakeFiles/rdpdbg.dir/rdpdbg_main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/rdpdbg.dir/rdpdbg_main.c.s"
	cd /source/clients/FreeRDP-1.0.2/channels/rdpdbg && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -S /source/clients/FreeRDP-1.0.2/channels/rdpdbg/rdpdbg_main.c -o CMakeFiles/rdpdbg.dir/rdpdbg_main.c.s

channels/rdpdbg/CMakeFiles/rdpdbg.dir/rdpdbg_main.c.o.requires:
.PHONY : channels/rdpdbg/CMakeFiles/rdpdbg.dir/rdpdbg_main.c.o.requires

channels/rdpdbg/CMakeFiles/rdpdbg.dir/rdpdbg_main.c.o.provides: channels/rdpdbg/CMakeFiles/rdpdbg.dir/rdpdbg_main.c.o.requires
	$(MAKE) -f channels/rdpdbg/CMakeFiles/rdpdbg.dir/build.make channels/rdpdbg/CMakeFiles/rdpdbg.dir/rdpdbg_main.c.o.provides.build
.PHONY : channels/rdpdbg/CMakeFiles/rdpdbg.dir/rdpdbg_main.c.o.provides

channels/rdpdbg/CMakeFiles/rdpdbg.dir/rdpdbg_main.c.o.provides.build: channels/rdpdbg/CMakeFiles/rdpdbg.dir/rdpdbg_main.c.o

# Object files for target rdpdbg
rdpdbg_OBJECTS = \
"CMakeFiles/rdpdbg.dir/rdpdbg_main.c.o"

# External object files for target rdpdbg
rdpdbg_EXTERNAL_OBJECTS =

channels/rdpdbg/rdpdbg.so: channels/rdpdbg/CMakeFiles/rdpdbg.dir/rdpdbg_main.c.o
channels/rdpdbg/rdpdbg.so: channels/rdpdbg/CMakeFiles/rdpdbg.dir/build.make
channels/rdpdbg/rdpdbg.so: libfreerdp-utils/libfreerdp-utils.so.1.0.2
channels/rdpdbg/rdpdbg.so: channels/rdpdbg/CMakeFiles/rdpdbg.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C shared library rdpdbg.so"
	cd /source/clients/FreeRDP-1.0.2/channels/rdpdbg && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/rdpdbg.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
channels/rdpdbg/CMakeFiles/rdpdbg.dir/build: channels/rdpdbg/rdpdbg.so
.PHONY : channels/rdpdbg/CMakeFiles/rdpdbg.dir/build

channels/rdpdbg/CMakeFiles/rdpdbg.dir/requires: channels/rdpdbg/CMakeFiles/rdpdbg.dir/rdpdbg_main.c.o.requires
.PHONY : channels/rdpdbg/CMakeFiles/rdpdbg.dir/requires

channels/rdpdbg/CMakeFiles/rdpdbg.dir/clean:
	cd /source/clients/FreeRDP-1.0.2/channels/rdpdbg && $(CMAKE_COMMAND) -P CMakeFiles/rdpdbg.dir/cmake_clean.cmake
.PHONY : channels/rdpdbg/CMakeFiles/rdpdbg.dir/clean

channels/rdpdbg/CMakeFiles/rdpdbg.dir/depend:
	cd /source/clients/FreeRDP-1.0.2 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /source/clients/FreeRDP-1.0.2 /source/clients/FreeRDP-1.0.2/channels/rdpdbg /source/clients/FreeRDP-1.0.2 /source/clients/FreeRDP-1.0.2/channels/rdpdbg /source/clients/FreeRDP-1.0.2/channels/rdpdbg/CMakeFiles/rdpdbg.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : channels/rdpdbg/CMakeFiles/rdpdbg.dir/depend

