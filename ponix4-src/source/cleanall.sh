#!/bin/sh

ls -1 | while read dir
do

echo "DIR $dir"
cd $dir && make clean
cd /build/source/

done



