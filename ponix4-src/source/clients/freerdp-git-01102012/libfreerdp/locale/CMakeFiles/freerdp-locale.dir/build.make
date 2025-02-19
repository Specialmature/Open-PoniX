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
include libfreerdp/locale/CMakeFiles/freerdp-locale.dir/depend.make

# Include the progress variables for this target.
include libfreerdp/locale/CMakeFiles/freerdp-locale.dir/progress.make

# Include the compile flags for this target's objects.
include libfreerdp/locale/CMakeFiles/freerdp-locale.dir/flags.make

libfreerdp/locale/CMakeFiles/freerdp-locale.dir/virtual_key_codes.c.o: libfreerdp/locale/CMakeFiles/freerdp-locale.dir/flags.make
libfreerdp/locale/CMakeFiles/freerdp-locale.dir/virtual_key_codes.c.o: libfreerdp/locale/virtual_key_codes.c
	$(CMAKE_COMMAND) -E cmake_progress_report /f/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object libfreerdp/locale/CMakeFiles/freerdp-locale.dir/virtual_key_codes.c.o"
	cd /f/libfreerdp/locale && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/freerdp-locale.dir/virtual_key_codes.c.o   -c /f/libfreerdp/locale/virtual_key_codes.c

libfreerdp/locale/CMakeFiles/freerdp-locale.dir/virtual_key_codes.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/freerdp-locale.dir/virtual_key_codes.c.i"
	cd /f/libfreerdp/locale && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -E /f/libfreerdp/locale/virtual_key_codes.c > CMakeFiles/freerdp-locale.dir/virtual_key_codes.c.i

libfreerdp/locale/CMakeFiles/freerdp-locale.dir/virtual_key_codes.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/freerdp-locale.dir/virtual_key_codes.c.s"
	cd /f/libfreerdp/locale && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -S /f/libfreerdp/locale/virtual_key_codes.c -o CMakeFiles/freerdp-locale.dir/virtual_key_codes.c.s

libfreerdp/locale/CMakeFiles/freerdp-locale.dir/virtual_key_codes.c.o.requires:
.PHONY : libfreerdp/locale/CMakeFiles/freerdp-locale.dir/virtual_key_codes.c.o.requires

libfreerdp/locale/CMakeFiles/freerdp-locale.dir/virtual_key_codes.c.o.provides: libfreerdp/locale/CMakeFiles/freerdp-locale.dir/virtual_key_codes.c.o.requires
	$(MAKE) -f libfreerdp/locale/CMakeFiles/freerdp-locale.dir/build.make libfreerdp/locale/CMakeFiles/freerdp-locale.dir/virtual_key_codes.c.o.provides.build
.PHONY : libfreerdp/locale/CMakeFiles/freerdp-locale.dir/virtual_key_codes.c.o.provides

libfreerdp/locale/CMakeFiles/freerdp-locale.dir/virtual_key_codes.c.o.provides.build: libfreerdp/locale/CMakeFiles/freerdp-locale.dir/virtual_key_codes.c.o

libfreerdp/locale/CMakeFiles/freerdp-locale.dir/keyboard_layout.c.o: libfreerdp/locale/CMakeFiles/freerdp-locale.dir/flags.make
libfreerdp/locale/CMakeFiles/freerdp-locale.dir/keyboard_layout.c.o: libfreerdp/locale/keyboard_layout.c
	$(CMAKE_COMMAND) -E cmake_progress_report /f/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object libfreerdp/locale/CMakeFiles/freerdp-locale.dir/keyboard_layout.c.o"
	cd /f/libfreerdp/locale && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/freerdp-locale.dir/keyboard_layout.c.o   -c /f/libfreerdp/locale/keyboard_layout.c

libfreerdp/locale/CMakeFiles/freerdp-locale.dir/keyboard_layout.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/freerdp-locale.dir/keyboard_layout.c.i"
	cd /f/libfreerdp/locale && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -E /f/libfreerdp/locale/keyboard_layout.c > CMakeFiles/freerdp-locale.dir/keyboard_layout.c.i

