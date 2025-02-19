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
include channels/drdynvc/audin/alsa/CMakeFiles/audin_alsa.dir/depend.make

# Include the progress variables for this target.
include channels/drdynvc/audin/alsa/CMakeFiles/audin_alsa.dir/progress.make

# Include the compile flags for this target's objects.
include channels/drdynvc/audin/alsa/CMakeFiles/audin_alsa.dir/flags.make

channels/drdynvc/audin/alsa/CMakeFiles/audin_alsa.dir/audin_alsa.c.o: channels/drdynvc/audin/alsa/CMakeFiles/audin_alsa.dir/flags.make
channels/drdynvc/audin/alsa/CMakeFiles/audin_alsa.dir/audin_alsa.c.o: channels/drdynvc/audin/alsa/audin_alsa.c
	$(CMAKE_COMMAND) -E cmake_progress_report /source/clients/FreeRDP-1.0.2/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object channels/drdynvc/audin/alsa/CMakeFiles/audin_alsa.dir/audin_alsa.c.o"
	cd /source/clients/FreeRDP-1.0.2/channels/drdynvc/audin/alsa && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/audin_alsa.dir/audin_alsa.c.o   -c /source/clients/FreeRDP-1.0.2/channels/drdynvc/audin/alsa/audin_alsa.c

channels/drdynvc/audin/alsa/CMakeFiles/audin_alsa.dir/audin_alsa.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/audin_alsa.dir/audin_alsa.c.i"
	cd /source/clients/FreeRDP-1.0.2/channels/drdynvc/audin/alsa && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -E /source/clients/FreeRDP-1.0.2/channels/drdynvc/audin/alsa/audin_alsa.c > CMakeFiles/audin_alsa.dir/audin_alsa.c.i

channels/drdynvc/audin/alsa/CMakeFiles/audin_alsa.dir/audin_alsa.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/audin_alsa.dir/audin_alsa.c.s"
	cd /source/clients/FreeRDP-1.0.2/channels/drdynvc/audin/alsa && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -S /source/clients/FreeRDP-1.0.2/channels/drdynvc/audin/alsa/audin_alsa.c -o CMakeFiles/audin_alsa.dir/audin_alsa.c.s

channels/drdynvc/audin/alsa/CMakeFiles/audin_alsa.dir/audin_alsa.c.o.requires:
.PHONY : channels/drdynvc/audin/alsa/CMakeFiles/audin_alsa.dir/audin_alsa.c.o.requires

channels/drdynvc/audin/alsa/CMakeFiles/audin_alsa.dir/audin_alsa.c.o.provides: channels/drdynvc/audin/alsa/CMakeFiles/audin_alsa.dir/audin_alsa.c.o.requires
	$(MAKE) -f channels/drdynvc/audin/alsa/CMakeFiles/audin_alsa.dir/build.make channels/drdynvc/audin/alsa/CMakeFiles/audin_alsa.dir/audin_alsa.c.o.provides.build
.PHONY : channels/drdynvc/audin/alsa/CMakeFiles/audin_alsa.dir/audin_alsa.c.o.provides

channels/drdynvc/audin/alsa/CMakeFiles/audin_alsa.dir/audin_alsa.c.o.provides.build: channels/drdynvc/audin/alsa/CMakeFiles/audin_alsa.dir/audin_alsa.c.o

# Object files for target audin_alsa
audin_alsa_OBJECTS = \
"CMakeFiles/audin_alsa.dir/audin_alsa.c.o"

# External object files for target audin_alsa
audin_alsa_EXTERNAL_OBJECTS =

channels/drdynvc/audin/alsa/audin_alsa.so: channels/drdynvc/audin/alsa/CMakeFiles/audin_alsa.dir/audin_alsa.c.o
channels/drdynvc/audin/alsa/audin_alsa.so: channels/drdynvc/audin/alsa/CMakeFiles/audin_alsa.dir/build.make
channels/drdynvc/audin/alsa/audin_alsa.so: libfreerdp-utils/libfreerdp-utils.so.1.0.2
channels/drdynvc/audin/alsa/audin_alsa.so: /usr/lib/libasound.so
channels/drdynvc/audin/alsa/audin_alsa.so: channels/drdynvc/audin/alsa/CMakeFiles/audin_alsa.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C shared library audin_alsa.so"
	cd /source/clients/FreeRDP-1.0.2/channels/drdynvc/audin/alsa && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/audin_alsa.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
channels/drdynvc/audin/alsa/CMakeFiles/audin_alsa.dir/build: channels/drdynvc/audin/alsa/audin_alsa.so
.PHONY : channels/drdynvc/audin/alsa/CMakeFiles/audin_alsa.dir/build

channels/drdynvc/audin/alsa/CMakeFiles/audin_alsa.dir/requires: channels/drdynvc/audin/alsa/CMakeFiles/audin_alsa.dir/audin_alsa.c.o.requires
.PHONY : channels/drdynvc/audin/alsa/CMakeFiles/audin_alsa.dir/requires

channels/drdynvc/audin/alsa/CMakeFiles/audin_alsa.dir/clean:
	cd /source/clients/FreeRDP-1.0.2/channels/drdynvc/audin/alsa && $(CMAKE_COMMAND) -P CMakeFiles/audin_alsa.dir/cmake_clean.cmake
.PHONY : channels/drdynvc/audin/alsa/CMakeFiles/audin_alsa.dir/clean

channels/drdynvc/audin/alsa/CMakeFiles/audin_alsa.dir/depend:
	cd /source/clients/FreeRDP-1.0.2 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /source/clients/FreeRDP-1.0.2 /source/clients/FreeRDP-1.0.2/channels/drdynvc/audin/alsa /source/clients/FreeRDP-1.0.2 /source/clients/FreeRDP-1.0.2/channels/drdynvc/audin/alsa /source/clients/FreeRDP-1.0.2/channels/drdynvc/audin/alsa/CMakeFiles/audin_alsa.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : channels/drdynvc/audin/alsa/CMakeFiles/audin_alsa.dir/depend

