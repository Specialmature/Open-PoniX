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
include winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/depend.make

# Include the progress variables for this target.
include winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/progress.make

# Include the compile flags for this target's objects.
include winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/flags.make

winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/ntlm.c.o: winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/flags.make
winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/ntlm.c.o: winpr/libwinpr/utils/ntlm.c
	$(CMAKE_COMMAND) -E cmake_progress_report /f/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/ntlm.c.o"
	cd /f/winpr/libwinpr/utils && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/winpr-utils.dir/ntlm.c.o   -c /f/winpr/libwinpr/utils/ntlm.c

winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/ntlm.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/winpr-utils.dir/ntlm.c.i"
	cd /f/winpr/libwinpr/utils && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -E /f/winpr/libwinpr/utils/ntlm.c > CMakeFiles/winpr-utils.dir/ntlm.c.i

winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/ntlm.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/winpr-utils.dir/ntlm.c.s"
	cd /f/winpr/libwinpr/utils && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -S /f/winpr/libwinpr/utils/ntlm.c -o CMakeFiles/winpr-utils.dir/ntlm.c.s

winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/ntlm.c.o.requires:
.PHONY : winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/ntlm.c.o.requires

winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/ntlm.c.o.provides: winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/ntlm.c.o.requires
	$(MAKE) -f winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/build.make winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/ntlm.c.o.provides.build
.PHONY : winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/ntlm.c.o.provides

winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/ntlm.c.o.provides.build: winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/ntlm.c.o

winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/print.c.o: winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/flags.make
winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/print.c.o: winpr/libwinpr/utils/print.c
	$(CMAKE_COMMAND) -E cmake_progress_report /f/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/print.c.o"
	cd /f/winpr/libwinpr/utils && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/winpr-utils.dir/print.c.o   -c /f/winpr/libwinpr/utils/print.c

winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/print.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/winpr-utils.dir/print.c.i"
	cd /f/winpr/libwinpr/utils && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -E /f/winpr/libwinpr/utils/print.c > CMakeFiles/winpr-utils.dir/print.c.i

winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/print.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/winpr-utils.dir/print.c.s"
	cd /f/winpr/libwinpr/utils && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -S /f/winpr/libwinpr/utils/print.c -o CMakeFiles/winpr-utils.dir/print.c.s

winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/print.c.o.requires:
.PHONY : winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/print.c.o.requires

winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/print.c.o.provides: winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/print.c.o.requires
	$(MAKE) -f winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/build.make winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/print.c.o.provides.build
.PHONY : winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/print.c.o.provides

winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/print.c.o.provides.build: winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/print.c.o

winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/sam.c.o: winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/flags.make
winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/sam.c.o: winpr/libwinpr/utils/sam.c
	$(CMAKE_COMMAND) -E cmake_progress_report /f/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/sam.c.o"
	cd /f/winpr/libwinpr/utils && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/winpr-utils.dir/sam.c.o   -c /f/winpr/libwinpr/utils/sam.c

winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/sam.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/winpr-utils.dir/sam.c.i"
	cd /f/winpr/libwinpr/utils && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -E /f/winpr/libwinpr/utils/sam.c > CMakeFiles/winpr-utils.dir/sam.c.i

winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/sam.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/winpr-utils.dir/sam.c.s"
	cd /f/winpr/libwinpr/utils && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -S /f/winpr/libwinpr/utils/sam.c -o CMakeFiles/winpr-utils.dir/sam.c.s

winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/sam.c.o.requires:
.PHONY : winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/sam.c.o.requires

winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/sam.c.o.provides: winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/sam.c.o.requires
	$(MAKE) -f winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/build.make winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/sam.c.o.provides.build
.PHONY : winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/sam.c.o.provides

winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/sam.c.o.provides.build: winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/sam.c.o

winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/stream.c.o: winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/flags.make
winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/stream.c.o: winpr/libwinpr/utils/stream.c
	$(CMAKE_COMMAND) -E cmake_progress_report /f/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/stream.c.o"
	cd /f/winpr/libwinpr/utils && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/winpr-utils.dir/stream.c.o   -c /f/winpr/libwinpr/utils/stream.c

winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/stream.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/winpr-utils.dir/stream.c.i"
	cd /f/winpr/libwinpr/utils && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -E /f/winpr/libwinpr/utils/stream.c > CMakeFiles/winpr-utils.dir/stream.c.i

winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/stream.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/winpr-utils.dir/stream.c.s"
	cd /f/winpr/libwinpr/utils && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -S /f/winpr/libwinpr/utils/stream.c -o CMakeFiles/winpr-utils.dir/stream.c.s

winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/stream.c.o.requires:
.PHONY : winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/stream.c.o.requires

winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/stream.c.o.provides: winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/stream.c.o.requires
	$(MAKE) -f winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/build.make winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/stream.c.o.provides.build
.PHONY : winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/stream.c.o.provides

winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/stream.c.o.provides.build: winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/stream.c.o

# Object files for target winpr-utils
winpr__utils_OBJECTS = \
"CMakeFiles/winpr-utils.dir/ntlm.c.o" \
"CMakeFiles/winpr-utils.dir/print.c.o" \
"CMakeFiles/winpr-utils.dir/sam.c.o" \
"CMakeFiles/winpr-utils.dir/stream.c.o"

# External object files for target winpr-utils
winpr__utils_EXTERNAL_OBJECTS =

