cmd_scripts/mod/modpost.o := gcc -Wp,-MD,scripts/mod/.modpost.o.d -Wall -Wmissing-prototypes -Wstrict-prototypes -O2 -fomit-frame-pointer     -c -o scripts/mod/modpost.o scripts/mod/modpost.c

source_scripts/mod/modpost.o := scripts/mod/modpost.c

deps_scripts/mod/modpost.o := \
    $(wildcard include/config/modversions.h) \
    $(wildcard include/config/module/srcversion/all.h) \
    $(wildcard include/config/have/underscore/symbol/prefix.h) \
    $(wildcard include/config/relocatable.h) \
    $(wildcard include/config/module/unload.h) \
    $(wildcard include/config/debug/section/mismatch.h) \
  /toolchain/i486-TSOL-linux-gnu/sysroot/usr/include/stdio.h \
  /toolchain/i486-TSOL-linux-gnu/sysroot/usr/include/features.h \
  /toolchain/i486-TSOL-linux-gnu/sysroot/usr/include/bits/predefs.h \
  /toolchain/i486-TSOL-linux-gnu/sysroot/usr/include/sys/cdefs.h \
  /toolchain/i486-TSOL-linux-gnu/sysroot/usr/include/bits/wordsize.h \
  /toolchain/i486-TSOL-linux-gnu/sysroot/usr/include/gnu/stubs.h \
  /toolchain/i486-TSOL-linux-gnu/sysroot/usr/include/gnu/stubs-32.h \
  /toolchain/i486-TSOL-linux-gnu/bin/../lib/gcc/i486-TSOL-linux-gnu/4.6.3/include/stddef.h \
  /toolchain/i486-TSOL-linux-gnu/sysroot/usr/include/bits/types.h \
  /toolchain/i486-TSOL-linux-gnu/sysroot/usr/include/bits/typesizes.h \
  /toolchain/i486-TSOL-linux-gnu/sysroot/usr/include/libio.h \
  /toolchain/i486-TSOL-linux-gnu/sysroot/usr/include/_G_config.h \
  /toolchain/i486-TSOL-linux-gnu/sysroot/usr/include/wchar.h \
  /toolchain/i486-TSOL-linux-gnu/bin/../lib/gcc/i486-TSOL-linux-gnu/4.6.3/include/stdarg.h \
  /toolchain/i486-TSOL-linux-gnu/sysroot/usr/include/bits/stdio_lim.h \
  /toolchain/i486-TSOL-linux-gnu/sysroot/usr/include/bits/sys_errlist.h \
  /toolchain/i486-TSOL-linux-gnu/sysroot/usr/include/bits/stdio.h \
  /toolchain/i486-TSOL-linux-gnu/sysroot/usr/include/ctype.h \
  /toolchain/i486-TSOL-linux-gnu/sysroot/usr/include/endian.h \
  /toolchain/i486-TSOL-linux-gnu/sysroot/usr/include/bits/endian.h \
  /toolchain/i486-TSOL-linux-gnu/sysroot/usr/include/bits/byteswap.h \
  /toolchain/i486-TSOL-linux-gnu/sysroot/usr/include/xlocale.h \
  /toolchain/i486-TSOL-linux-gnu/sysroot/usr/include/string.h \
  /toolchain/i486-TSOL-linux-gnu/sysroot/usr/include/bits/string.h \
  /toolchain/i486-TSOL-linux-gnu/sysroot/usr/include/bits/string2.h \
  /toolchain/i486-TSOL-linux-gnu/sysroot/usr/include/stdlib.h \
  /toolchain/i486-TSOL-linux-gnu/bin/../lib/gcc/i486-TSOL-linux-gnu/4.6.3/include-fixed/limits.h \
  /toolchain/i486-TSOL-linux-gnu/bin/../lib/gcc/i486-TSOL-linux-gnu/4.6.3/include-fixed/syslimits.h \
  /toolchain/i486-TSOL-linux-gnu/sysroot/usr/include/limits.h \
  /toolchain/i486-TSOL-linux-gnu/sysroot/usr/include/bits/posix1_lim.h \
  /toolchain/i486-TSOL-linux-gnu/sysroot/usr/include/bits/local_lim.h \
  /toolchain/i486-TSOL-linux-gnu/sysroot/usr/include/linux/limits.h \
  /toolchain/i486-TSOL-linux-gnu/sysroot/usr/include/bits/posix2_lim.h \
  /toolchain/i486-TSOL-linux-gnu/sysroot/usr/include/bits/xopen_lim.h \
  /toolchain/i486-TSOL-linux-gnu/bin/../lib/gcc/i486-TSOL-linux-gnu/4.6.3/include/stdbool.h \
  /toolchain/i486-TSOL-linux-gnu/sysroot/usr/include/errno.h \
  /toolchain/i486-TSOL-linux-gnu/sysroot/usr/include/bits/errno.h \
  /toolchain/i486-TSOL-linux-gnu/sysroot/usr/include/linux/errno.h \
  /toolchain/i486-TSOL-linux-gnu/sysroot/usr/include/asm/errno.h \
  /toolchain/i486-TSOL-linux-gnu/sysroot/usr/include/asm-generic/errno.h \
  /toolchain/i486-TSOL-linux-gnu/sysroot/usr/include/asm-generic/errno-base.h \
  scripts/mod/modpost.h \
  /toolchain/i486-TSOL-linux-gnu/sysroot/usr/include/bits/waitflags.h \
  /toolchain/i486-TSOL-linux-gnu/sysroot/usr/include/bits/waitstatus.h \
  /toolchain/i486-TSOL-linux-gnu/sysroot/usr/include/sys/types.h \
  /toolchain/i486-TSOL-linux-gnu/sysroot/usr/include/time.h \
  /toolchain/i486-TSOL-linux-gnu/sysroot/usr/include/sys/select.h \
  /toolchain/i486-TSOL-linux-gnu/sysroot/usr/include/bits/select.h \
  /toolchain/i486-TSOL-linux-gnu/sysroot/usr/include/bits/sigset.h \
  /toolchain/i486-TSOL-linux-gnu/sysroot/usr/include/bits/time.h \
  /toolchain/i486-TSOL-linux-gnu/sysroot/usr/include/sys/sysmacros.h \
  /toolchain/i486-TSOL-linux-gnu/sysroot/usr/include/bits/pthreadtypes.h \
  /toolchain/i486-TSOL-linux-gnu/sysroot/usr/include/alloca.h \
  /toolchain/i486-TSOL-linux-gnu/sysroot/usr/include/sys/stat.h \
  /toolchain/i486-TSOL-linux-gnu/sysroot/usr/include/bits/stat.h \
  /toolchain/i486-TSOL-linux-gnu/sysroot/usr/include/sys/mman.h \
  /toolchain/i486-TSOL-linux-gnu/sysroot/usr/include/bits/mman.h \
  /toolchain/i486-TSOL-linux-gnu/sysroot/usr/include/fcntl.h \
  /toolchain/i486-TSOL-linux-gnu/sysroot/usr/include/bits/fcntl.h \
  /toolchain/i486-TSOL-linux-gnu/sysroot/usr/include/bits/uio.h \
  /toolchain/i486-TSOL-linux-gnu/sysroot/usr/include/unistd.h \
  /toolchain/i486-TSOL-linux-gnu/sysroot/usr/include/bits/posix_opt.h \
  /toolchain/i486-TSOL-linux-gnu/sysroot/usr/include/bits/environments.h \
  /toolchain/i486-TSOL-linux-gnu/sysroot/usr/include/bits/confname.h \
  /toolchain/i486-TSOL-linux-gnu/sysroot/usr/include/getopt.h \
  /toolchain/i486-TSOL-linux-gnu/sysroot/usr/include/elf.h \
  /toolchain/i486-TSOL-linux-gnu/bin/../lib/gcc/i486-TSOL-linux-gnu/4.6.3/include/stdint.h \
  /toolchain/i486-TSOL-linux-gnu/sysroot/usr/include/stdint.h \
  /toolchain/i486-TSOL-linux-gnu/sysroot/usr/include/bits/wchar.h \
  scripts/mod/elfconfig.h \
  scripts/mod/../../include/linux/license.h \
  scripts/mod/../../include/linux/export.h \
    $(wildcard include/config/modules.h) \
    $(wildcard include/config/unused/symbols.h) \

scripts/mod/modpost.o: $(deps_scripts/mod/modpost.o)

$(deps_scripts/mod/modpost.o):
