#!/bin/sh
if [ "$1" = "" ] ; then
	echo "Usage: $0 program-name"
else
	if [ -x $1 ] ; then
		dir=`dirname $0`
		/home/dave/qemu/svn/arm-softmmu/qemu-system-arm -S -s -kernel $1 -hda /dev/zero -serial pty &
		sleep 2
		/gnu/insight-6.8-arm/bin/arm-elf-insight $1
#		/gnu/insight-6.8-arm/bin/arm-elf-insight -x ${dir}/gdb-init $1 &
	else
		echo "Usage: $0 program-name"
	fi
fi
