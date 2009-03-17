#!/bin/sh
# Usage:
#	cd to architecture subdirectory, then type
#	../common/script/make-arch-dirs.sh

mkdir o
mkdir lib
mkdir bin

ln -s ../common/doc doc
ln -s ../common/drv drv
ln -s ../common/forth forth
ln -s ../common/h h
ln -s ../common/kernel kernel
ln -s ../common/kernel-utils kernel-utils
ln -s ../common/libc libc
ln -s ../common/monitor monitor
ln -s ../common/test test
