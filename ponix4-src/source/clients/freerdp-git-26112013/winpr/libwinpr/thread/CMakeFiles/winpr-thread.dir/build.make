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
CMAKE_SOURCE_DIR = /source/clients/freerdp-git-26112013

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /source/clients/freerdp-git-26112013

# Include any dependencies generated for this target.
include winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/depend.make

# Include the progress variables for this target.
include winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/progress.make

# Include the compile flags for this target's objects.
include winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/flags.make

winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/argv.c.o: winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/flags.make
winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/argv.c.o: winpr/libwinpr/thread/argv.c
	$(CMAKE_COMMAND) -E cmake_progress_report /source/clients/freerdp-git-26112013/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/argv.c.o"
	cd /source/clients/freerdp-git-26112013/winpr/libwinpr/thread && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/winpr-thread.dir/argv.c.o   -c /source/clients/freerdp-git-26112013/winpr/libwinpr/thread/argv.c

winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/argv.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/winpr-thread.dir/argv.c.i"
	cd /source/clients/freerdp-git-26112013/winpr/libwinpr/thread && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -E /source/clients/freerdp-git-26112013/winpr/libwinpr/thread/argv.c > CMakeFiles/winpr-thread.dir/argv.c.i

winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/argv.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/winpr-thread.dir/argv.c.s"
	cd /source/clients/freerdp-git-26112013/winpr/libwinpr/thread && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -S /source/clients/freerdp-git-26112013/winpr/libwinpr/thread/argv.c -o CMakeFiles/winpr-thread.dir/argv.c.s

winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/argv.c.o.requires:
.PHONY : winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/argv.c.o.requires

winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/argv.c.o.provides: winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/argv.c.o.requires
	$(MAKE) -f winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/build.make winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/argv.c.o.provides.build
.PHONY : winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/argv.c.o.provides

winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/argv.c.o.provides.build: winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/argv.c.o

winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/process.c.o: winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/flags.make
winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/process.c.o: winpr/libwinpr/thread/process.c
	$(CMAKE_COMMAND) -E cmake_progress_report /source/clients/freerdp-git-26112013/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/process.c.o"
	cd /source/clients/freerdp-git-26112013/winpr/libwinpr/thread && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/winpr-thread.dir/process.c.o   -c /source/clients/freerdp-git-26112013/winpr/libwinpr/thread/process.c

winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/process.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/winpr-thread.dir/process.c.i"
	cd /source/clients/freerdp-git-26112013/winpr/libwinpr/thread && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -E /source/clients/freerdp-git-26112013/winpr/libwinpr/thread/process.c > CMakeFiles/winpr-thread.dir/process.c.i

winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/process.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/winpr-thread.dir/process.c.s"
	cd /source/clients/freerdp-git-26112013/winpr/libwinpr/thread && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -S /source/clients/freerdp-git-26112013/winpr/libwinpr/thread/process.c -o CMakeFiles/winpr-thread.dir/process.c.s

winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/process.c.o.requires:
.PHONY : winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/process.c.o.requires

winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/process.c.o.provides: winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/process.c.o.requires
	$(MAKE) -f winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/build.make winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/process.c.o.provides.build
.PHONY : winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/process.c.o.provides

winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/process.c.o.provides.build: winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/process.c.o

winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/processor.c.o: winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/flags.make
winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/processor.c.o: winpr/libwinpr/thread/processor.c
	$(CMAKE_COMMAND) -E cmake_progress_report /source/clients/freerdp-git-26112013/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/processor.c.o"
	cd /source/clients/freerdp-git-26112013/winpr/libwinpr/thread && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/winpr-thread.dir/processor.c.o   -c /source/clients/freerdp-git-26112013/winpr/libwinpr/thread/processor.c

winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/processor.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/winpr-thread.dir/processor.c.i"
	cd /source/clients/freerdp-git-26112013/winpr/libwinpr/thread && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -E /source/clients/freerdp-git-26112013/winpr/libwinpr/thread/processor.c > CMakeFiles/winpr-thread.dir/processor.c.i

winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/processor.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/winpr-thread.dir/processor.c.s"
	cd /source/clients/freerdp-git-26112013/winpr/libwinpr/thread && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -S /source/clients/freerdp-git-26112013/winpr/libwinpr/thread/processor.c -o CMakeFiles/winpr-thread.dir/processor.c.s

winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/processor.c.o.requires:
.PHONY : winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/processor.c.o.requires

winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/processor.c.o.provides: winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/processor.c.o.requires
	$(MAKE) -f winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/build.make winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/processor.c.o.provides.build
.PHONY : winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/processor.c.o.provides

winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/processor.c.o.provides.build: winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/processor.c.o

winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/thread.c.o: winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/flags.make
winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/thread.c.o: winpr/libwinpr/thread/thread.c
	$(CMAKE_COMMAND) -E cmake_progress_report /source/clients/freerdp-git-26112013/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/thread.c.o"
	cd /source/clients/freerdp-git-26112013/winpr/libwinpr/thread && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/winpr-thread.dir/thread.c.o   -c /source/clients/freerdp-git-26112013/winpr/libwinpr/thread/thread.c

winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/thread.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/winpr-thread.dir/thread.c.i"
	cd /source/clients/freerdp-git-26112013/winpr/libwinpr/thread && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -E /source/clients/freerdp-git-26112013/winpr/libwinpr/thread/thread.c > CMakeFiles/winpr-thread.dir/thread.c.i

winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/thread.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/winpr-thread.dir/thread.c.s"
	cd /source/clients/freerdp-git-26112013/winpr/libwinpr/thread && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -S /source/clients/freerdp-git-26112013/winpr/libwinpr/thread/thread.c -o CMakeFiles/winpr-thread.dir/thread.c.s

winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/thread.c.o.requires:
.PHONY : winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/thread.c.o.requires

winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/thread.c.o.provides: winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/thread.c.o.requires
	$(MAKE) -f winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/build.make winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/thread.c.o.provides.build
.PHONY : winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/thread.c.o.provides

winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/thread.c.o.provides.build: winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/thread.c.o

winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/tls.c.o: winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/flags.make
winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/tls.c.o: winpr/libwinpr/thread/tls.c
	$(CMAKE_COMMAND) -E cmake_progress_report /source/clients/freerdp-git-26112013/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/tls.c.o"
	cd /source/clients/freerdp-git-26112013/winpr/libwinpr/thread && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/winpr-thread.dir/tls.c.o   -c /source/clients/freerdp-git-26112013/winpr/libwinpr/thread/tls.c

winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/tls.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/winpr-thread.dir/tls.c.i"
	cd /source/clients/freerdp-git-26112013/winpr/libwinpr/thread && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -E /source/clients/freerdp-git-26112013/winpr/libwinpr/thread/tls.c > CMakeFiles/winpr-thread.dir/tls.c.i

winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/tls.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/winpr-thread.dir/tls.c.s"
	cd /source/clients/freerdp-git-26112013/winpr/libwinpr/thread && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -S /source/clients/freerdp-git-26112013/winpr/libwinpr/thread/tls.c -o CMakeFiles/winpr-thread.dir/tls.c.s

winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/tls.c.o.requires:
.PHONY : winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/tls.c.o.requires

winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/tls.c.o.provides: winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/tls.c.o.requires
	$(MAKE) -f winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/build.make winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/tls.c.o.provides.build
.PHONY : winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/tls.c.o.provides

winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/tls.c.o.provides.build: winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/tls.c.o

winpr-thread: winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/argv.c.o
winpr-thread: winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/process.c.o
winpr-thread: winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/processor.c.o
winpr-thread: winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/thread.c.o
winpr-thread: winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/tls.c.o
winpr-thread: winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/build.make
.PHONY : winpr-thread

# Rule to build all files generated by this target.
winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/build: winpr-thread
.PHONY : winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/build

winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/requires: winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/argv.c.o.requires
winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/requires: winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/process.c.o.requires
winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/requires: winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/processor.c.o.requires
winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/requires: winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/thread.c.o.requires
winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/requires: winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/tls.c.o.requires
.PHONY : winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/requires

winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/clean:
	cd /source/clients/freerdp-git-26112013/winpr/libwinpr/thread && $(CMAKE_COMMAND) -P CMakeFiles/winpr-thread.dir/cmake_clean.cmake
.PHONY : winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/clean

winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/depend:
	cd /source/clients/freerdp-git-26112013 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /source/clients/freerdp-git-26112013 /source/clients/freerdp-git-26112013/winpr/libwinpr/thread /source/clients/freerdp-git-26112013 /source/clients/freerdp-git-26112013/winpr/libwinpr/thread /source/clients/freerdp-git-26112013/winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/depend

