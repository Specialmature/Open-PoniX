#ifndef __CONFIG_H
#define __CONFIG_H

#define FREERDP_VERSION_MAJOR 1
#define FREERDP_VERSION_MINOR 1
#define FREERDP_VERSION_REVISION 0
#define FREERDP_VERSION_SUFFIX "dev"
#define FREERDP_API_VERSION "1.1"
#define FREERDP_VERSION "1.1.0"
#define FREERDP_VERSION_FULL "1.1.0-dev"
#define GIT_REVISION "n/a"

#define FREERDP_DATA_PATH "/freerdp/share/freerdp"
#define FREERDP_KEYMAP_PATH "/freerdp/share/freerdp/keymaps"
#define FREERDP_PLUGIN_PATH "lib/freerdp"

#define FREERDP_INSTALL_PREFIX "/freerdp"

#define FREERDP_LIBRARY_PATH "lib"

#define FREERDP_ADDIN_PATH "lib/freerdp"

/* Include files */
#define HAVE_FCNTL_H
#define HAVE_UNISTD_H
#define HAVE_STDINT_H
#define HAVE_INTTYPES_H
/* #undef HAVE_SYS_MODEM_H */
/* #undef HAVE_SYS_FILIO_H */
/* #undef HAVE_SYS_STRTIO_H */

#define HAVE_TM_GMTOFF


/* Options */
/* #undef WITH_PROFILER */
/* #undef WITH_SSE2 */
/* #undef WITH_NEON */
/* #undef WITH_NATIVE_SSPI */
/* #undef WITH_JPEG */
/* #undef WITH_WIN8 */

/* Plugins */
/* #undef STATIC_CHANNELS */
/* #undef WITH_RDPDR */


/* Debug */
/* #undef WITH_DEBUG_CERTIFICATE */
/* #undef WITH_DEBUG_CHANNELS */
/* #undef WITH_DEBUG_CLIPRDR */
/* #undef WITH_DEBUG_DVC */
/* #undef WITH_DEBUG_GDI */
/* #undef WITH_DEBUG_KBD */
/* #undef WITH_DEBUG_LICENSE */
/* #undef WITH_DEBUG_NEGO */
/* #undef WITH_DEBUG_NLA */
/* #undef WITH_DEBUG_NTLM */
/* #undef WITH_DEBUG_TSG */
/* #undef WITH_DEBUG_ORDERS */
/* #undef WITH_DEBUG_RAIL */
/* #undef WITH_DEBUG_RDP */
/* #undef WITH_DEBUG_REDIR */
/* #undef WITH_DEBUG_RFX */
/* #undef WITH_DEBUG_SCARD */
/* #undef WITH_DEBUG_SVC */
/* #undef WITH_DEBUG_TIMEZONE */
/* #undef WITH_DEBUG_TRANSPORT */
/* #undef WITH_DEBUG_WND */
/* #undef WITH_DEBUG_X11 */
/* #undef WITH_DEBUG_X11_CLIPRDR */
/* #undef WITH_DEBUG_X11_LOCAL_MOVESIZE */
/* #undef WITH_DEBUG_XV */
#endif
