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
CMAKE_SOURCE_DIR = /source/clients/freerdp-git-07062016

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /source/clients/freerdp-git-07062016

# Include any dependencies generated for this target.
include rdtk/librdtk/CMakeFiles/rdtk.dir/depend.make

# Include the progress variables for this target.
include rdtk/librdtk/CMakeFiles/rdtk.dir/progress.make

# Include the compile flags for this target's objects.
include rdtk/librdtk/CMakeFiles/rdtk.dir/flags.make

rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_resources.c.o: rdtk/librdtk/CMakeFiles/rdtk.dir/flags.make
rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_resources.c.o: rdtk/librdtk/rdtk_resources.c
	$(CMAKE_COMMAND) -E cmake_progress_report /source/clients/freerdp-git-07062016/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_resources.c.o"
	cd /source/clients/freerdp-git-07062016/rdtk/librdtk && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/rdtk.dir/rdtk_resources.c.o   -c /source/clients/freerdp-git-07062016/rdtk/librdtk/rdtk_resources.c

rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_resources.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/rdtk.dir/rdtk_resources.c.i"
	cd /source/clients/freerdp-git-07062016/rdtk/librdtk && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -E /source/clients/freerdp-git-07062016/rdtk/librdtk/rdtk_resources.c > CMakeFiles/rdtk.dir/rdtk_resources.c.i

rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_resources.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/rdtk.dir/rdtk_resources.c.s"
	cd /source/clients/freerdp-git-07062016/rdtk/librdtk && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -S /source/clients/freerdp-git-07062016/rdtk/librdtk/rdtk_resources.c -o CMakeFiles/rdtk.dir/rdtk_resources.c.s

rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_resources.c.o.requires:
.PHONY : rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_resources.c.o.requires

rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_resources.c.o.provides: rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_resources.c.o.requires
	$(MAKE) -f rdtk/librdtk/CMakeFiles/rdtk.dir/build.make rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_resources.c.o.provides.build
.PHONY : rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_resources.c.o.provides

rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_resources.c.o.provides.build: rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_resources.c.o

rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_surface.c.o: rdtk/librdtk/CMakeFiles/rdtk.dir/flags.make
rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_surface.c.o: rdtk/librdtk/rdtk_surface.c
	$(CMAKE_COMMAND) -E cmake_progress_report /source/clients/freerdp-git-07062016/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_surface.c.o"
	cd /source/clients/freerdp-git-07062016/rdtk/librdtk && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/rdtk.dir/rdtk_surface.c.o   -c /source/clients/freerdp-git-07062016/rdtk/librdtk/rdtk_surface.c

rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_surface.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/rdtk.dir/rdtk_surface.c.i"
	cd /source/clients/freerdp-git-07062016/rdtk/librdtk && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -E /source/clients/freerdp-git-07062016/rdtk/librdtk/rdtk_surface.c > CMakeFiles/rdtk.dir/rdtk_surface.c.i

rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_surface.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/rdtk.dir/rdtk_surface.c.s"
	cd /source/clients/freerdp-git-07062016/rdtk/librdtk && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -S /source/clients/freerdp-git-07062016/rdtk/librdtk/rdtk_surface.c -o CMakeFiles/rdtk.dir/rdtk_surface.c.s

rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_surface.c.o.requires:
.PHONY : rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_surface.c.o.requires

rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_surface.c.o.provides: rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_surface.c.o.requires
	$(MAKE) -f rdtk/librdtk/CMakeFiles/rdtk.dir/build.make rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_surface.c.o.provides.build
.PHONY : rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_surface.c.o.provides

rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_surface.c.o.provides.build: rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_surface.c.o

rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_font.c.o: rdtk/librdtk/CMakeFiles/rdtk.dir/flags.make
rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_font.c.o: rdtk/librdtk/rdtk_font.c
	$(CMAKE_COMMAND) -E cmake_progress_report /source/clients/freerdp-git-07062016/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_font.c.o"
	cd /source/clients/freerdp-git-07062016/rdtk/librdtk && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/rdtk.dir/rdtk_font.c.o   -c /source/clients/freerdp-git-07062016/rdtk/librdtk/rdtk_font.c

rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_font.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/rdtk.dir/rdtk_font.c.i"
	cd /source/clients/freerdp-git-07062016/rdtk/librdtk && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -E /source/clients/freerdp-git-07062016/rdtk/librdtk/rdtk_font.c > CMakeFiles/rdtk.dir/rdtk_font.c.i

rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_font.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/rdtk.dir/rdtk_font.c.s"
	cd /source/clients/freerdp-git-07062016/rdtk/librdtk && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -S /source/clients/freerdp-git-07062016/rdtk/librdtk/rdtk_font.c -o CMakeFiles/rdtk.dir/rdtk_font.c.s

rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_font.c.o.requires:
.PHONY : rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_font.c.o.requires

rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_font.c.o.provides: rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_font.c.o.requires
	$(MAKE) -f rdtk/librdtk/CMakeFiles/rdtk.dir/build.make rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_font.c.o.provides.build
.PHONY : rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_font.c.o.provides

rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_font.c.o.provides.build: rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_font.c.o

rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_button.c.o: rdtk/librdtk/CMakeFiles/rdtk.dir/flags.make
rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_button.c.o: rdtk/librdtk/rdtk_button.c
	$(CMAKE_COMMAND) -E cmake_progress_report /source/clients/freerdp-git-07062016/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_button.c.o"
	cd /source/clients/freerdp-git-07062016/rdtk/librdtk && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/rdtk.dir/rdtk_button.c.o   -c /source/clients/freerdp-git-07062016/rdtk/librdtk/rdtk_button.c

rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_button.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/rdtk.dir/rdtk_button.c.i"
	cd /source/clients/freerdp-git-07062016/rdtk/librdtk && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -E /source/clients/freerdp-git-07062016/rdtk/librdtk/rdtk_button.c > CMakeFiles/rdtk.dir/rdtk_button.c.i

rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_button.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/rdtk.dir/rdtk_button.c.s"
	cd /source/clients/freerdp-git-07062016/rdtk/librdtk && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -S /source/clients/freerdp-git-07062016/rdtk/librdtk/rdtk_button.c -o CMakeFiles/rdtk.dir/rdtk_button.c.s

rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_button.c.o.requires:
.PHONY : rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_button.c.o.requires

rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_button.c.o.provides: rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_button.c.o.requires
	$(MAKE) -f rdtk/librdtk/CMakeFiles/rdtk.dir/build.make rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_button.c.o.provides.build
.PHONY : rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_button.c.o.provides

rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_button.c.o.provides.build: rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_button.c.o

rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_label.c.o: rdtk/librdtk/CMakeFiles/rdtk.dir/flags.make
rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_label.c.o: rdtk/librdtk/rdtk_label.c
	$(CMAKE_COMMAND) -E cmake_progress_report /source/clients/freerdp-git-07062016/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_label.c.o"
	cd /source/clients/freerdp-git-07062016/rdtk/librdtk && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/rdtk.dir/rdtk_label.c.o   -c /source/clients/freerdp-git-07062016/rdtk/librdtk/rdtk_label.c

rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_label.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/rdtk.dir/rdtk_label.c.i"
	cd /source/clients/freerdp-git-07062016/rdtk/librdtk && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -E /source/clients/freerdp-git-07062016/rdtk/librdtk/rdtk_label.c > CMakeFiles/rdtk.dir/rdtk_label.c.i

rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_label.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/rdtk.dir/rdtk_label.c.s"
	cd /source/clients/freerdp-git-07062016/rdtk/librdtk && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -S /source/clients/freerdp-git-07062016/rdtk/librdtk/rdtk_label.c -o CMakeFiles/rdtk.dir/rdtk_label.c.s

rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_label.c.o.requires:
.PHONY : rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_label.c.o.requires

rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_label.c.o.provides: rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_label.c.o.requires
	$(MAKE) -f rdtk/librdtk/CMakeFiles/rdtk.dir/build.make rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_label.c.o.provides.build
.PHONY : rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_label.c.o.provides

rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_label.c.o.provides.build: rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_label.c.o

rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_nine_patch.c.o: rdtk/librdtk/CMakeFiles/rdtk.dir/flags.make
rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_nine_patch.c.o: rdtk/librdtk/rdtk_nine_patch.c
	$(CMAKE_COMMAND) -E cmake_progress_report /source/clients/freerdp-git-07062016/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_nine_patch.c.o"
	cd /source/clients/freerdp-git-07062016/rdtk/librdtk && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/rdtk.dir/rdtk_nine_patch.c.o   -c /source/clients/freerdp-git-07062016/rdtk/librdtk/rdtk_nine_patch.c

rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_nine_patch.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/rdtk.dir/rdtk_nine_patch.c.i"
	cd /source/clients/freerdp-git-07062016/rdtk/librdtk && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -E /source/clients/freerdp-git-07062016/rdtk/librdtk/rdtk_nine_patch.c > CMakeFiles/rdtk.dir/rdtk_nine_patch.c.i

rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_nine_patch.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/rdtk.dir/rdtk_nine_patch.c.s"
	cd /source/clients/freerdp-git-07062016/rdtk/librdtk && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -S /source/clients/freerdp-git-07062016/rdtk/librdtk/rdtk_nine_patch.c -o CMakeFiles/rdtk.dir/rdtk_nine_patch.c.s

rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_nine_patch.c.o.requires:
.PHONY : rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_nine_patch.c.o.requires

rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_nine_patch.c.o.provides: rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_nine_patch.c.o.requires
	$(MAKE) -f rdtk/librdtk/CMakeFiles/rdtk.dir/build.make rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_nine_patch.c.o.provides.build
.PHONY : rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_nine_patch.c.o.provides

rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_nine_patch.c.o.provides.build: rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_nine_patch.c.o

rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_text_field.c.o: rdtk/librdtk/CMakeFiles/rdtk.dir/flags.make
rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_text_field.c.o: rdtk/librdtk/rdtk_text_field.c
	$(CMAKE_COMMAND) -E cmake_progress_report /source/clients/freerdp-git-07062016/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_text_field.c.o"
	cd /source/clients/freerdp-git-07062016/rdtk/librdtk && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/rdtk.dir/rdtk_text_field.c.o   -c /source/clients/freerdp-git-07062016/rdtk/librdtk/rdtk_text_field.c

rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_text_field.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/rdtk.dir/rdtk_text_field.c.i"
	cd /source/clients/freerdp-git-07062016/rdtk/librdtk && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -E /source/clients/freerdp-git-07062016/rdtk/librdtk/rdtk_text_field.c > CMakeFiles/rdtk.dir/rdtk_text_field.c.i

rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_text_field.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/rdtk.dir/rdtk_text_field.c.s"
	cd /source/clients/freerdp-git-07062016/rdtk/librdtk && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -S /source/clients/freerdp-git-07062016/rdtk/librdtk/rdtk_text_field.c -o CMakeFiles/rdtk.dir/rdtk_text_field.c.s

rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_text_field.c.o.requires:
.PHONY : rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_text_field.c.o.requires

rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_text_field.c.o.provides: rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_text_field.c.o.requires
	$(MAKE) -f rdtk/librdtk/CMakeFiles/rdtk.dir/build.make rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_text_field.c.o.provides.build
.PHONY : rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_text_field.c.o.provides

rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_text_field.c.o.provides.build: rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_text_field.c.o

rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_engine.c.o: rdtk/librdtk/CMakeFiles/rdtk.dir/flags.make
rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_engine.c.o: rdtk/librdtk/rdtk_engine.c
	$(CMAKE_COMMAND) -E cmake_progress_report /source/clients/freerdp-git-07062016/CMakeFiles $(CMAKE_PROGRESS_8)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_engine.c.o"
	cd /source/clients/freerdp-git-07062016/rdtk/librdtk && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/rdtk.dir/rdtk_engine.c.o   -c /source/clients/freerdp-git-07062016/rdtk/librdtk/rdtk_engine.c

rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_engine.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/rdtk.dir/rdtk_engine.c.i"
	cd /source/clients/freerdp-git-07062016/rdtk/librdtk && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -E /source/clients/freerdp-git-07062016/rdtk/librdtk/rdtk_engine.c > CMakeFiles/rdtk.dir/rdtk_engine.c.i

rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_engine.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/rdtk.dir/rdtk_engine.c.s"
	cd /source/clients/freerdp-git-07062016/rdtk/librdtk && /toolchain/bin/i486-TSOL-linux-gnu-gcc  $(C_DEFINES) $(C_FLAGS) -S /source/clients/freerdp-git-07062016/rdtk/librdtk/rdtk_engine.c -o CMakeFiles/rdtk.dir/rdtk_engine.c.s

rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_engine.c.o.requires:
.PHONY : rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_engine.c.o.requires

rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_engine.c.o.provides: rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_engine.c.o.requires
	$(MAKE) -f rdtk/librdtk/CMakeFiles/rdtk.dir/build.make rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_engine.c.o.provides.build
.PHONY : rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_engine.c.o.provides

rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_engine.c.o.provides.build: rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_engine.c.o

# Object files for target rdtk
rdtk_OBJECTS = \
"CMakeFiles/rdtk.dir/rdtk_resources.c.o" \
"CMakeFiles/rdtk.dir/rdtk_surface.c.o" \
"CMakeFiles/rdtk.dir/rdtk_font.c.o" \
"CMakeFiles/rdtk.dir/rdtk_button.c.o" \
"CMakeFiles/rdtk.dir/rdtk_label.c.o" \
"CMakeFiles/rdtk.dir/rdtk_nine_patch.c.o" \
"CMakeFiles/rdtk.dir/rdtk_text_field.c.o" \
"CMakeFiles/rdtk.dir/rdtk_engine.c.o"

# External object files for target rdtk
rdtk_EXTERNAL_OBJECTS =

rdtk/librdtk/librdtk.a: rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_resources.c.o
rdtk/librdtk/librdtk.a: rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_surface.c.o
rdtk/librdtk/librdtk.a: rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_font.c.o
rdtk/librdtk/librdtk.a: rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_button.c.o
rdtk/librdtk/librdtk.a: rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_label.c.o
rdtk/librdtk/librdtk.a: rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_nine_patch.c.o
rdtk/librdtk/librdtk.a: rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_text_field.c.o
rdtk/librdtk/librdtk.a: rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_engine.c.o
rdtk/librdtk/librdtk.a: rdtk/librdtk/CMakeFiles/rdtk.dir/build.make
rdtk/librdtk/librdtk.a: rdtk/librdtk/CMakeFiles/rdtk.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C static library librdtk.a"
	cd /source/clients/freerdp-git-07062016/rdtk/librdtk && $(CMAKE_COMMAND) -P CMakeFiles/rdtk.dir/cmake_clean_target.cmake
	cd /source/clients/freerdp-git-07062016/rdtk/librdtk && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/rdtk.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
rdtk/librdtk/CMakeFiles/rdtk.dir/build: rdtk/librdtk/librdtk.a
.PHONY : rdtk/librdtk/CMakeFiles/rdtk.dir/build

rdtk/librdtk/CMakeFiles/rdtk.dir/requires: rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_resources.c.o.requires
rdtk/librdtk/CMakeFiles/rdtk.dir/requires: rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_surface.c.o.requires
rdtk/librdtk/CMakeFiles/rdtk.dir/requires: rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_font.c.o.requires
rdtk/librdtk/CMakeFiles/rdtk.dir/requires: rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_button.c.o.requires
rdtk/librdtk/CMakeFiles/rdtk.dir/requires: rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_label.c.o.requires
rdtk/librdtk/CMakeFiles/rdtk.dir/requires: rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_nine_patch.c.o.requires
rdtk/librdtk/CMakeFiles/rdtk.dir/requires: rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_text_field.c.o.requires
rdtk/librdtk/CMakeFiles/rdtk.dir/requires: rdtk/librdtk/CMakeFiles/rdtk.dir/rdtk_engine.c.o.requires
.PHONY : rdtk/librdtk/CMakeFiles/rdtk.dir/requires

rdtk/librdtk/CMakeFiles/rdtk.dir/clean:
	cd /source/clients/freerdp-git-07062016/rdtk/librdtk && $(CMAKE_COMMAND) -P CMakeFiles/rdtk.dir/cmake_clean.cmake
.PHONY : rdtk/librdtk/CMakeFiles/rdtk.dir/clean

rdtk/librdtk/CMakeFiles/rdtk.dir/depend:
	cd /source/clients/freerdp-git-07062016 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /source/clients/freerdp-git-07062016 /source/clients/freerdp-git-07062016/rdtk/librdtk /source/clients/freerdp-git-07062016 /source/clients/freerdp-git-07062016/rdtk/librdtk /source/clients/freerdp-git-07062016/rdtk/librdtk/CMakeFiles/rdtk.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : rdtk/librdtk/CMakeFiles/rdtk.dir/depend

