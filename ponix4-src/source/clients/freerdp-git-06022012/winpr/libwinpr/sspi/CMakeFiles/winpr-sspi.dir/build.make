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
CMAKE_SOURCE_DIR = /source/clients/freerdp-git-06022012

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /source/clients/freerdp-git-06022012

# Include any dependencies generated for this target.
include winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/depend.make

# Include the progress variables for this target.
include winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/progress.make

# Include the compile flags for this target's objects.
include winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/flags.make

winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/NTLM/ntlm_av_pairs.c.o: winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/flags.make
winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/NTLM/ntlm_av_pairs.c.o: winpr/libwinpr/sspi/NTLM/ntlm_av_pairs.c
	$(CMAKE_COMMAND) -E cmake_progress_report /source/clients/freerdp-git-06022012/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/NTLM/ntlm_av_pairs.c.o"
	cd /source/clients/freerdp-git-06022012/winpr/libwinpr/sspi && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/winpr-sspi.dir/NTLM/ntlm_av_pairs.c.o   -c /source/clients/freerdp-git-06022012/winpr/libwinpr/sspi/NTLM/ntlm_av_pairs.c

winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/NTLM/ntlm_av_pairs.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/winpr-sspi.dir/NTLM/ntlm_av_pairs.c.i"
	cd /source/clients/freerdp-git-06022012/winpr/libwinpr/sspi && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -E /source/clients/freerdp-git-06022012/winpr/libwinpr/sspi/NTLM/ntlm_av_pairs.c > CMakeFiles/winpr-sspi.dir/NTLM/ntlm_av_pairs.c.i

winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/NTLM/ntlm_av_pairs.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/winpr-sspi.dir/NTLM/ntlm_av_pairs.c.s"
	cd /source/clients/freerdp-git-06022012/winpr/libwinpr/sspi && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -S /source/clients/freerdp-git-06022012/winpr/libwinpr/sspi/NTLM/ntlm_av_pairs.c -o CMakeFiles/winpr-sspi.dir/NTLM/ntlm_av_pairs.c.s

winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/NTLM/ntlm_av_pairs.c.o.requires:
.PHONY : winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/NTLM/ntlm_av_pairs.c.o.requires

winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/NTLM/ntlm_av_pairs.c.o.provides: winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/NTLM/ntlm_av_pairs.c.o.requires
	$(MAKE) -f winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/build.make winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/NTLM/ntlm_av_pairs.c.o.provides.build
.PHONY : winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/NTLM/ntlm_av_pairs.c.o.provides

winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/NTLM/ntlm_av_pairs.c.o.provides.build: winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/NTLM/ntlm_av_pairs.c.o

winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/NTLM/ntlm_compute.c.o: winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/flags.make
winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/NTLM/ntlm_compute.c.o: winpr/libwinpr/sspi/NTLM/ntlm_compute.c
	$(CMAKE_COMMAND) -E cmake_progress_report /source/clients/freerdp-git-06022012/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/NTLM/ntlm_compute.c.o"
	cd /source/clients/freerdp-git-06022012/winpr/libwinpr/sspi && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/winpr-sspi.dir/NTLM/ntlm_compute.c.o   -c /source/clients/freerdp-git-06022012/winpr/libwinpr/sspi/NTLM/ntlm_compute.c

winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/NTLM/ntlm_compute.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/winpr-sspi.dir/NTLM/ntlm_compute.c.i"
	cd /source/clients/freerdp-git-06022012/winpr/libwinpr/sspi && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -E /source/clients/freerdp-git-06022012/winpr/libwinpr/sspi/NTLM/ntlm_compute.c > CMakeFiles/winpr-sspi.dir/NTLM/ntlm_compute.c.i

winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/NTLM/ntlm_compute.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/winpr-sspi.dir/NTLM/ntlm_compute.c.s"
	cd /source/clients/freerdp-git-06022012/winpr/libwinpr/sspi && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -S /source/clients/freerdp-git-06022012/winpr/libwinpr/sspi/NTLM/ntlm_compute.c -o CMakeFiles/winpr-sspi.dir/NTLM/ntlm_compute.c.s

winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/NTLM/ntlm_compute.c.o.requires:
.PHONY : winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/NTLM/ntlm_compute.c.o.requires

winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/NTLM/ntlm_compute.c.o.provides: winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/NTLM/ntlm_compute.c.o.requires
	$(MAKE) -f winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/build.make winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/NTLM/ntlm_compute.c.o.provides.build
.PHONY : winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/NTLM/ntlm_compute.c.o.provides

winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/NTLM/ntlm_compute.c.o.provides.build: winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/NTLM/ntlm_compute.c.o

winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/NTLM/ntlm_message.c.o: winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/flags.make
winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/NTLM/ntlm_message.c.o: winpr/libwinpr/sspi/NTLM/ntlm_message.c
	$(CMAKE_COMMAND) -E cmake_progress_report /source/clients/freerdp-git-06022012/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/NTLM/ntlm_message.c.o"
	cd /source/clients/freerdp-git-06022012/winpr/libwinpr/sspi && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/winpr-sspi.dir/NTLM/ntlm_message.c.o   -c /source/clients/freerdp-git-06022012/winpr/libwinpr/sspi/NTLM/ntlm_message.c

winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/NTLM/ntlm_message.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/winpr-sspi.dir/NTLM/ntlm_message.c.i"
	cd /source/clients/freerdp-git-06022012/winpr/libwinpr/sspi && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -E /source/clients/freerdp-git-06022012/winpr/libwinpr/sspi/NTLM/ntlm_message.c > CMakeFiles/winpr-sspi.dir/NTLM/ntlm_message.c.i

winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/NTLM/ntlm_message.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/winpr-sspi.dir/NTLM/ntlm_message.c.s"
	cd /source/clients/freerdp-git-06022012/winpr/libwinpr/sspi && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -S /source/clients/freerdp-git-06022012/winpr/libwinpr/sspi/NTLM/ntlm_message.c -o CMakeFiles/winpr-sspi.dir/NTLM/ntlm_message.c.s

winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/NTLM/ntlm_message.c.o.requires:
.PHONY : winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/NTLM/ntlm_message.c.o.requires

winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/NTLM/ntlm_message.c.o.provides: winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/NTLM/ntlm_message.c.o.requires
	$(MAKE) -f winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/build.make winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/NTLM/ntlm_message.c.o.provides.build
.PHONY : winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/NTLM/ntlm_message.c.o.provides

winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/NTLM/ntlm_message.c.o.provides.build: winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/NTLM/ntlm_message.c.o

winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/NTLM/ntlm.c.o: winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/flags.make
winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/NTLM/ntlm.c.o: winpr/libwinpr/sspi/NTLM/ntlm.c
	$(CMAKE_COMMAND) -E cmake_progress_report /source/clients/freerdp-git-06022012/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/NTLM/ntlm.c.o"
	cd /source/clients/freerdp-git-06022012/winpr/libwinpr/sspi && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/winpr-sspi.dir/NTLM/ntlm.c.o   -c /source/clients/freerdp-git-06022012/winpr/libwinpr/sspi/NTLM/ntlm.c

winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/NTLM/ntlm.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/winpr-sspi.dir/NTLM/ntlm.c.i"
	cd /source/clients/freerdp-git-06022012/winpr/libwinpr/sspi && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -E /source/clients/freerdp-git-06022012/winpr/libwinpr/sspi/NTLM/ntlm.c > CMakeFiles/winpr-sspi.dir/NTLM/ntlm.c.i

winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/NTLM/ntlm.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/winpr-sspi.dir/NTLM/ntlm.c.s"
	cd /source/clients/freerdp-git-06022012/winpr/libwinpr/sspi && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -S /source/clients/freerdp-git-06022012/winpr/libwinpr/sspi/NTLM/ntlm.c -o CMakeFiles/winpr-sspi.dir/NTLM/ntlm.c.s

winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/NTLM/ntlm.c.o.requires:
.PHONY : winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/NTLM/ntlm.c.o.requires

winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/NTLM/ntlm.c.o.provides: winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/NTLM/ntlm.c.o.requires
	$(MAKE) -f winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/build.make winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/NTLM/ntlm.c.o.provides.build
.PHONY : winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/NTLM/ntlm.c.o.provides

winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/NTLM/ntlm.c.o.provides.build: winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/NTLM/ntlm.c.o

winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/Negotiate/negotiate.c.o: winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/flags.make
winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/Negotiate/negotiate.c.o: winpr/libwinpr/sspi/Negotiate/negotiate.c
	$(CMAKE_COMMAND) -E cmake_progress_report /source/clients/freerdp-git-06022012/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/Negotiate/negotiate.c.o"
	cd /source/clients/freerdp-git-06022012/winpr/libwinpr/sspi && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/winpr-sspi.dir/Negotiate/negotiate.c.o   -c /source/clients/freerdp-git-06022012/winpr/libwinpr/sspi/Negotiate/negotiate.c

winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/Negotiate/negotiate.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/winpr-sspi.dir/Negotiate/negotiate.c.i"
	cd /source/clients/freerdp-git-06022012/winpr/libwinpr/sspi && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -E /source/clients/freerdp-git-06022012/winpr/libwinpr/sspi/Negotiate/negotiate.c > CMakeFiles/winpr-sspi.dir/Negotiate/negotiate.c.i

winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/Negotiate/negotiate.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/winpr-sspi.dir/Negotiate/negotiate.c.s"
	cd /source/clients/freerdp-git-06022012/winpr/libwinpr/sspi && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -S /source/clients/freerdp-git-06022012/winpr/libwinpr/sspi/Negotiate/negotiate.c -o CMakeFiles/winpr-sspi.dir/Negotiate/negotiate.c.s

winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/Negotiate/negotiate.c.o.requires:
.PHONY : winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/Negotiate/negotiate.c.o.requires

winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/Negotiate/negotiate.c.o.provides: winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/Negotiate/negotiate.c.o.requires
	$(MAKE) -f winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/build.make winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/Negotiate/negotiate.c.o.provides.build
.PHONY : winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/Negotiate/negotiate.c.o.provides

winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/Negotiate/negotiate.c.o.provides.build: winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/Negotiate/negotiate.c.o

winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/Schannel/schannel_openssl.c.o: winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/flags.make
winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/Schannel/schannel_openssl.c.o: winpr/libwinpr/sspi/Schannel/schannel_openssl.c
	$(CMAKE_COMMAND) -E cmake_progress_report /source/clients/freerdp-git-06022012/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/Schannel/schannel_openssl.c.o"
	cd /source/clients/freerdp-git-06022012/winpr/libwinpr/sspi && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/winpr-sspi.dir/Schannel/schannel_openssl.c.o   -c /source/clients/freerdp-git-06022012/winpr/libwinpr/sspi/Schannel/schannel_openssl.c

winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/Schannel/schannel_openssl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/winpr-sspi.dir/Schannel/schannel_openssl.c.i"
	cd /source/clients/freerdp-git-06022012/winpr/libwinpr/sspi && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -E /source/clients/freerdp-git-06022012/winpr/libwinpr/sspi/Schannel/schannel_openssl.c > CMakeFiles/winpr-sspi.dir/Schannel/schannel_openssl.c.i

winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/Schannel/schannel_openssl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/winpr-sspi.dir/Schannel/schannel_openssl.c.s"
	cd /source/clients/freerdp-git-06022012/winpr/libwinpr/sspi && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -S /source/clients/freerdp-git-06022012/winpr/libwinpr/sspi/Schannel/schannel_openssl.c -o CMakeFiles/winpr-sspi.dir/Schannel/schannel_openssl.c.s

winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/Schannel/schannel_openssl.c.o.requires:
.PHONY : winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/Schannel/schannel_openssl.c.o.requires

winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/Schannel/schannel_openssl.c.o.provides: winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/Schannel/schannel_openssl.c.o.requires
	$(MAKE) -f winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/build.make winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/Schannel/schannel_openssl.c.o.provides.build