libfreerdp/locale/CMakeFiles/freerdp-locale.dir/keyboard_layout.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/freerdp-locale.dir/keyboard_layout.c.s"
	cd /f/libfreerdp/locale && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -S /f/libfreerdp/locale/keyboard_layout.c -o CMakeFiles/freerdp-locale.dir/keyboard_layout.c.s

libfreerdp/locale/CMakeFiles/freerdp-locale.dir/keyboard_layout.c.o.requires:
.PHONY : libfreerdp/locale/CMakeFiles/freerdp-locale.dir/keyboard_layout.c.o.requires

libfreerdp/locale/CMakeFiles/freerdp-locale.dir/keyboard_layout.c.o.provides: libfreerdp/locale/CMakeFiles/freerdp-locale.dir/keyboard_layout.c.o.requires
	$(MAKE) -f libfreerdp/locale/CMakeFiles/freerdp-locale.dir/build.make libfreerdp/locale/CMakeFiles/freerdp-locale.dir/keyboard_layout.c.o.provides.build
.PHONY : libfreerdp/locale/CMakeFiles/freerdp-locale.dir/keyboard_layout.c.o.provides

libfreerdp/locale/CMakeFiles/freerdp-locale.dir/keyboard_layout.c.o.provides.build: libfreerdp/locale/CMakeFiles/freerdp-locale.dir/keyboard_layout.c.o

libfreerdp/locale/CMakeFiles/freerdp-locale.dir/keyboard.c.o: libfreerdp/locale/CMakeFiles/freerdp-locale.dir/flags.make
libfreerdp/locale/CMakeFiles/freerdp-locale.dir/keyboard.c.o: libfreerdp/locale/keyboard.c
	$(CMAKE_COMMAND) -E cmake_progress_report /f/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object libfreerdp/locale/CMakeFiles/freerdp-locale.dir/keyboard.c.o"
	cd /f/libfreerdp/locale && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/freerdp-locale.dir/keyboard.c.o   -c /f/libfreerdp/locale/keyboard.c

libfreerdp/locale/CMakeFiles/freerdp-locale.dir/keyboard.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/freerdp-locale.dir/keyboard.c.i"
	cd /f/libfreerdp/locale && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -E /f/libfreerdp/locale/keyboard.c > CMakeFiles/freerdp-locale.dir/keyboard.c.i

libfreerdp/locale/CMakeFiles/freerdp-locale.dir/keyboard.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/freerdp-locale.dir/keyboard.c.s"
	cd /f/libfreerdp/locale && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -S /f/libfreerdp/locale/keyboard.c -o CMakeFiles/freerdp-locale.dir/keyboard.c.s

libfreerdp/locale/CMakeFiles/freerdp-locale.dir/keyboard.c.o.requires:
.PHONY : libfreerdp/locale/CMakeFiles/freerdp-locale.dir/keyboard.c.o.requires

libfreerdp/locale/CMakeFiles/freerdp-locale.dir/keyboard.c.o.provides: libfreerdp/locale/CMakeFiles/freerdp-locale.dir/keyboard.c.o.requires
	$(MAKE) -f libfreerdp/locale/CMakeFiles/freerdp-locale.dir/build.make libfreerdp/locale/CMakeFiles/freerdp-locale.dir/keyboard.c.o.provides.build
.PHONY : libfreerdp/locale/CMakeFiles/freerdp-locale.dir/keyboard.c.o.provides

libfreerdp/locale/CMakeFiles/freerdp-locale.dir/keyboard.c.o.provides.build: libfreerdp/locale/CMakeFiles/freerdp-locale.dir/keyboard.c.o

libfreerdp/locale/CMakeFiles/freerdp-locale.dir/locale.c.o: libfreerdp/locale/CMakeFiles/freerdp-locale.dir/flags.make
libfreerdp/locale/CMakeFiles/freerdp-locale.dir/locale.c.o: libfreerdp/locale/locale.c
	$(CMAKE_COMMAND) -E cmake_progress_report /f/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object libfreerdp/locale/CMakeFiles/freerdp-locale.dir/locale.c.o"
	cd /f/libfreerdp/locale && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/freerdp-locale.dir/locale.c.o   -c /f/libfreerdp/locale/locale.c