winpr/libwinpr/utils/libwinpr-utils.so.0.1.0: winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/ntlm.c.o
winpr/libwinpr/utils/libwinpr-utils.so.0.1.0: winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/print.c.o
winpr/libwinpr/utils/libwinpr-utils.so.0.1.0: winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/sam.c.o
winpr/libwinpr/utils/libwinpr-utils.so.0.1.0: winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/stream.c.o
winpr/libwinpr/utils/libwinpr-utils.so.0.1.0: winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/build.make
winpr/libwinpr/utils/libwinpr-utils.so.0.1.0: /usr/lib/libz.so
winpr/libwinpr/utils/libwinpr-utils.so.0.1.0: /usr/lib/libssl.so
winpr/libwinpr/utils/libwinpr-utils.so.0.1.0: /usr/lib/libcrypto.so
winpr/libwinpr/utils/libwinpr-utils.so.0.1.0: winpr/libwinpr/crt/libwinpr-crt.so.0.1.0
winpr/libwinpr/utils/libwinpr-utils.so.0.1.0: winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C shared library libwinpr-utils.so"
	cd /f/winpr/libwinpr/utils && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/winpr-utils.dir/link.txt --verbose=$(VERBOSE)
	cd /f/winpr/libwinpr/utils && $(CMAKE_COMMAND) -E cmake_symlink_library libwinpr-utils.so.0.1.0 libwinpr-utils.so.0.1 libwinpr-utils.so

winpr/libwinpr/utils/libwinpr-utils.so.0.1: winpr/libwinpr/utils/libwinpr-utils.so.0.1.0

winpr/libwinpr/utils/libwinpr-utils.so: winpr/libwinpr/utils/libwinpr-utils.so.0.1.0

# Rule to build all files generated by this target.
winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/build: winpr/libwinpr/utils/libwinpr-utils.so
.PHONY : winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/build

# Object files for target winpr-utils
winpr__utils_OBJECTS = \
"CMakeFiles/winpr-utils.dir/ntlm.c.o" \
"CMakeFiles/winpr-utils.dir/print.c.o" \
"CMakeFiles/winpr-utils.dir/sam.c.o" \
"CMakeFiles/winpr-utils.dir/stream.c.o"

# External object files for target winpr-utils
winpr__utils_EXTERNAL_OBJECTS =

winpr/libwinpr/utils/CMakeFiles/CMakeRelink.dir/libwinpr-utils.so.0.1.0: winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/ntlm.c.o
winpr/libwinpr/utils/CMakeFiles/CMakeRelink.dir/libwinpr-utils.so.0.1.0: winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/print.c.o
winpr/libwinpr/utils/CMakeFiles/CMakeRelink.dir/libwinpr-utils.so.0.1.0: winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/sam.c.o
winpr/libwinpr/utils/CMakeFiles/CMakeRelink.dir/libwinpr-utils.so.0.1.0: winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/stream.c.o
winpr/libwinpr/utils/CMakeFiles/CMakeRelink.dir/libwinpr-utils.so.0.1.0: winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/build.make
winpr/libwinpr/utils/CMakeFiles/CMakeRelink.dir/libwinpr-utils.so.0.1.0: /usr/lib/libz.so
winpr/libwinpr/utils/CMakeFiles/CMakeRelink.dir/libwinpr-utils.so.0.1.0: /usr/lib/libssl.so
winpr/libwinpr/utils/CMakeFiles/CMakeRelink.dir/libwinpr-utils.so.0.1.0: /usr/lib/libcrypto.so
winpr/libwinpr/utils/CMakeFiles/CMakeRelink.dir/libwinpr-utils.so.0.1.0: winpr/libwinpr/crt/libwinpr-crt.so.0.1.0
winpr/libwinpr/utils/CMakeFiles/CMakeRelink.dir/libwinpr-utils.so.0.1.0: winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/relink.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C shared library CMakeFiles/CMakeRelink.dir/libwinpr-utils.so"
	cd /f/winpr/libwinpr/utils && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/winpr-utils.dir/relink.txt --verbose=$(VERBOSE)
	cd /f/winpr/libwinpr/utils && $(CMAKE_COMMAND) -E cmake_symlink_library CMakeFiles/CMakeRelink.dir/libwinpr-utils.so.0.1.0 CMakeFiles/CMakeRelink.dir/libwinpr-utils.so.0.1 CMakeFiles/CMakeRelink.dir/libwinpr-utils.so

winpr/libwinpr/utils/CMakeFiles/CMakeRelink.dir/libwinpr-utils.so.0.1: winpr/libwinpr/utils/CMakeFiles/CMakeRelink.dir/libwinpr-utils.so.0.1.0

winpr/libwinpr/utils/CMakeFiles/CMakeRelink.dir/libwinpr-utils.so: winpr/libwinpr/utils/CMakeFiles/CMakeRelink.dir/libwinpr-utils.so.0.1.0

# Rule to relink during preinstall.
winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/preinstall: winpr/libwinpr/utils/CMakeFiles/CMakeRelink.dir/libwinpr-utils.so
.PHONY : winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/preinstall

winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/requires: winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/ntlm.c.o.requires
winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/requires: winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/print.c.o.requires
winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/requires: winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/sam.c.o.requires
winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/requires: winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/stream.c.o.requires
.PHONY : winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/requires

winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/clean:
	cd /f/winpr/libwinpr/utils && $(CMAKE_COMMAND) -P CMakeFiles/winpr-utils.dir/cmake_clean.cmake
.PHONY : winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/clean

winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/depend:
	cd /f && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /f /f/winpr/libwinpr/utils /f /f/winpr/libwinpr/utils /f/winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/depend

