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
CMAKE_SOURCE_DIR = /source/clients/FreeRDP-1.1.0-beta-2013071101

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /source/clients/FreeRDP-1.1.0-beta-2013071101

# Include any dependencies generated for this target.
include channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/depend.make

# Include the progress variables for this target.
include channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/progress.make

# Include the compile flags for this target's objects.
include channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/flags.make

channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/searchman.c.o: channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/flags.make
channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/searchman.c.o: channels/urbdrc/client/searchman.c
	$(CMAKE_COMMAND) -E cmake_progress_report /source/clients/FreeRDP-1.1.0-beta-2013071101/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/searchman.c.o"
	cd /source/clients/FreeRDP-1.1.0-beta-2013071101/channels/urbdrc/client && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/urbdrc-client.dir/searchman.c.o   -c /source/clients/FreeRDP-1.1.0-beta-2013071101/channels/urbdrc/client/searchman.c

channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/searchman.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/urbdrc-client.dir/searchman.c.i"
	cd /source/clients/FreeRDP-1.1.0-beta-2013071101/channels/urbdrc/client && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -E /source/clients/FreeRDP-1.1.0-beta-2013071101/channels/urbdrc/client/searchman.c > CMakeFiles/urbdrc-client.dir/searchman.c.i

channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/searchman.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/urbdrc-client.dir/searchman.c.s"
	cd /source/clients/FreeRDP-1.1.0-beta-2013071101/channels/urbdrc/client && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -S /source/clients/FreeRDP-1.1.0-beta-2013071101/channels/urbdrc/client/searchman.c -o CMakeFiles/urbdrc-client.dir/searchman.c.s

channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/searchman.c.o.requires:
.PHONY : channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/searchman.c.o.requires

channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/searchman.c.o.provides: channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/searchman.c.o.requires
	$(MAKE) -f channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/build.make channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/searchman.c.o.provides.build
.PHONY : channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/searchman.c.o.provides

channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/searchman.c.o.provides.build: channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/searchman.c.o

channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/isoch_queue.c.o: channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/flags.make
channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/isoch_queue.c.o: channels/urbdrc/client/isoch_queue.c
	$(CMAKE_COMMAND) -E cmake_progress_report /source/clients/FreeRDP-1.1.0-beta-2013071101/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/isoch_queue.c.o"
	cd /source/clients/FreeRDP-1.1.0-beta-2013071101/channels/urbdrc/client && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/urbdrc-client.dir/isoch_queue.c.o   -c /source/clients/FreeRDP-1.1.0-beta-2013071101/channels/urbdrc/client/isoch_queue.c

channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/isoch_queue.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/urbdrc-client.dir/isoch_queue.c.i"
	cd /source/clients/FreeRDP-1.1.0-beta-2013071101/channels/urbdrc/client && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -E /source/clients/FreeRDP-1.1.0-beta-2013071101/channels/urbdrc/client/isoch_queue.c > CMakeFiles/urbdrc-client.dir/isoch_queue.c.i

channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/isoch_queue.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/urbdrc-client.dir/isoch_queue.c.s"
	cd /source/clients/FreeRDP-1.1.0-beta-2013071101/channels/urbdrc/client && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -S /source/clients/FreeRDP-1.1.0-beta-2013071101/channels/urbdrc/client/isoch_queue.c -o CMakeFiles/urbdrc-client.dir/isoch_queue.c.s

channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/isoch_queue.c.o.requires:
.PHONY : channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/isoch_queue.c.o.requires

channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/isoch_queue.c.o.provides: channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/isoch_queue.c.o.requires
	$(MAKE) -f channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/build.make channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/isoch_queue.c.o.provides.build
.PHONY : channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/isoch_queue.c.o.provides

channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/isoch_queue.c.o.provides.build: channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/isoch_queue.c.o

channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/data_transfer.c.o: channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/flags.make
channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/data_transfer.c.o: channels/urbdrc/client/data_transfer.c
	$(CMAKE_COMMAND) -E cmake_progress_report /source/clients/FreeRDP-1.1.0-beta-2013071101/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/data_transfer.c.o"
	cd /source/clients/FreeRDP-1.1.0-beta-2013071101/channels/urbdrc/client && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/urbdrc-client.dir/data_transfer.c.o   -c /source/clients/FreeRDP-1.1.0-beta-2013071101/channels/urbdrc/client/data_transfer.c

channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/data_transfer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/urbdrc-client.dir/data_transfer.c.i"
	cd /source/clients/FreeRDP-1.1.0-beta-2013071101/channels/urbdrc/client && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -E /source/clients/FreeRDP-1.1.0-beta-2013071101/channels/urbdrc/client/data_transfer.c > CMakeFiles/urbdrc-client.dir/data_transfer.c.i

channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/data_transfer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/urbdrc-client.dir/data_transfer.c.s"
	cd /source/clients/FreeRDP-1.1.0-beta-2013071101/channels/urbdrc/client && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -S /source/clients/FreeRDP-1.1.0-beta-2013071101/channels/urbdrc/client/data_transfer.c -o CMakeFiles/urbdrc-client.dir/data_transfer.c.s

channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/data_transfer.c.o.requires:
.PHONY : channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/data_transfer.c.o.requires

channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/data_transfer.c.o.provides: channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/data_transfer.c.o.requires
	$(MAKE) -f channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/build.make channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/data_transfer.c.o.provides.build
.PHONY : channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/data_transfer.c.o.provides

channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/data_transfer.c.o.provides.build: channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/data_transfer.c.o

channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/urbdrc_main.c.o: channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/flags.make
channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/urbdrc_main.c.o: channels/urbdrc/client/urbdrc_main.c
	$(CMAKE_COMMAND) -E cmake_progress_report /source/clients/FreeRDP-1.1.0-beta-2013071101/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/urbdrc_main.c.o"
	cd /source/clients/FreeRDP-1.1.0-beta-2013071101/channels/urbdrc/client && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/urbdrc-client.dir/urbdrc_main.c.o   -c /source/clients/FreeRDP-1.1.0-beta-2013071101/channels/urbdrc/client/urbdrc_main.c

channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/urbdrc_main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/urbdrc-client.dir/urbdrc_main.c.i"
	cd /source/clients/FreeRDP-1.1.0-beta-2013071101/channels/urbdrc/client && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -E /source/clients/FreeRDP-1.1.0-beta-2013071101/channels/urbdrc/client/urbdrc_main.c > CMakeFiles/urbdrc-client.dir/urbdrc_main.c.i

channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/urbdrc_main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/urbdrc-client.dir/urbdrc_main.c.s"
	cd /source/clients/FreeRDP-1.1.0-beta-2013071101/channels/urbdrc/client && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -S /source/clients/FreeRDP-1.1.0-beta-2013071101/channels/urbdrc/client/urbdrc_main.c -o CMakeFiles/urbdrc-client.dir/urbdrc_main.c.s

channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/urbdrc_main.c.o.requires:
.PHONY : channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/urbdrc_main.c.o.requires

channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/urbdrc_main.c.o.provides: channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/urbdrc_main.c.o.requires
	$(MAKE) -f channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/build.make channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/urbdrc_main.c.o.provides.build
.PHONY : channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/urbdrc_main.c.o.provides

channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/urbdrc_main.c.o.provides.build: channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/urbdrc_main.c.o

# Object files for target urbdrc-client
urbdrc__client_OBJECTS = \
"CMakeFiles/urbdrc-client.dir/searchman.c.o" \
"CMakeFiles/urbdrc-client.dir/isoch_queue.c.o" \
"CMakeFiles/urbdrc-client.dir/data_transfer.c.o" \
"CMakeFiles/urbdrc-client.dir/urbdrc_main.c.o"