libfreerdp/locale/CMakeFiles/freerdp-locale.dir/locale.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/freerdp-locale.dir/locale.c.i"
	cd /f/libfreerdp/locale && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -E /f/libfreerdp/locale/locale.c > CMakeFiles/freerdp-locale.dir/locale.c.i

libfreerdp/locale/CMakeFiles/freerdp-locale.dir/locale.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/freerdp-locale.dir/locale.c.s"
	cd /f/libfreerdp/locale && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -S /f/libfreerdp/locale/locale.c -o CMakeFiles/freerdp-locale.dir/locale.c.s

libfreerdp/locale/CMakeFiles/freerdp-locale.dir/locale.c.o.requires:
.PHONY : libfreerdp/locale/CMakeFiles/freerdp-locale.dir/locale.c.o.requires

libfreerdp/locale/CMakeFiles/freerdp-locale.dir/locale.c.o.provides: libfreerdp/locale/CMakeFiles/freerdp-locale.dir/locale.c.o.requires
	$(MAKE) -f libfreerdp/locale/CMakeFiles/freerdp-locale.dir/build.make libfreerdp/locale/CMakeFiles/freerdp-locale.dir/locale.c.o.provides.build
.PHONY : libfreerdp/locale/CMakeFiles/freerdp-locale.dir/locale.c.o.provides

libfreerdp/locale/CMakeFiles/freerdp-locale.dir/locale.c.o.provides.build: libfreerdp/locale/CMakeFiles/freerdp-locale.dir/locale.c.o

libfreerdp/locale/CMakeFiles/freerdp-locale.dir/timezone.c.o: libfreerdp/locale/CMakeFiles/freerdp-locale.dir/flags.make
libfreerdp/locale/CMakeFiles/freerdp-locale.dir/timezone.c.o: libfreerdp/locale/timezone.c
	$(CMAKE_COMMAND) -E cmake_progress_report /f/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object libfreerdp/locale/CMakeFiles/freerdp-locale.dir/timezone.c.o"
	cd /f/libfreerdp/locale && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/freerdp-locale.dir/timezone.c.o   -c /f/libfreerdp/locale/timezone.c

libfreerdp/locale/CMakeFiles/freerdp-locale.dir/timezone.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/freerdp-locale.dir/timezone.c.i"
	cd /f/libfreerdp/locale && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -E /f/libfreerdp/locale/timezone.c > CMakeFiles/freerdp-locale.dir/timezone.c.i

libfreerdp/locale/CMakeFiles/freerdp-locale.dir/timezone.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/freerdp-locale.dir/timezone.c.s"
	cd /f/libfreerdp/locale && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -S /f/libfreerdp/locale/timezone.c -o CMakeFiles/freerdp-locale.dir/timezone.c.s

libfreerdp/locale/CMakeFiles/freerdp-locale.dir/timezone.c.o.requires:
.PHONY : libfreerdp/locale/CMakeFiles/freerdp-locale.dir/timezone.c.o.requires

libfreerdp/locale/CMakeFiles/freerdp-locale.dir/timezone.c.o.provides: libfreerdp/locale/CMakeFiles/freerdp-locale.dir/timezone.c.o.requires
	$(MAKE) -f libfreerdp/locale/CMakeFiles/freerdp-locale.dir/build.make libfreerdp/locale/CMakeFiles/freerdp-locale.dir/timezone.c.o.provides.build
.PHONY : libfreerdp/locale/CMakeFiles/freerdp-locale.dir/timezone.c.o.provides

libfreerdp/locale/CMakeFiles/freerdp-locale.dir/timezone.c.o.provides.build: libfreerdp/locale/CMakeFiles/freerdp-locale.dir/timezone.c.o

