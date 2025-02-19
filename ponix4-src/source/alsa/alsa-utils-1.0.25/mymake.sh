#!/bin/sh

#./configure --prefix=/tmp/alsa-utils-1025 --disable-xmlto --disable-alsatest --disable-alsaconf \
#--with-udev-rules-dir=/usr/etc/udev/rules.d --with-librt=no


./configure --prefix=/usr --disable-xmlto --disable-alsatest --disable-alsaconf \
--with-udev-rules-dir=/usr/etc/udev/rules.d --with-librt=no

#  --disable-nls           do not use Native Language Support
#  --disable-dependency-tracking  speeds up one-time build
#  --enable-dependency-tracking   do not reject slow dependency extractors
#  --disable-rpath         do not hardcode runtime library paths
#  --disable-alsatest      Do not try to compile and run a test Alsa program
#  --disable-alsamixer     Disable alsamixer compilation
#  --disable-alsaconf      Disable alsaconf packaging
#  --disable-alsaloop      Disable alsaloop packaging
#  --disable-xmlto         Disable man page creation via xmlto
#  --disable-largefile     omit support for large files
#
#Optional Packages:
#  --with-PACKAGE[=ARG]    use PACKAGE [ARG=yes]
#  --without-PACKAGE       do not use PACKAGE (same as --with-PACKAGE=no)
#  --with-gnu-ld           assume the C compiler uses GNU ld default=no
#  --with-libiconv-prefix[=DIR]  search for libiconv in DIR/include and DIR/lib
#  --without-libiconv-prefix     don't search for libiconv in includedir and libdir
#  --with-libintl-prefix[=DIR]  search for libintl in DIR/include and DIR/lib
#  --without-libintl-prefix     don't search for libintl in includedir and libdir
#  --with-alsa-prefix=PFX  Prefix where Alsa library is installed(optional)
#  --with-alsa-inc-prefix=PFX  Prefix where include libraries are (optional)
#  --with-librt            Use librt for monotonic clock (default = yes)
#  --with-udev-rules-dir   Directory where to install udev rules to (defaults
#                          to /lib/udev/rules.d)
#  --with-curses libname   Specify the curses library to use (default=auto)
#  --with-testsound=file        give the path of test sound file for alsaconf
#  --with-systemdsystemunitdir=DIR
#                          Directory for systemd service files
#  --with-asound-state-dir=DIR
#                          Directory to place asound.state file in
