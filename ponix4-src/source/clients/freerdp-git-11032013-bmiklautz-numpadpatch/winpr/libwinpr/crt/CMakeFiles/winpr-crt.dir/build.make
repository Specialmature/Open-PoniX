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
include winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/depend.make

# Include the progress variables for this target.
include winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/progress.make

# Include the compile flags for this target's objects.
include winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/flags.make

winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/alignment.c.o: winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/flags.make
winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/alignment.c.o: winpr/libwinpr/crt/alignment.c
	$(CMAKE_COMMAND) -E cmake_progress_report /source/clients/freerdp-git-11032013-bmiklautz-numpadpatch/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/alignment.c.o"
	cd /source/clients/freerdp-git-11032013-bmiklautz-numpadpatch/winpr/libwinpr/crt && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/winpr-crt.dir/alignment.c.o   -c /source/clients/freerdp-git-11032013-bmiklautz-numpadpatch/winpr/libwinpr/crt/alignment.c

winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/alignment.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/winpr-crt.dir/alignment.c.i"
	cd /source/clients/freerdp-git-11032013-bmiklautz-numpadpatch/winpr/libwinpr/crt && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -E /source/clients/freerdp-git-11032013-bmiklautz-numpadpatch/winpr/libwinpr/crt/alignment.c > CMakeFiles/winpr-crt.dir/alignment.c.i

winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/alignment.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/winpr-crt.dir/alignment.c.s"
	cd /source/clients/freerdp-git-11032013-bmiklautz-numpadpatch/winpr/libwinpr/crt && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -S /source/clients/freerdp-git-11032013-bmiklautz-numpadpatch/winpr/libwinpr/crt/alignment.c -o CMakeFiles/winpr-crt.dir/alignment.c.s

winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/alignment.c.o.requires:
.PHONY : winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/alignment.c.o.requires

winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/alignment.c.o.provides: winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/alignment.c.o.requires
	$(MAKE) -f winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/build.make winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/alignment.c.o.provides.build
.PHONY : winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/alignment.c.o.provides

winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/alignment.c.o.provides.build: winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/alignment.c.o

winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/conversion.c.o: winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/flags.make
winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/conversion.c.o: winpr/libwinpr/crt/conversion.c
	$(CMAKE_COMMAND) -E cmake_progress_report /source/clients/freerdp-git-11032013-bmiklautz-numpadpatch/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/conversion.c.o"
	cd /source/clients/freerdp-git-11032013-bmiklautz-numpadpatch/winpr/libwinpr/crt && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/winpr-crt.dir/conversion.c.o   -c /source/clients/freerdp-git-11032013-bmiklautz-numpadpatch/winpr/libwinpr/crt/conversion.c

winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/conversion.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/winpr-crt.dir/conversion.c.i"
	cd /source/clients/freerdp-git-11032013-bmiklautz-numpadpatch/winpr/libwinpr/crt && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -E /source/clients/freerdp-git-11032013-bmiklautz-numpadpatch/winpr/libwinpr/crt/conversion.c > CMakeFiles/winpr-crt.dir/conversion.c.i

winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/conversion.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/winpr-crt.dir/conversion.c.s"
	cd /source/clients/freerdp-git-11032013-bmiklautz-numpadpatch/winpr/libwinpr/crt && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -S /source/clients/freerdp-git-11032013-bmiklautz-numpadpatch/winpr/libwinpr/crt/conversion.c -o CMakeFiles/winpr-crt.dir/conversion.c.s

winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/conversion.c.o.requires:
.PHONY : winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/conversion.c.o.requires

winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/conversion.c.o.provides: winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/conversion.c.o.requires
	$(MAKE) -f winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/build.make winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/conversion.c.o.provides.build
.PHONY : winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/conversion.c.o.provides

winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/conversion.c.o.provides.build: winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/conversion.c.o

winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/buffer.c.o: winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/flags.make
winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/buffer.c.o: winpr/libwinpr/crt/buffer.c
	$(CMAKE_COMMAND) -E cmake_progress_report /source/clients/freerdp-git-11032013-bmiklautz-numpadpatch/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/buffer.c.o"
	cd /source/clients/freerdp-git-11032013-bmiklautz-numpadpatch/winpr/libwinpr/crt && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/winpr-crt.dir/buffer.c.o   -c /source/clients/freerdp-git-11032013-bmiklautz-numpadpatch/winpr/libwinpr/crt/buffer.c

winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/buffer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/winpr-crt.dir/buffer.c.i"
	cd /source/clients/freerdp-git-11032013-bmiklautz-numpadpatch/winpr/libwinpr/crt && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -E /source/clients/freerdp-git-11032013-bmiklautz-numpadpatch/winpr/libwinpr/crt/buffer.c > CMakeFiles/winpr-crt.dir/buffer.c.i

winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/buffer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/winpr-crt.dir/buffer.c.s"
	cd /source/clients/freerdp-git-11032013-bmiklautz-numpadpatch/winpr/libwinpr/crt && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -S /source/clients/freerdp-git-11032013-bmiklautz-numpadpatch/winpr/libwinpr/crt/buffer.c -o CMakeFiles/winpr-crt.dir/buffer.c.s

winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/buffer.c.o.requires:
.PHONY : winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/buffer.c.o.requires

winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/buffer.c.o.provides: winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/buffer.c.o.requires
	$(MAKE) -f winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/build.make winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/buffer.c.o.provides.build
.PHONY : winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/buffer.c.o.provides

winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/buffer.c.o.provides.build: winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/buffer.c.o

winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/memory.c.o: winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/flags.make
winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/memory.c.o: winpr/libwinpr/crt/memory.c
	$(CMAKE_COMMAND) -E cmake_progress_report /source/clients/freerdp-git-11032013-bmiklautz-numpadpatch/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/memory.c.o"
	cd /source/clients/freerdp-git-11032013-bmiklautz-numpadpatch/winpr/libwinpr/crt && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/winpr-crt.dir/memory.c.o   -c /source/clients/freerdp-git-11032013-bmiklautz-numpadpatch/winpr/libwinpr/crt/memory.c

winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/memory.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/winpr-crt.dir/memory.c.i"
	cd /source/clients/freerdp-git-11032013-bmiklautz-numpadpatch/winpr/libwinpr/crt && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -E /source/clients/freerdp-git-11032013-bmiklautz-numpadpatch/winpr/libwinpr/crt/memory.c > CMakeFiles/winpr-crt.dir/memory.c.i

winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/memory.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/winpr-crt.dir/memory.c.s"
	cd /source/clients/freerdp-git-11032013-bmiklautz-numpadpatch/winpr/libwinpr/crt && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -S /source/clients/freerdp-git-11032013-bmiklautz-numpadpatch/winpr/libwinpr/crt/memory.c -o CMakeFiles/winpr-crt.dir/memory.c.s

winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/memory.c.o.requires:
.PHONY : winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/memory.c.o.requires

winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/memory.c.o.provides: winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/memory.c.o.requires
	$(MAKE) -f winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/build.make winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/memory.c.o.provides.build
.PHONY : winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/memory.c.o.provides

winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/memory.c.o.provides.build: winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/memory.c.o

winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/string.c.o: winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/flags.make
winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/string.c.o: winpr/libwinpr/crt/string.c
	$(CMAKE_COMMAND) -E cmake_progress_report /source/clients/freerdp-git-11032013-bmiklautz-numpadpatch/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/string.c.o"
	cd /source/clients/freerdp-git-11032013-bmiklautz-numpadpatch/winpr/libwinpr/crt && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/winpr-crt.dir/string.c.o   -c /source/clients/freerdp-git-11032013-bmiklautz-numpadpatch/winpr/libwinpr/crt/string.c

winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/string.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/winpr-crt.dir/string.c.i"
	cd /source/clients/freerdp-git-11032013-bmiklautz-numpadpatch/winpr/libwinpr/crt && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -E /source/clients/freerdp-git-11032013-bmiklautz-numpadpatch/winpr/libwinpr/crt/string.c > CMakeFiles/winpr-crt.dir/string.c.i

winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/string.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/winpr-crt.dir/string.c.s"
	cd /source/clients/freerdp-git-11032013-bmiklautz-numpadpatch/winpr/libwinpr/crt && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -S /source/clients/freerdp-git-11032013-bmiklautz-numpadpatch/winpr/libwinpr/crt/string.c -o CMakeFiles/winpr-crt.dir/string.c.s

winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/string.c.o.requires:
.PHONY : winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/string.c.o.requires

winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/string.c.o.provides: winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/string.c.o.requires
	$(MAKE) -f winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/build.make winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/string.c.o.provides.build
.PHONY : winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/string.c.o.provides

winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/string.c.o.provides.build: winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/string.c.o

# Object files for target winpr-crt
winpr__crt_OBJECTS = \
"CMakeFiles/winpr-crt.dir/alignment.c.o" \
"CMakeFiles/winpr-crt.dir/conversion.c.o" \
"CMakeFiles/winpr-crt.dir/buffer.c.o" \
"CMakeFiles/winpr-crt.dir/memory.c.o" \
"CMakeFiles/winpr-crt.dir/string.c.o"

# External object files for target winpr-crt
winpr__crt_EXTERNAL_OBJECTS =

winpr/libwinpr/crt/libwinpr-crt.so.0.1.0: winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/alignment.c.o
winpr/libwinpr/crt/libwinpr-crt.so.0.1.0: winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/conversion.c.o
winpr/libwinpr/crt/libwinpr-crt.so.0.1.0: winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/buffer.c.o
winpr/libwinpr/crt/libwinpr-crt.so.0.1.0: winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/memory.c.o
winpr/libwinpr/crt/libwinpr-crt.so.0.1.0: winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/string.c.o
winpr/libwinpr/crt/libwinpr-crt.so.0.1.0: winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/build.make
winpr/libwinpr/crt/libwinpr-crt.so.0.1.0: winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C shared library libwinpr-crt.so"
	cd /source/clients/freerdp-git-11032013-bmiklautz-numpadpatch/winpr/libwinpr/crt && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/winpr-crt.dir/link.txt --verbose=$(VERBOSE)
	cd /source/clients/freerdp-git-11032013-bmiklautz-numpadpatch/winpr/libwinpr/crt && $(CMAKE_COMMAND) -E cmake_symlink_library libwinpr-crt.so.0.1.0 libwinpr-crt.so.0.1 libwinpr-crt.so

winpr/libwinpr/crt/libwinpr-crt.so.0.1: winpr/libwinpr/crt/libwinpr-crt.so.0.1.0

winpr/libwinpr/crt/libwinpr-crt.so: winpr/libwinpr/crt/libwinpr-crt.so.0.1.0

# Rule to build all files generated by this target.
winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/build: winpr/libwinpr/crt/libwinpr-crt.so
.PHONY : winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/build

winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/requires: winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/alignment.c.o.requires
winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/requires: winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/conversion.c.o.requires
winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/requires: winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/buffer.c.o.requires
winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/requires: winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/memory.c.o.requires
winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/requires: winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/string.c.o.requires
.PHONY : winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/requires

winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/clean:
	cd /source/clients/freerdp-git-11032013-bmiklautz-numpadpatch/winpr/libwinpr/crt && $(CMAKE_COMMAND) -P CMakeFiles/winpr-crt.dir/cmake_clean.cmake
.PHONY : winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/clean

winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/depend:
	cd /source/clients/freerdp-git-11032013-bmiklautz-numpadpatch && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /source/clients/freerdp-git-11032013-bmiklautz-numpadpatch /source/clients/freerdp-git-11032013-bmiklautz-numpadpatch/winpr/libwinpr/crt /source/clients/freerdp-git-11032013-bmiklautz-numpadpatch /source/clients/freerdp-git-11032013-bmiklautz-numpadpatch/winpr/libwinpr/crt /source/clients/freerdp-git-11032013-bmiklautz-numpadpatch/winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/depend