libfreerdp/locale/CMakeFiles/freerdp-locale.dir/xkb_layout_ids.c.o: libfreerdp/locale/CMakeFiles/freerdp-locale.dir/flags.make
libfreerdp/locale/CMakeFiles/freerdp-locale.dir/xkb_layout_ids.c.o: libfreerdp/locale/xkb_layout_ids.c
	$(CMAKE_COMMAND) -E cmake_progress_report /f/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object libfreerdp/locale/CMakeFiles/freerdp-locale.dir/xkb_layout_ids.c.o"
	cd /f/libfreerdp/locale && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/freerdp-locale.dir/xkb_layout_ids.c.o   -c /f/libfreerdp/locale/xkb_layout_ids.c

libfreerdp/locale/CMakeFiles/freerdp-locale.dir/xkb_layout_ids.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/freerdp-locale.dir/xkb_layout_ids.c.i"
	cd /f/libfreerdp/locale && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -E /f/libfreerdp/locale/xkb_layout_ids.c > CMakeFiles/freerdp-locale.dir/xkb_layout_ids.c.i

libfreerdp/locale/CMakeFiles/freerdp-locale.dir/xkb_layout_ids.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/freerdp-locale.dir/xkb_layout_ids.c.s"
	cd /f/libfreerdp/locale && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -S /f/libfreerdp/locale/xkb_layout_ids.c -o CMakeFiles/freerdp-locale.dir/xkb_layout_ids.c.s

libfreerdp/locale/CMakeFiles/freerdp-locale.dir/xkb_layout_ids.c.o.requires:
.PHONY : libfreerdp/locale/CMakeFiles/freerdp-locale.dir/xkb_layout_ids.c.o.requires

libfreerdp/locale/CMakeFiles/freerdp-locale.dir/xkb_layout_ids.c.o.provides: libfreerdp/locale/CMakeFiles/freerdp-locale.dir/xkb_layout_ids.c.o.requires
	$(MAKE) -f libfreerdp/locale/CMakeFiles/freerdp-locale.dir/build.make libfreerdp/locale/CMakeFiles/freerdp-locale.dir/xkb_layout_ids.c.o.provides.build
.PHONY : libfreerdp/locale/CMakeFiles/freerdp-locale.dir/xkb_layout_ids.c.o.provides

libfreerdp/locale/CMakeFiles/freerdp-locale.dir/xkb_layout_ids.c.o.provides.build: libfreerdp/locale/CMakeFiles/freerdp-locale.dir/xkb_layout_ids.c.o

libfreerdp/locale/CMakeFiles/freerdp-locale.dir/keyboard_xkbfile.c.o: libfreerdp/locale/CMakeFiles/freerdp-locale.dir/flags.make
libfreerdp/locale/CMakeFiles/freerdp-locale.dir/keyboard_xkbfile.c.o: libfreerdp/locale/keyboard_xkbfile.c
	$(CMAKE_COMMAND) -E cmake_progress_report /f/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object libfreerdp/locale/CMakeFiles/freerdp-locale.dir/keyboard_xkbfile.c.o"
	cd /f/libfreerdp/locale && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/freerdp-locale.dir/keyboard_xkbfile.c.o   -c /f/libfreerdp/locale/keyboard_xkbfile.c

libfreerdp/locale/CMakeFiles/freerdp-locale.dir/keyboard_xkbfile.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/freerdp-locale.dir/keyboard_xkbfile.c.i"
	cd /f/libfreerdp/locale && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -E /f/libfreerdp/locale/keyboard_xkbfile.c > CMakeFiles/freerdp-locale.dir/keyboard_xkbfile.c.i

libfreerdp/locale/CMakeFiles/freerdp-locale.dir/keyboard_xkbfile.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/freerdp-locale.dir/keyboard_xkbfile.c.s"
	cd /f/libfreerdp/locale && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -S /f/libfreerdp/locale/keyboard_xkbfile.c -o CMakeFiles/freerdp-locale.dir/keyboard_xkbfile.c.s

libfreerdp/locale/CMakeFiles/freerdp-locale.dir/keyboard_xkbfile.c.o.requires:
.PHONY : libfreerdp/locale/CMakeFiles/freerdp-locale.dir/keyboard_xkbfile.c.o.requires