.PHONY : winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/Schannel/schannel_openssl.c.o.provides

winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/Schannel/schannel_openssl.c.o.provides.build: winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/Schannel/schannel_openssl.c.o

winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/Schannel/schannel.c.o: winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/flags.make
winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/Schannel/schannel.c.o: winpr/libwinpr/sspi/Schannel/schannel.c
	$(CMAKE_COMMAND) -E cmake_progress_report /source/clients/freerdp-git-06022012/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/Schannel/schannel.c.o"
	cd /source/clients/freerdp-git-06022012/winpr/libwinpr/sspi && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/winpr-sspi.dir/Schannel/schannel.c.o   -c /source/clients/freerdp-git-06022012/winpr/libwinpr/sspi/Schannel/schannel.c

winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/Schannel/schannel.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/winpr-sspi.dir/Schannel/schannel.c.i"
	cd /source/clients/freerdp-git-06022012/winpr/libwinpr/sspi && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -E /source/clients/freerdp-git-06022012/winpr/libwinpr/sspi/Schannel/schannel.c > CMakeFiles/winpr-sspi.dir/Schannel/schannel.c.i

winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/Schannel/schannel.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/winpr-sspi.dir/Schannel/schannel.c.s"
	cd /source/clients/freerdp-git-06022012/winpr/libwinpr/sspi && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -S /source/clients/freerdp-git-06022012/winpr/libwinpr/sspi/Schannel/schannel.c -o CMakeFiles/winpr-sspi.dir/Schannel/schannel.c.s

winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/Schannel/schannel.c.o.requires:
.PHONY : winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/Schannel/schannel.c.o.requires

winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/Schannel/schannel.c.o.provides: winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/Schannel/schannel.c.o.requires
	$(MAKE) -f winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/build.make winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/Schannel/schannel.c.o.provides.build
.PHONY : winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/Schannel/schannel.c.o.provides

winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/Schannel/schannel.c.o.provides.build: winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/Schannel/schannel.c.o

winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/CredSSP/credssp.c.o: winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/flags.make
winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/CredSSP/credssp.c.o: winpr/libwinpr/sspi/CredSSP/credssp.c
	$(CMAKE_COMMAND) -E cmake_progress_report /source/clients/freerdp-git-06022012/CMakeFiles $(CMAKE_PROGRESS_8)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/CredSSP/credssp.c.o"
	cd /source/clients/freerdp-git-06022012/winpr/libwinpr/sspi && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/winpr-sspi.dir/CredSSP/credssp.c.o   -c /source/clients/freerdp-git-06022012/winpr/libwinpr/sspi/CredSSP/credssp.c

winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/CredSSP/credssp.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/winpr-sspi.dir/CredSSP/credssp.c.i"
	cd /source/clients/freerdp-git-06022012/winpr/libwinpr/sspi && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -E /source/clients/freerdp-git-06022012/winpr/libwinpr/sspi/CredSSP/credssp.c > CMakeFiles/winpr-sspi.dir/CredSSP/credssp.c.i

winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/CredSSP/credssp.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/winpr-sspi.dir/CredSSP/credssp.c.s"
	cd /source/clients/freerdp-git-06022012/winpr/libwinpr/sspi && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -S /source/clients/freerdp-git-06022012/winpr/libwinpr/sspi/CredSSP/credssp.c -o CMakeFiles/winpr-sspi.dir/CredSSP/credssp.c.s

winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/CredSSP/credssp.c.o.requires:
.PHONY : winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/CredSSP/credssp.c.o.requires

winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/CredSSP/credssp.c.o.provides: winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/CredSSP/credssp.c.o.requires
	$(MAKE) -f winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/build.make winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/CredSSP/credssp.c.o.provides.build
.PHONY : winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/CredSSP/credssp.c.o.provides

winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/CredSSP/credssp.c.o.provides.build: winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/CredSSP/credssp.c.o

winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/sspi.c.o: winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/flags.make
winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/sspi.c.o: winpr/libwinpr/sspi/sspi.c
	$(CMAKE_COMMAND) -E cmake_progress_report /source/clients/freerdp-git-06022012/CMakeFiles $(CMAKE_PROGRESS_9)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/sspi.c.o"
	cd /source/clients/freerdp-git-06022012/winpr/libwinpr/sspi && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/winpr-sspi.dir/sspi.c.o   -c /source/clients/freerdp-git-06022012/winpr/libwinpr/sspi/sspi.c

winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/sspi.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/winpr-sspi.dir/sspi.c.i"
	cd /source/clients/freerdp-git-06022012/winpr/libwinpr/sspi && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -E /source/clients/freerdp-git-06022012/winpr/libwinpr/sspi/sspi.c > CMakeFiles/winpr-sspi.dir/sspi.c.i

winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/sspi.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/winpr-sspi.dir/sspi.c.s"
	cd /source/clients/freerdp-git-06022012/winpr/libwinpr/sspi && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -S /source/clients/freerdp-git-06022012/winpr/libwinpr/sspi/sspi.c -o CMakeFiles/winpr-sspi.dir/sspi.c.s

winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/sspi.c.o.requires:
.PHONY : winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/sspi.c.o.requires

winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/sspi.c.o.provides: winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/sspi.c.o.requires
	$(MAKE) -f winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/build.make winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/sspi.c.o.provides.build
.PHONY : winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/sspi.c.o.provides

winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/sspi.c.o.provides.build: winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/sspi.c.o

# Object files for target winpr-sspi
winpr__sspi_OBJECTS = \
"CMakeFiles/winpr-sspi.dir/NTLM/ntlm_av_pairs.c.o" \
"CMakeFiles/winpr-sspi.dir/NTLM/ntlm_compute.c.o" \
"CMakeFiles/winpr-sspi.dir/NTLM/ntlm_message.c.o" \
"CMakeFiles/winpr-sspi.dir/NTLM/ntlm.c.o" \
"CMakeFiles/winpr-sspi.dir/Negotiate/negotiate.c.o" \
"CMakeFiles/winpr-sspi.dir/Schannel/schannel_openssl.c.o" \
"CMakeFiles/winpr-sspi.dir/Schannel/schannel.c.o" \
"CMakeFiles/winpr-sspi.dir/CredSSP/credssp.c.o" \
"CMakeFiles/winpr-sspi.dir/sspi.c.o"

# External object files for target winpr-sspi
winpr__sspi_EXTERNAL_OBJECTS =