# External object files for target urbdrc-client
urbdrc__client_EXTERNAL_OBJECTS =

channels/urbdrc/client/urbdrc-client.so: channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/searchman.c.o
channels/urbdrc/client/urbdrc-client.so: channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/isoch_queue.c.o
channels/urbdrc/client/urbdrc-client.so: channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/data_transfer.c.o
channels/urbdrc/client/urbdrc-client.so: channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/urbdrc_main.c.o
channels/urbdrc/client/urbdrc-client.so: channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/build.make
channels/urbdrc/client/urbdrc-client.so: winpr/libwinpr/utils/libwinpr-utils.so.0.1.0
channels/urbdrc/client/urbdrc-client.so: libfreerdp/common/libfreerdp-common.so.1.1.0-beta1
channels/urbdrc/client/urbdrc-client.so: libfreerdp/utils/libfreerdp-utils.so.1.1.0
channels/urbdrc/client/urbdrc-client.so: winpr/libwinpr/file/libwinpr-file.so.0.1.0
channels/urbdrc/client/urbdrc-client.so: winpr/libwinpr/library/libwinpr-library.so.0.1.0
channels/urbdrc/client/urbdrc-client.so: winpr/libwinpr/utils/libwinpr-utils.so.0.1.0
channels/urbdrc/client/urbdrc-client.so: /usr/lib/libz.so
channels/urbdrc/client/urbdrc-client.so: /usr/lib/libssl.so
channels/urbdrc/client/urbdrc-client.so: /usr/lib/libcrypto.so
channels/urbdrc/client/urbdrc-client.so: winpr/libwinpr/sysinfo/libwinpr-sysinfo.so.0.1.0
channels/urbdrc/client/urbdrc-client.so: winpr/libwinpr/synch/libwinpr-synch.so.0.1.0
channels/urbdrc/client/urbdrc-client.so: winpr/libwinpr/path/libwinpr-path.so.0.1.0
channels/urbdrc/client/urbdrc-client.so: winpr/libwinpr/crt/libwinpr-crt.so.0.1.0
channels/urbdrc/client/urbdrc-client.so: winpr/libwinpr/heap/libwinpr-heap.so.0.1.0
channels/urbdrc/client/urbdrc-client.so: winpr/libwinpr/environment/libwinpr-environment.so.0.1.0
channels/urbdrc/client/urbdrc-client.so: winpr/libwinpr/thread/libwinpr-thread.so.0.1.0
channels/urbdrc/client/urbdrc-client.so: winpr/libwinpr/handle/libwinpr-handle.so.0.1.0
channels/urbdrc/client/urbdrc-client.so: channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C shared library urbdrc-client.so"
	cd /source/clients/FreeRDP-1.1.0-beta-2013071101/channels/urbdrc/client && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/urbdrc-client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/build: channels/urbdrc/client/urbdrc-client.so
.PHONY : channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/build

channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/requires: channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/searchman.c.o.requires
channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/requires: channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/isoch_queue.c.o.requires
channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/requires: channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/data_transfer.c.o.requires
channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/requires: channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/urbdrc_main.c.o.requires
.PHONY : channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/requires

channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/clean:
	cd /source/clients/FreeRDP-1.1.0-beta-2013071101/channels/urbdrc/client && $(CMAKE_COMMAND) -P CMakeFiles/urbdrc-client.dir/cmake_clean.cmake
.PHONY : channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/clean

channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/depend:
	cd /source/clients/FreeRDP-1.1.0-beta-2013071101 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /source/clients/FreeRDP-1.1.0-beta-2013071101 /source/clients/FreeRDP-1.1.0-beta-2013071101/channels/urbdrc/client /source/clients/FreeRDP-1.1.0-beta-2013071101 /source/clients/FreeRDP-1.1.0-beta-2013071101/channels/urbdrc/client /source/clients/FreeRDP-1.1.0-beta-2013071101/channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : channels/urbdrc/client/CMakeFiles/urbdrc-client.dir/depend