libfreerdp/locale/CMakeFiles/freerdp-locale.dir/keyboard_xkbfile.c.o.provides: libfreerdp/locale/CMakeFiles/freerdp-locale.dir/keyboard_xkbfile.c.o.requires
	$(MAKE) -f libfreerdp/locale/CMakeFiles/freerdp-locale.dir/build.make libfreerdp/locale/CMakeFiles/freerdp-locale.dir/keyboard_xkbfile.c.o.provides.build
.PHONY : libfreerdp/locale/CMakeFiles/freerdp-locale.dir/keyboard_xkbfile.c.o.provides

libfreerdp/locale/CMakeFiles/freerdp-locale.dir/keyboard_xkbfile.c.o.provides.build: libfreerdp/locale/CMakeFiles/freerdp-locale.dir/keyboard_xkbfile.c.o

# Object files for target freerdp-locale
freerdp__locale_OBJECTS = \
"CMakeFiles/freerdp-locale.dir/virtual_key_codes.c.o" \
"CMakeFiles/freerdp-locale.dir/keyboard_layout.c.o" \
"CMakeFiles/freerdp-locale.dir/keyboard.c.o" \
"CMakeFiles/freerdp-locale.dir/locale.c.o" \
"CMakeFiles/freerdp-locale.dir/timezone.c.o" \
"CMakeFiles/freerdp-locale.dir/xkb_layout_ids.c.o" \
"CMakeFiles/freerdp-locale.dir/keyboard_xkbfile.c.o"

# External object files for target freerdp-locale
freerdp__locale_EXTERNAL_OBJECTS =

libfreerdp/locale/libfreerdp-locale.so.1.1.0: libfreerdp/locale/CMakeFiles/freerdp-locale.dir/virtual_key_codes.c.o
libfreerdp/locale/libfreerdp-locale.so.1.1.0: libfreerdp/locale/CMakeFiles/freerdp-locale.dir/keyboard_layout.c.o
libfreerdp/locale/libfreerdp-locale.so.1.1.0: libfreerdp/locale/CMakeFiles/freerdp-locale.dir/keyboard.c.o
libfreerdp/locale/libfreerdp-locale.so.1.1.0: libfreerdp/locale/CMakeFiles/freerdp-locale.dir/locale.c.o
libfreerdp/locale/libfreerdp-locale.so.1.1.0: libfreerdp/locale/CMakeFiles/freerdp-locale.dir/timezone.c.o
libfreerdp/locale/libfreerdp-locale.so.1.1.0: libfreerdp/locale/CMakeFiles/freerdp-locale.dir/xkb_layout_ids.c.o
libfreerdp/locale/libfreerdp-locale.so.1.1.0: libfreerdp/locale/CMakeFiles/freerdp-locale.dir/keyboard_xkbfile.c.o
libfreerdp/locale/libfreerdp-locale.so.1.1.0: libfreerdp/locale/CMakeFiles/freerdp-locale.dir/build.make
libfreerdp/locale/libfreerdp-locale.so.1.1.0: /usr/xorg/lib/libX11.so
libfreerdp/locale/libfreerdp-locale.so.1.1.0: /usr/xorg/lib/libxkbfile.so
libfreerdp/locale/libfreerdp-locale.so.1.1.0: libfreerdp/utils/libfreerdp-utils.so.1.1.0
libfreerdp/locale/libfreerdp-locale.so.1.1.0: winpr/libwinpr/crt/libwinpr-crt.so.0.1.0
libfreerdp/locale/libfreerdp-locale.so.1.1.0: winpr/libwinpr/synch/libwinpr-synch.so.0.1.0
libfreerdp/locale/libfreerdp-locale.so.1.1.0: winpr/libwinpr/handle/libwinpr-handle.so.0.1.0
libfreerdp/locale/libfreerdp-locale.so.1.1.0: libfreerdp/locale/CMakeFiles/freerdp-locale.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C shared library libfreerdp-locale.so"
	cd /f/libfreerdp/locale && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/freerdp-locale.dir/link.txt --verbose=$(VERBOSE)
	cd /f/libfreerdp/locale && $(CMAKE_COMMAND) -E cmake_symlink_library libfreerdp-locale.so.1.1.0 libfreerdp-locale.so.1.1 libfreerdp-locale.so

