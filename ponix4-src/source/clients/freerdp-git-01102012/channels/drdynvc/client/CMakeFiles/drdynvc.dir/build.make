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
CMAKE_SOURCE_DIR = /f

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /f

# Include any dependencies generated for this target.
include channels/drdynvc/client/CMakeFiles/drdynvc.dir/depend.make

# Include the progress variables for this target.
include channels/drdynvc/client/CMakeFiles/drdynvc.dir/progress.make

# Include the compile flags for this target's objects.
include channels/drdynvc/client/CMakeFiles/drdynvc.dir/flags.make

channels/drdynvc/client/CMakeFiles/drdynvc.dir/drdynvc_main.c.o: channels/drdynvc/client/CMakeFiles/drdynvc.dir/flags.make
channels/drdynvc/client/CMakeFiles/drdynvc.dir/drdynvc_main.c.o: channels/drdynvc/client/drdynvc_main.c
	$(CMAKE_COMMAND) -E cmake_progress_report /f/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object channels/drdynvc/client/CMakeFiles/drdynvc.dir/drdynvc_main.c.o"
	cd /f/channels/drdynvc/client && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/drdynvc.dir/drdynvc_main.c.o   -c /f/channels/drdynvc/client/drdynvc_main.c

channels/drdynvc/client/CMakeFiles/drdynvc.dir/drdynvc_main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/drdynvc.dir/drdynvc_main.c.i"
	cd /f/channels/drdynvc/client && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -E /f/channels/drdynvc/client/drdynvc_main.c > CMakeFiles/drdynvc.dir/drdynvc_main.c.i

channels/drdynvc/client/CMakeFiles/drdynvc.dir/drdynvc_main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/drdynvc.dir/drdynvc_main.c.s"
	cd /f/channels/drdynvc/client && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -S /f/channels/drdynvc/client/drdynvc_main.c -o CMakeFiles/drdynvc.dir/drdynvc_main.c.s

channels/drdynvc/client/CMakeFiles/drdynvc.dir/drdynvc_main.c.o.requires:
.PHONY : channels/drdynvc/client/CMakeFiles/drdynvc.dir/drdynvc_main.c.o.requires

channels/drdynvc/client/CMakeFiles/drdynvc.dir/drdynvc_main.c.o.provides: channels/drdynvc/client/CMakeFiles/drdynvc.dir/drdynvc_main.c.o.requires
	$(MAKE) -f channels/drdynvc/client/CMakeFiles/drdynvc.dir/build.make channels/drdynvc/client/CMakeFiles/drdynvc.dir/drdynvc_main.c.o.provides.build
.PHONY : channels/drdynvc/client/CMakeFiles/drdynvc.dir/drdynvc_main.c.o.provides

channels/drdynvc/client/CMakeFiles/drdynvc.dir/drdynvc_main.c.o.provides.build: channels/drdynvc/client/CMakeFiles/drdynvc.dir/drdynvc_main.c.o

channels/drdynvc/client/CMakeFiles/drdynvc.dir/dvcman.c.o: channels/drdynvc/client/CMakeFiles/drdynvc.dir/flags.make
channels/drdynvc/client/CMakeFiles/drdynvc.dir/dvcman.c.o: channels/drdynvc/client/dvcman.c
	$(CMAKE_COMMAND) -E cmake_progress_report /f/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object channels/drdynvc/client/CMakeFiles/drdynvc.dir/dvcman.c.o"
	cd /f/channels/drdynvc/client && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/drdynvc.dir/dvcman.c.o   -c /f/channels/drdynvc/client/dvcman.c

channels/drdynvc/client/CMakeFiles/drdynvc.dir/dvcman.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/drdynvc.dir/dvcman.c.i"
	cd /f/channels/drdynvc/client && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -E /f/channels/drdynvc/client/dvcman.c > CMakeFiles/drdynvc.dir/dvcman.c.i

channels/drdynvc/client/CMakeFiles/drdynvc.dir/dvcman.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/drdynvc.dir/dvcman.c.s"
	cd /f/channels/drdynvc/client && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -S /f/channels/drdynvc/client/dvcman.c -o CMakeFiles/drdynvc.dir/dvcman.c.s

channels/drdynvc/client/CMakeFiles/drdynvc.dir/dvcman.c.o.requires:
.PHONY : channels/drdynvc/client/CMakeFiles/drdynvc.dir/dvcman.c.o.requires

channels/drdynvc/client/CMakeFiles/drdynvc.dir/dvcman.c.o.provides: channels/drdynvc/client/CMakeFiles/drdynvc.dir/dvcman.c.o.requires
	$(MAKE) -f channels/drdynvc/client/CMakeFiles/drdynvc.dir/build.make channels/drdynvc/client/CMakeFiles/drdynvc.dir/dvcman.c.o.provides.build
.PHONY : channels/drdynvc/client/CMakeFiles/drdynvc.dir/dvcman.c.o.provides

channels/drdynvc/client/CMakeFiles/drdynvc.dir/dvcman.c.o.provides.build: channels/drdynvc/client/CMakeFiles/drdynvc.dir/dvcman.c.o

