#!/bin/sh

#export LDFLAGS=-L/alsa-1.0.21/lib/
#export CPPFLAGS=-I/alsa-1.0.21/include/

#echo ld=$LDFLAGS
#echo spp=$CPPFLAGS
#exit

./configure --prefix=/usr --disable-oss --disable-ssl 
#--with-external-pa 