libfreerdp/locale/libfreerdp-locale.so.1.1: libfreerdp/locale/libfreerdp-locale.so.1.1.0

libfreerdp/locale/libfreerdp-locale.so: libfreerdp/locale/libfreerdp-locale.so.1.1.0

# Rule to build all files generated by this target.
libfreerdp/locale/CMakeFiles/freerdp-locale.dir/build: libfreerdp/locale/libfreerdp-locale.so
.PHONY : libfreerdp/locale/CMakeFiles/freerdp-locale.dir/build

# Object files for target freerdp-locale
freerdp__locale_OBJECTS = \
"CMakeFiles/freerdp-locale.dir/virtual_key_codes.c.o" \
"CMakeFiles/freerdp-locale.dir/keyboard_layout.c.o" \
"CMakeFiles/freerdp-locale.dir/keyboard.c.o" \
"CMakeFiles/freerdp-locale.dir/locale.c.o" \
"CMakeFiles/freerdp-locale.dir/timezone.c.o" \
"CMakeFiles/freerdp-locale.dir/xkb_layout_ids.c.o" \
"CMakeFiles/freerdp-locale.dir/keyboard_xkbfile.c.o"

# External object files for target freerdp-locale
freerdp__locale_EXTERNAL_OBJECTS =

libfreerdp/locale/CMakeFiles/CMakeRelink.dir/libfreerdp-locale.so.1.1.0: libfreerdp/locale/CMakeFiles/freerdp-locale.dir/virtual_key_codes.c.o
libfreerdp/locale/CMakeFiles/CMakeRelink.dir/libfreerdp-locale.so.1.1.0: libfreerdp/locale/CMakeFiles/freerdp-locale.dir/keyboard_layout.c.o
libfreerdp/locale/CMakeFiles/CMakeRelink.dir/libfreerdp-locale.so.1.1.0: libfreerdp/locale/CMakeFiles/freerdp-locale.dir/keyboard.c.o
libfreerdp/locale/CMakeFiles/CMakeRelink.dir/libfreerdp-locale.so.1.1.0: libfreerdp/locale/CMakeFiles/freerdp-locale.dir/locale.c.o
libfreerdp/locale/CMakeFiles/CMakeRelink.dir/libfreerdp-locale.so.1.1.0: libfreerdp/locale/CMakeFiles/freerdp-locale.dir/timezone.c.o
libfreerdp/locale/CMakeFiles/CMakeRelink.dir/libfreerdp-locale.so.1.1.0: libfreerdp/locale/CMakeFiles/freerdp-locale.dir/xkb_layout_ids.c.o
libfreerdp/locale/CMakeFiles/CMakeRelink.dir/libfreerdp-locale.so.1.1.0: libfreerdp/locale/CMakeFiles/freerdp-locale.dir/keyboard_xkbfile.c.o
libfreerdp/locale/CMakeFiles/CMakeRelink.dir/libfreerdp-locale.so.1.1.0: libfreerdp/locale/CMakeFiles/freerdp-locale.dir/build.make
libfreerdp/locale/CMakeFiles/CMakeRelink.dir/libfreerdp-locale.so.1.1.0: /usr/xorg/lib/libX11.so
libfreerdp/locale/CMakeFiles/CMakeRelink.dir/libfreerdp-locale.so.1.1.0: /usr/xorg/lib/libxkbfile.so
libfreerdp/locale/CMakeFiles/CMakeRelink.dir/libfreerdp-locale.so.1.1.0: libfreerdp/utils/libfreerdp-utils.so.1.1.0
libfreerdp/locale/CMakeFiles/CMakeRelink.dir/libfreerdp-locale.so.1.1.0: winpr/libwinpr/crt/libwinpr-crt.so.0.1.0
libfreerdp/locale/CMakeFiles/CMakeRelink.dir/libfreerdp-locale.so.1.1.0: winpr/libwinpr/synch/libwinpr-synch.so.0.1.0
libfreerdp/locale/CMakeFiles/CMakeRelink.dir/libfreerdp-locale.so.1.1.0: winpr/libwinpr/handle/libwinpr-handle.so.0.1.0
libfreerdp/locale/CMakeFiles/CMakeRelink.dir/libfreerdp-locale.so.1.1.0: libfreerdp/locale/CMakeFiles/freerdp-locale.dir/relink.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C shared library CMakeFiles/CMakeRelink.dir/libfreerdp-locale.so"
	cd /f/libfreerdp/locale && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/freerdp-locale.dir/relink.txt --verbose=$(VERBOSE)
	cd /f/libfreerdp/locale && $(CMAKE_COMMAND) -E cmake_symlink_library CMakeFiles/CMakeRelink.dir/libfreerdp-locale.so.1.1.0 CMakeFiles/CMakeRelink.dir/libfreerdp-locale.so.1.1 CMakeFiles/CMakeRelink.dir/libfreerdp-locale.so

