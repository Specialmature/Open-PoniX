#!/bin/sh

export PATH="/source/Xdialog-2.3.1/bin:${PATH}"

./configure --prefix=/source/Xdialog-2.3.1 --enable-static --enable-shared=no --disable-docs --with-confdir=/etc/fonts \
CFLAGS="${CFLAGS} -I/source/Xdialog-2.3.1/include" \
LDFLAGS="${LDFLAGS} -L/source/Xdialog-2.3.1/lib" \
PKG_CONFIG_PATH=/source/Xdialog-2.3.1/lib/pkgconfig:${PKG_CONFIG_PATH}

