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
CMAKE_SOURCE_DIR = /source/clients/freerdp-git-01102012

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /source/clients/freerdp-git-01102012

# Include any dependencies generated for this target.
include winpr/libwinpr/CMakeFiles/winpr.dir/depend.make

# Include the progress variables for this target.
include winpr/libwinpr/CMakeFiles/winpr.dir/progress.make

# Include the compile flags for this target's objects.
include winpr/libwinpr/CMakeFiles/winpr.dir/flags.make

# Object files for target winpr
winpr_OBJECTS =

# External object files for target winpr
winpr_EXTERNAL_OBJECTS = \
"/source/clients/freerdp-git-01102012/winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/alignment.c.o" \
"/source/clients/freerdp-git-01102012/winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/memory.c.o" \
"/source/clients/freerdp-git-01102012/winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/string.c.o" \
"/source/clients/freerdp-git-01102012/winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/ntlm.c.o" \
"/source/clients/freerdp-git-01102012/winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/print.c.o" \
"/source/clients/freerdp-git-01102012/winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/sam.c.o" \
"/source/clients/freerdp-git-01102012/winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/stream.c.o" \
"/source/clients/freerdp-git-01102012/winpr/libwinpr/heap/CMakeFiles/winpr-heap.dir/heap.c.o" \
"/source/clients/freerdp-git-01102012/winpr/libwinpr/path/CMakeFiles/winpr-path.dir/path.c.o" \
"/source/clients/freerdp-git-01102012/winpr/libwinpr/io/CMakeFiles/winpr-io.dir/io.c.o" \
"/source/clients/freerdp-git-01102012/winpr/libwinpr/file/CMakeFiles/winpr-file.dir/file.c.o" \
"/source/clients/freerdp-git-01102012/winpr/libwinpr/error/CMakeFiles/winpr-error.dir/error.c.o" \
"/source/clients/freerdp-git-01102012/winpr/libwinpr/environment/CMakeFiles/winpr-environment.dir/environment.c.o" \
"/source/clients/freerdp-git-01102012/winpr/libwinpr/interlocked/CMakeFiles/winpr-interlocked.dir/interlocked.c.o" \
"/source/clients/freerdp-git-01102012/winpr/libwinpr/handle/CMakeFiles/winpr-handle.dir/handle.c.o" \
"/source/clients/freerdp-git-01102012/winpr/libwinpr/handle/CMakeFiles/winpr-handle.dir/table.c.o" \
"/source/clients/freerdp-git-01102012/winpr/libwinpr/synch/CMakeFiles/winpr-synch.dir/address.c.o" \
"/source/clients/freerdp-git-01102012/winpr/libwinpr/synch/CMakeFiles/winpr-synch.dir/barrier.c.o" \
"/source/clients/freerdp-git-01102012/winpr/libwinpr/synch/CMakeFiles/winpr-synch.dir/condition.c.o" \
"/source/clients/freerdp-git-01102012/winpr/libwinpr/synch/CMakeFiles/winpr-synch.dir/critical.c.o" \
"/source/clients/freerdp-git-01102012/winpr/libwinpr/synch/CMakeFiles/winpr-synch.dir/event.c.o" \
"/source/clients/freerdp-git-01102012/winpr/libwinpr/synch/CMakeFiles/winpr-synch.dir/init.c.o" \
"/source/clients/freerdp-git-01102012/winpr/libwinpr/synch/CMakeFiles/winpr-synch.dir/mutex.c.o" \
"/source/clients/freerdp-git-01102012/winpr/libwinpr/synch/CMakeFiles/winpr-synch.dir/semaphore.c.o" \
"/source/clients/freerdp-git-01102012/winpr/libwinpr/synch/CMakeFiles/winpr-synch.dir/sleep.c.o" \
"/source/clients/freerdp-git-01102012/winpr/libwinpr/synch/CMakeFiles/winpr-synch.dir/srw.c.o" \
"/source/clients/freerdp-git-01102012/winpr/libwinpr/synch/CMakeFiles/winpr-synch.dir/synch.c.o" \
"/source/clients/freerdp-git-01102012/winpr/libwinpr/synch/CMakeFiles/winpr-synch.dir/timer.c.o" \
"/source/clients/freerdp-git-01102012/winpr/libwinpr/synch/CMakeFiles/winpr-synch.dir/wait.c.o" \
"/source/clients/freerdp-git-01102012/winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/process.c.o" \
"/source/clients/freerdp-git-01102012/winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/processor.c.o" \
"/source/clients/freerdp-git-01102012/winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/thread.c.o" \
"/source/clients/freerdp-git-01102012/winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/tls.c.o" \
"/source/clients/freerdp-git-01102012/winpr/libwinpr/sysinfo/CMakeFiles/winpr-sysinfo.dir/sysinfo.c.o" \
"/source/clients/freerdp-git-01102012/winpr/libwinpr/bcrypt/CMakeFiles/winpr-bcrypt.dir/bcrypt.c.o" \
"/source/clients/freerdp-git-01102012/winpr/libwinpr/dsparse/CMakeFiles/winpr-dsparse.dir/dsparse.c.o" \
"/source/clients/freerdp-git-01102012/winpr/libwinpr/asn1/CMakeFiles/winpr-asn1.dir/asn1.c.o" \
"/source/clients/freerdp-git-01102012/winpr/libwinpr/rpc/CMakeFiles/winpr-rpc.dir/rpc.c.o" \
"/source/clients/freerdp-git-01102012/winpr/libwinpr/rpc/CMakeFiles/winpr-rpc.dir/ndr.c.o" \
"/source/clients/freerdp-git-01102012/winpr/libwinpr/rpc/CMakeFiles/winpr-rpc.dir/ndr_array.c.o" \
"/source/clients/freerdp-git-01102012/winpr/libwinpr/rpc/CMakeFiles/winpr-rpc.dir/ndr_context.c.o" \
"/source/clients/freerdp-git-01102012/winpr/libwinpr/rpc/CMakeFiles/winpr-rpc.dir/ndr_correlation.c.o" \
"/source/clients/freerdp-git-01102012/winpr/libwinpr/rpc/CMakeFiles/winpr-rpc.dir/ndr_pointer.c.o" \
"/source/clients/freerdp-git-01102012/winpr/libwinpr/rpc/CMakeFiles/winpr-rpc.dir/ndr_private.c.o" \
"/source/clients/freerdp-git-01102012/winpr/libwinpr/rpc/CMakeFiles/winpr-rpc.dir/ndr_simple.c.o" \
"/source/clients/freerdp-git-01102012/winpr/libwinpr/rpc/CMakeFiles/winpr-rpc.dir/ndr_string.c.o" \
"/source/clients/freerdp-git-01102012/winpr/libwinpr/rpc/CMakeFiles/winpr-rpc.dir/ndr_structure.c.o" \
"/source/clients/freerdp-git-01102012/winpr/libwinpr/rpc/CMakeFiles/winpr-rpc.dir/ndr_union.c.o" \
"/source/clients/freerdp-git-01102012/winpr/libwinpr/rpc/CMakeFiles/winpr-rpc.dir/midl.c.o" \
"/source/clients/freerdp-git-01102012/winpr/libwinpr/sspicli/CMakeFiles/winpr-sspicli.dir/sspicli.c.o" \
"/source/clients/freerdp-git-01102012/winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/NTLM/ntlm_av_pairs.c.o" \
"/source/clients/freerdp-git-01102012/winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/NTLM/ntlm_compute.c.o" \
"/source/clients/freerdp-git-01102012/winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/NTLM/ntlm_message.c.o" \
"/source/clients/freerdp-git-01102012/winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/NTLM/ntlm.c.o" \
"/source/clients/freerdp-git-01102012/winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/Negotiate/negotiate.c.o" \
"/source/clients/freerdp-git-01102012/winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/Schannel/schannel.c.o" \
"/source/clients/freerdp-git-01102012/winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/CredSSP/credssp.c.o" \
"/source/clients/freerdp-git-01102012/winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/sspi.c.o" \
"/source/clients/freerdp-git-01102012/winpr/libwinpr/registry/CMakeFiles/winpr-registry.dir/registry_reg.c.o" \
"/source/clients/freerdp-git-01102012/winpr/libwinpr/registry/CMakeFiles/winpr-registry.dir/registry.c.o" \
"/source/clients/freerdp-git-01102012/winpr/libwinpr/library/CMakeFiles/winpr-library.dir/library.c.o" \
"/source/clients/freerdp-git-01102012/winpr/libwinpr/timezone/CMakeFiles/winpr-timezone.dir/timezone.c.o" \
"/source/clients/freerdp-git-01102012/winpr/libwinpr/winsock/CMakeFiles/winpr-winsock.dir/winsock.c.o" \
"/source/clients/freerdp-git-01102012/winpr/libwinpr/winhttp/CMakeFiles/winpr-winhttp.dir/winhttp.c.o"