libfreerdp/locale/CMakeFiles/CMakeRelink.dir/libfreerdp-locale.so.1.1: libfreerdp/locale/CMakeFiles/CMakeRelink.dir/libfreerdp-locale.so.1.1.0

libfreerdp/locale/CMakeFiles/CMakeRelink.dir/libfreerdp-locale.so: libfreerdp/locale/CMakeFiles/CMakeRelink.dir/libfreerdp-locale.so.1.1.0

# Rule to relink during preinstall.
libfreerdp/locale/CMakeFiles/freerdp-locale.dir/preinstall: libfreerdp/locale/CMakeFiles/CMakeRelink.dir/libfreerdp-locale.so
.PHONY : libfreerdp/locale/CMakeFiles/freerdp-locale.dir/preinstall

libfreerdp/locale/CMakeFiles/freerdp-locale.dir/requires: libfreerdp/locale/CMakeFiles/freerdp-locale.dir/virtual_key_codes.c.o.requires
libfreerdp/locale/CMakeFiles/freerdp-locale.dir/requires: libfreerdp/locale/CMakeFiles/freerdp-locale.dir/keyboard_layout.c.o.requires
libfreerdp/locale/CMakeFiles/freerdp-locale.dir/requires: libfreerdp/locale/CMakeFiles/freerdp-locale.dir/keyboard.c.o.requires
libfreerdp/locale/CMakeFiles/freerdp-locale.dir/requires: libfreerdp/locale/CMakeFiles/freerdp-locale.dir/locale.c.o.requires
libfreerdp/locale/CMakeFiles/freerdp-locale.dir/requires: libfreerdp/locale/CMakeFiles/freerdp-locale.dir/timezone.c.o.requires
libfreerdp/locale/CMakeFiles/freerdp-locale.dir/requires: libfreerdp/locale/CMakeFiles/freerdp-locale.dir/xkb_layout_ids.c.o.requires
libfreerdp/locale/CMakeFiles/freerdp-locale.dir/requires: libfreerdp/locale/CMakeFiles/freerdp-locale.dir/keyboard_xkbfile.c.o.requires
.PHONY : libfreerdp/locale/CMakeFiles/freerdp-locale.dir/requires

libfreerdp/locale/CMakeFiles/freerdp-locale.dir/clean:
	cd /f/libfreerdp/locale && $(CMAKE_COMMAND) -P CMakeFiles/freerdp-locale.dir/cmake_clean.cmake
.PHONY : libfreerdp/locale/CMakeFiles/freerdp-locale.dir/clean

libfreerdp/locale/CMakeFiles/freerdp-locale.dir/depend:
	cd /f && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /f /f/libfreerdp/locale /f /f/libfreerdp/locale /f/libfreerdp/locale/CMakeFiles/freerdp-locale.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : libfreerdp/locale/CMakeFiles/freerdp-locale.dir/depend

