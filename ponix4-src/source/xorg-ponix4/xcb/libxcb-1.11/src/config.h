/* src/config.h.  Generated from config.h.in by configure.  */
/* src/config.h.in.  Generated from configure.ac by autoheader.  */

/* Defined if GCC supports the visibility feature */
#define GCC_HAS_VISIBILITY /**/

/* Has Wraphelp.c needed for XDM AUTH protocols */
#define HASXDMAUTH 1

/* Define if your platform supports abstract sockets */
#define HAVE_ABSTRACT_SOCKETS 1

/* Define to 1 if you have the <dlfcn.h> header file. */
#define HAVE_DLFCN_H 1

/* getaddrinfo() function is available */
#define HAVE_GETADDRINFO 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define to 1 if you have the `is_system_labeled' function. */
/* #undef HAVE_IS_SYSTEM_LABELED */

/* launchd support available */
/* #undef HAVE_LAUNCHD */

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define if your platform supports sendmsg */
#define HAVE_SENDMSG 1

/* Have the sockaddr_un.sun_len member. */
/* #undef HAVE_SOCKADDR_SUN_LEN */

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <tsol/label.h> header file. */
/* #undef HAVE_TSOL_LABEL_H */

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define if not provided by <limits.h> */
/* #undef IOV_MAX */

/* Define to the sub-directory in which libtool stores uninstalled libraries.
   */
#define LT_OBJDIR ".libs/"

/* Name of package */
#define PACKAGE "libxcb"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "https://bugs.freedesktop.org/enter_bug.cgi?product=xcb"

/* Define to the full name of this package. */
#define PACKAGE_NAME "libxcb"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "libxcb 1.11"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "libxcb"

/* Define to the home page for this package. */
#define PACKAGE_URL ""

/* Define to the version of this package. */
#define PACKAGE_VERSION "1.11"

/* Major version of this package */
#define PACKAGE_VERSION_MAJOR 1

/* Minor version of this package */
#define PACKAGE_VERSION_MINOR 11

/* Patch version of this package */
#define PACKAGE_VERSION_PATCHLEVEL 0

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* poll() function is available */
#define USE_POLL 1

/* Enable extensions on AIX 3, Interix.  */
#ifndef _ALL_SOURCE
# define _ALL_SOURCE 1
#endif
/* Enable GNU extensions on systems that have them.  */
#ifndef _GNU_SOURCE
# define _GNU_SOURCE 1
#endif
/* Enable threading extensions on Solaris.  */
#ifndef _POSIX_PTHREAD_SEMANTICS
# define _POSIX_PTHREAD_SEMANTICS 1
#endif
/* Enable extensions on HP NonStop.  */
#ifndef _TANDEM_SOURCE
# define _TANDEM_SOURCE 1
#endif
/* Enable general extensions on Solaris.  */
#ifndef __EXTENSIONS__
# define __EXTENSIONS__ 1
#endif


/* Version number of package */
#define VERSION "1.11"

/* XCB buffer queue size */
#define XCB_QUEUE_BUFFER_SIZE 16384

/* Define to 1 if on MINIX. */
/* #undef _MINIX */

/* Define to 2 if the system does not provide POSIX.1 features except with
   this defined. */
/* #undef _POSIX_1_SOURCE */

/* Define to 1 if you need to in order for `stat' and other things to work. */
/* #undef _POSIX_SOURCE */

/* Defined if needed to expose struct msghdr.msg_control */
/* #undef _XOPEN_SOURCE */