# Object files for target drdynvc
drdynvc_OBJECTS = \
"CMakeFiles/drdynvc.dir/drdynvc_main.c.o" \
"CMakeFiles/drdynvc.dir/dvcman.c.o"

# External object files for target drdynvc
drdynvc_EXTERNAL_OBJECTS =

channels/drdynvc/client/drdynvc.so: channels/drdynvc/client/CMakeFiles/drdynvc.dir/drdynvc_main.c.o
channels/drdynvc/client/drdynvc.so: channels/drdynvc/client/CMakeFiles/drdynvc.dir/dvcman.c.o
channels/drdynvc/client/drdynvc.so: channels/drdynvc/client/CMakeFiles/drdynvc.dir/build.make
channels/drdynvc/client/drdynvc.so: libfreerdp/utils/libfreerdp-utils.so.1.1.0
channels/drdynvc/client/drdynvc.so: winpr/libwinpr/crt/libwinpr-crt.so.0.1.0
channels/drdynvc/client/drdynvc.so: winpr/libwinpr/synch/libwinpr-synch.so.0.1.0
channels/drdynvc/client/drdynvc.so: winpr/libwinpr/handle/libwinpr-handle.so.0.1.0
channels/drdynvc/client/drdynvc.so: channels/drdynvc/client/CMakeFiles/drdynvc.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C shared library drdynvc.so"
	cd /f/channels/drdynvc/client && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/drdynvc.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
channels/drdynvc/client/CMakeFiles/drdynvc.dir/build: channels/drdynvc/client/drdynvc.so
.PHONY : channels/drdynvc/client/CMakeFiles/drdynvc.dir/build

# Object files for target drdynvc
drdynvc_OBJECTS = \
"CMakeFiles/drdynvc.dir/drdynvc_main.c.o" \
"CMakeFiles/drdynvc.dir/dvcman.c.o"

# External object files for target drdynvc
drdynvc_EXTERNAL_OBJECTS =

channels/drdynvc/client/CMakeFiles/CMakeRelink.dir/drdynvc.so: channels/drdynvc/client/CMakeFiles/drdynvc.dir/drdynvc_main.c.o
channels/drdynvc/client/CMakeFiles/CMakeRelink.dir/drdynvc.so: channels/drdynvc/client/CMakeFiles/drdynvc.dir/dvcman.c.o
channels/drdynvc/client/CMakeFiles/CMakeRelink.dir/drdynvc.so: channels/drdynvc/client/CMakeFiles/drdynvc.dir/build.make
channels/drdynvc/client/CMakeFiles/CMakeRelink.dir/drdynvc.so: libfreerdp/utils/libfreerdp-utils.so.1.1.0
channels/drdynvc/client/CMakeFiles/CMakeRelink.dir/drdynvc.so: winpr/libwinpr/crt/libwinpr-crt.so.0.1.0
channels/drdynvc/client/CMakeFiles/CMakeRelink.dir/drdynvc.so: winpr/libwinpr/synch/libwinpr-synch.so.0.1.0
channels/drdynvc/client/CMakeFiles/CMakeRelink.dir/drdynvc.so: winpr/libwinpr/handle/libwinpr-handle.so.0.1.0
channels/drdynvc/client/CMakeFiles/CMakeRelink.dir/drdynvc.so: channels/drdynvc/client/CMakeFiles/drdynvc.dir/relink.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C shared library CMakeFiles/CMakeRelink.dir/drdynvc.so"
	cd /f/channels/drdynvc/client && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/drdynvc.dir/relink.txt --verbose=$(VERBOSE)

# Rule to relink during preinstall.
channels/drdynvc/client/CMakeFiles/drdynvc.dir/preinstall: channels/drdynvc/client/CMakeFiles/CMakeRelink.dir/drdynvc.so
.PHONY : channels/drdynvc/client/CMakeFiles/drdynvc.dir/preinstall

channels/drdynvc/client/CMakeFiles/drdynvc.dir/requires: channels/drdynvc/client/CMakeFiles/drdynvc.dir/drdynvc_main.c.o.requires
channels/drdynvc/client/CMakeFiles/drdynvc.dir/requires: channels/drdynvc/client/CMakeFiles/drdynvc.dir/dvcman.c.o.requires
.PHONY : channels/drdynvc/client/CMakeFiles/drdynvc.dir/requires

channels/drdynvc/client/CMakeFiles/drdynvc.dir/clean:
	cd /f/channels/drdynvc/client && $(CMAKE_COMMAND) -P CMakeFiles/drdynvc.dir/cmake_clean.cmake
.PHONY : channels/drdynvc/client/CMakeFiles/drdynvc.dir/clean

channels/drdynvc/client/CMakeFiles/drdynvc.dir/depend:
	cd /f && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /f /f/channels/drdynvc/client /f /f/channels/drdynvc/client /f/channels/drdynvc/client/CMakeFiles/drdynvc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : channels/drdynvc/client/CMakeFiles/drdynvc.dir/depend