winpr/libwinpr/libwinpr.a: winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/alignment.c.o
winpr/libwinpr/libwinpr.a: winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/memory.c.o
winpr/libwinpr/libwinpr.a: winpr/libwinpr/crt/CMakeFiles/winpr-crt.dir/string.c.o
winpr/libwinpr/libwinpr.a: winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/ntlm.c.o
winpr/libwinpr/libwinpr.a: winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/print.c.o
winpr/libwinpr/libwinpr.a: winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/sam.c.o
winpr/libwinpr/libwinpr.a: winpr/libwinpr/utils/CMakeFiles/winpr-utils.dir/stream.c.o
winpr/libwinpr/libwinpr.a: winpr/libwinpr/heap/CMakeFiles/winpr-heap.dir/heap.c.o
winpr/libwinpr/libwinpr.a: winpr/libwinpr/path/CMakeFiles/winpr-path.dir/path.c.o
winpr/libwinpr/libwinpr.a: winpr/libwinpr/io/CMakeFiles/winpr-io.dir/io.c.o
winpr/libwinpr/libwinpr.a: winpr/libwinpr/file/CMakeFiles/winpr-file.dir/file.c.o
winpr/libwinpr/libwinpr.a: winpr/libwinpr/error/CMakeFiles/winpr-error.dir/error.c.o
winpr/libwinpr/libwinpr.a: winpr/libwinpr/environment/CMakeFiles/winpr-environment.dir/environment.c.o
winpr/libwinpr/libwinpr.a: winpr/libwinpr/interlocked/CMakeFiles/winpr-interlocked.dir/interlocked.c.o
winpr/libwinpr/libwinpr.a: winpr/libwinpr/handle/CMakeFiles/winpr-handle.dir/handle.c.o
winpr/libwinpr/libwinpr.a: winpr/libwinpr/handle/CMakeFiles/winpr-handle.dir/table.c.o
winpr/libwinpr/libwinpr.a: winpr/libwinpr/synch/CMakeFiles/winpr-synch.dir/address.c.o
winpr/libwinpr/libwinpr.a: winpr/libwinpr/synch/CMakeFiles/winpr-synch.dir/barrier.c.o
winpr/libwinpr/libwinpr.a: winpr/libwinpr/synch/CMakeFiles/winpr-synch.dir/condition.c.o
winpr/libwinpr/libwinpr.a: winpr/libwinpr/synch/CMakeFiles/winpr-synch.dir/critical.c.o
winpr/libwinpr/libwinpr.a: winpr/libwinpr/synch/CMakeFiles/winpr-synch.dir/event.c.o
winpr/libwinpr/libwinpr.a: winpr/libwinpr/synch/CMakeFiles/winpr-synch.dir/init.c.o
winpr/libwinpr/libwinpr.a: winpr/libwinpr/synch/CMakeFiles/winpr-synch.dir/mutex.c.o
winpr/libwinpr/libwinpr.a: winpr/libwinpr/synch/CMakeFiles/winpr-synch.dir/semaphore.c.o
winpr/libwinpr/libwinpr.a: winpr/libwinpr/synch/CMakeFiles/winpr-synch.dir/sleep.c.o
winpr/libwinpr/libwinpr.a: winpr/libwinpr/synch/CMakeFiles/winpr-synch.dir/srw.c.o
winpr/libwinpr/libwinpr.a: winpr/libwinpr/synch/CMakeFiles/winpr-synch.dir/synch.c.o
winpr/libwinpr/libwinpr.a: winpr/libwinpr/synch/CMakeFiles/winpr-synch.dir/timer.c.o
winpr/libwinpr/libwinpr.a: winpr/libwinpr/synch/CMakeFiles/winpr-synch.dir/wait.c.o
winpr/libwinpr/libwinpr.a: winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/process.c.o
winpr/libwinpr/libwinpr.a: winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/processor.c.o
winpr/libwinpr/libwinpr.a: winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/thread.c.o
winpr/libwinpr/libwinpr.a: winpr/libwinpr/thread/CMakeFiles/winpr-thread.dir/tls.c.o
winpr/libwinpr/libwinpr.a: winpr/libwinpr/sysinfo/CMakeFiles/winpr-sysinfo.dir/sysinfo.c.o
winpr/libwinpr/libwinpr.a: winpr/libwinpr/bcrypt/CMakeFiles/winpr-bcrypt.dir/bcrypt.c.o
winpr/libwinpr/libwinpr.a: winpr/libwinpr/dsparse/CMakeFiles/winpr-dsparse.dir/dsparse.c.o
winpr/libwinpr/libwinpr.a: winpr/libwinpr/asn1/CMakeFiles/winpr-asn1.dir/asn1.c.o
winpr/libwinpr/libwinpr.a: winpr/libwinpr/rpc/CMakeFiles/winpr-rpc.dir/rpc.c.o
winpr/libwinpr/libwinpr.a: winpr/libwinpr/rpc/CMakeFiles/winpr-rpc.dir/ndr.c.o
winpr/libwinpr/libwinpr.a: winpr/libwinpr/rpc/CMakeFiles/winpr-rpc.dir/ndr_array.c.o
winpr/libwinpr/libwinpr.a: winpr/libwinpr/rpc/CMakeFiles/winpr-rpc.dir/ndr_context.c.o
winpr/libwinpr/libwinpr.a: winpr/libwinpr/rpc/CMakeFiles/winpr-rpc.dir/ndr_correlation.c.o
winpr/libwinpr/libwinpr.a: winpr/libwinpr/rpc/CMakeFiles/winpr-rpc.dir/ndr_pointer.c.o
winpr/libwinpr/libwinpr.a: winpr/libwinpr/rpc/CMakeFiles/winpr-rpc.dir/ndr_private.c.o
winpr/libwinpr/libwinpr.a: winpr/libwinpr/rpc/CMakeFiles/winpr-rpc.dir/ndr_simple.c.o
winpr/libwinpr/libwinpr.a: winpr/libwinpr/rpc/CMakeFiles/winpr-rpc.dir/ndr_string.c.o
winpr/libwinpr/libwinpr.a: winpr/libwinpr/rpc/CMakeFiles/winpr-rpc.dir/ndr_structure.c.o
winpr/libwinpr/libwinpr.a: winpr/libwinpr/rpc/CMakeFiles/winpr-rpc.dir/ndr_union.c.o
winpr/libwinpr/libwinpr.a: winpr/libwinpr/rpc/CMakeFiles/winpr-rpc.dir/midl.c.o
winpr/libwinpr/libwinpr.a: winpr/libwinpr/sspicli/CMakeFiles/winpr-sspicli.dir/sspicli.c.o
winpr/libwinpr/libwinpr.a: winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/NTLM/ntlm_av_pairs.c.o
winpr/libwinpr/libwinpr.a: winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/NTLM/ntlm_compute.c.o
winpr/libwinpr/libwinpr.a: winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/NTLM/ntlm_message.c.o
winpr/libwinpr/libwinpr.a: winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/NTLM/ntlm.c.o
winpr/libwinpr/libwinpr.a: winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/Negotiate/negotiate.c.o
winpr/libwinpr/libwinpr.a: winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/Schannel/schannel.c.o
winpr/libwinpr/libwinpr.a: winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/CredSSP/credssp.c.o
winpr/libwinpr/libwinpr.a: winpr/libwinpr/sspi/CMakeFiles/winpr-sspi.dir/sspi.c.o
winpr/libwinpr/libwinpr.a: winpr/libwinpr/registry/CMakeFiles/winpr-registry.dir/registry_reg.c.o
winpr/libwinpr/libwinpr.a: winpr/libwinpr/registry/CMakeFiles/winpr-registry.dir/registry.c.o
winpr/libwinpr/libwinpr.a: winpr/libwinpr/library/CMakeFiles/winpr-library.dir/library.c.o
winpr/libwinpr/libwinpr.a: winpr/libwinpr/timezone/CMakeFiles/winpr-timezone.dir/timezone.c.o
winpr/libwinpr/libwinpr.a: winpr/libwinpr/winsock/CMakeFiles/winpr-winsock.dir/winsock.c.o
winpr/libwinpr/libwinpr.a: winpr/libwinpr/winhttp/CMakeFiles/winpr-winhttp.dir/winhttp.c.o
winpr/libwinpr/libwinpr.a: winpr/libwinpr/CMakeFiles/winpr.dir/build.make
winpr/libwinpr/libwinpr.a: winpr/libwinpr/CMakeFiles/winpr.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C static library libwinpr.a"
	cd /source/clients/freerdp-git-01102012/winpr/libwinpr && $(CMAKE_COMMAND) -P CMakeFiles/winpr.dir/cmake_clean_target.cmake
	cd /source/clients/freerdp-git-01102012/winpr/libwinpr && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/winpr.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
winpr/libwinpr/CMakeFiles/winpr.dir/build: winpr/libwinpr/libwinpr.a
.PHONY : winpr/libwinpr/CMakeFiles/winpr.dir/build

winpr/libwinpr/CMakeFiles/winpr.dir/requires:
.PHONY : winpr/libwinpr/CMakeFiles/winpr.dir/requires

winpr/libwinpr/CMakeFiles/winpr.dir/clean:
	cd /source/clients/freerdp-git-01102012/winpr/libwinpr && $(CMAKE_COMMAND) -P CMakeFiles/winpr.dir/cmake_clean.cmake
.PHONY : winpr/libwinpr/CMakeFiles/winpr.dir/clean

winpr/libwinpr/CMakeFiles/winpr.dir/depend:
	cd /source/clients/freerdp-git-01102012 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /source/clients/freerdp-git-01102012 /source/clients/freerdp-git-01102012/winpr/libwinpr /source/clients/freerdp-git-01102012 /source/clients/freerdp-git-01102012/winpr/libwinpr /source/clients/freerdp-git-01102012/winpr/libwinpr/CMakeFiles/winpr.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : winpr/libwinpr/CMakeFiles/winpr.dir/depend