winpr/libwinpr/sspi/libwinpr-sspi.so.0.1.0: winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/NTLM/ntlm_av_pairs.c.o
winpr/libwinpr/sspi/libwinpr-sspi.so.0.1.0: winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/NTLM/ntlm_compute.c.o
winpr/libwinpr/sspi/libwinpr-sspi.so.0.1.0: winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/NTLM/ntlm_message.c.o
winpr/libwinpr/sspi/libwinpr-sspi.so.0.1.0: winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/NTLM/ntlm.c.o
winpr/libwinpr/sspi/libwinpr-sspi.so.0.1.0: winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/Negotiate/negotiate.c.o
winpr/libwinpr/sspi/libwinpr-sspi.so.0.1.0: winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/Schannel/schannel_openssl.c.o
winpr/libwinpr/sspi/libwinpr-sspi.so.0.1.0: winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/Schannel/schannel.c.o
winpr/libwinpr/sspi/libwinpr-sspi.so.0.1.0: winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/CredSSP/credssp.c.o
winpr/libwinpr/sspi/libwinpr-sspi.so.0.1.0: winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/sspi.c.o
winpr/libwinpr/sspi/libwinpr-sspi.so.0.1.0: winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/build.make
winpr/libwinpr/sspi/libwinpr-sspi.so.0.1.0: /usr/lib/libz.so
winpr/libwinpr/sspi/libwinpr-sspi.so.0.1.0: /usr/lib/libssl.so
winpr/libwinpr/sspi/libwinpr-sspi.so.0.1.0: /usr/lib/libcrypto.so
winpr/libwinpr/sspi/libwinpr-sspi.so.0.1.0: /usr/lib/libz.so
winpr/libwinpr/sspi/libwinpr-sspi.so.0.1.0: winpr/libwinpr/crt/libwinpr-crt.so.0.1.0
winpr/libwinpr/sspi/libwinpr-sspi.so.0.1.0: winpr/libwinpr/sysinfo/libwinpr-sysinfo.so.0.1.0
winpr/libwinpr/sspi/libwinpr-sspi.so.0.1.0: winpr/libwinpr/registry/libwinpr-registry.so.0.1.0
winpr/libwinpr/sspi/libwinpr-sspi.so.0.1.0: winpr/libwinpr/crypto/libwinpr-crypto.so.0.1.0
winpr/libwinpr/sspi/libwinpr-sspi.so.0.1.0: winpr/libwinpr/utils/libwinpr-utils.so.0.1.0
winpr/libwinpr/sspi/libwinpr-sspi.so.0.1.0: /usr/lib/libz.so
winpr/libwinpr/sspi/libwinpr-sspi.so.0.1.0: /usr/lib/libssl.so
winpr/libwinpr/sspi/libwinpr-sspi.so.0.1.0: /usr/lib/libcrypto.so
winpr/libwinpr/sspi/libwinpr-sspi.so.0.1.0: winpr/libwinpr/crt/libwinpr-crt.so.0.1.0
winpr/libwinpr/sspi/libwinpr-sspi.so.0.1.0: winpr/libwinpr/synch/libwinpr-synch.so.0.1.0
winpr/libwinpr/sspi/libwinpr-sspi.so.0.1.0: winpr/libwinpr/handle/libwinpr-handle.so.0.1.0
winpr/libwinpr/sspi/libwinpr-sspi.so.0.1.0: winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C shared library libwinpr-sspi.so"
	cd /source/clients/freerdp-git-06022012/winpr/libwinpr/sspi && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/winpr-sspi.dir/link.txt --verbose=$(VERBOSE)
	cd /source/clients/freerdp-git-06022012/winpr/libwinpr/sspi && $(CMAKE_COMMAND) -E cmake_symlink_library libwinpr-sspi.so.0.1.0 libwinpr-sspi.so.0.1 libwinpr-sspi.so

winpr/libwinpr/sspi/libwinpr-sspi.so.0.1: winpr/libwinpr/sspi/libwinpr-sspi.so.0.1.0

winpr/libwinpr/sspi/libwinpr-sspi.so: winpr/libwinpr/sspi/libwinpr-sspi.so.0.1.0

# Rule to build all files generated by this target.
winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/build: winpr/libwinpr/sspi/libwinpr-sspi.so
.PHONY : winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/build

winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/requires: winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/NTLM/ntlm_av_pairs.c.o.requires
winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/requires: winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/NTLM/ntlm_compute.c.o.requires
winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/requires: winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/NTLM/ntlm_message.c.o.requires
winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/requires: winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/NTLM/ntlm.c.o.requires
winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/requires: winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/Negotiate/negotiate.c.o.requires
winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/requires: winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/Schannel/schannel_openssl.c.o.requires
winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/requires: winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/Schannel/schannel.c.o.requires
winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/requires: winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/CredSSP/credssp.c.o.requires
winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/requires: winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/sspi.c.o.requires
.PHONY : winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/requires

winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/clean:
	cd /source/clients/freerdp-git-06022012/winpr/libwinpr/sspi && $(CMAKE_COMMAND) -P CMakeFiles/winpr-sspi.dir/cmake_clean.cmake
.PHONY : winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/clean

winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/depend:
	cd /source/clients/freerdp-git-06022012 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /source/clients/freerdp-git-06022012 /source/clients/freerdp-git-06022012/winpr/libwinpr/sspi /source/clients/freerdp-git-06022012 /source/clients/freerdp-git-06022012/winpr/libwinpr/sspi /source/clients/freerdp-git-06022012/winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/depend

