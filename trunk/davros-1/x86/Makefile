#	Makefile for davros/x86
#
#	Copyright 2001 David Haworth
#
#	This file is free software; you can redistribute it and/or modify
#	it under the terms of the GNU General Public License as published by
#	the Free Software Foundation; either version 2, or (at your option)
#	any later version.
#
#	It is distributed in the hope that it will be useful,
#	but WITHOUT ANY WARRANTY; without even the implied warranty of
#	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#	GNU General Public License for more details.
#
#	You should have received a copy of the GNU General Public License
#	along with this program; see the file COPYING.  If not, write to
#	the Free Software Foundation, 59 Temple Place - Suite 330,
#	Boston, MA 02111-1307, USA.
#
#
#	This file is the master makefile for the x86 directory.

CPU_CONFIG =
#OTHER_CONFIG = -D__DAVROS_DEBUGGING

_CONFIG = $(CPU_CONFIG) $(OTHER_CONFIG)

AS = gcc
CC = gcc
LD =  ld
HPATH = -Iarch-h -Ih
CFLAGS = -g -c -Wall -fno-builtin $(_CONFIG) $(HPATH)
ASFLAGS = -g -c -xassembler-with-cpp $(_CONFIG) $(HPATH)
LDFLAGS = -g -X -N

default:	bin/davros

all:	bin/davros bin/kerntest

include boot/Makefile.m
include x86/Makefile.m
include monitor/Makefile.m
include forth/Makefile.m
include libc/ctype/Makefile.m
include libc/stdio/Makefile.m
include libc/string/Makefile.m
include libc/stdlib/Makefile.m
include kernel/Makefile.m
include kernel-utils/Makefile.m
include drv/Makefile.m
include test/Makefile.m

bin/test:		\
                o/entry.o o/boot-kernel.o o/devtest3.o \
				lib/libkutil.a lib/libdavros.a lib/libx86.a \
				lib/libdrv.a lib/libc.a
	$(LD) $(LDFLAGS) -T script/x86.ldscript \
                -e entry -o bin/test \
                o/entry.o o/boot-kernel.o o/devtest3.o o/x86-kernel.o \
				lib/libkutil.a lib/libdavros.a lib/libx86.a \
				lib/libdrv.a lib/libdavros.a lib/libc.a

bin/kerntest:	\
                o/entry.o o/boot-kernel.o o/kerntest.o \
				o/proctest.o o/semtest.o o/msgtest.o \
				lib/libkutil.a lib/libdavros.a lib/libx86.a \
				lib/libdrv.a lib/libc.a
	$(LD) $(LDFLAGS) -T script/x86.ldscript \
                -e entry -o bin/kerntest \
                o/entry.o o/boot-kernel.o o/kerntest.o o/x86-kernel.o \
				o/proctest.o o/semtest.o o/msgtest.o \
				lib/libkutil.a lib/libdavros.a lib/libx86.a \
				lib/libdrv.a lib/libdavros.a lib/libc.a

bin/davros:		\
                o/entry.o o/boot-kernel.o o/start-qdf.o \
				o/x86-kernel.o o/forth.o o/stddict.o \
				lib/libdavros.a lib/libx86.a lib/libdrv.a lib/libc.a
	$(LD) $(LDFLAGS) -T script/x86.ldscript \
                -e entry -o bin/davros \
                o/entry.o o/boot-kernel.o o/start-qdf.o \
				o/x86-kernel.o o/forth.o o/stddict.o \
				lib/libdavros.a lib/libx86.a lib/libdrv.a \
				lib/libdavros.a lib/libc.a

lib/libc.a:			$(LIBC_OBJECTS)
	-rm -f lib/libc.a
	ar crus lib/libc.a $(LIBC_OBJECTS)

lib/libdrv.a:	$(DRV_OBJECTS) $(ARCH_DRV_OBJECTS)
	-rm -f lib/libdrv.a
	ar crus lib/libdrv.a $(DRV_OBJECTS) $(ARCH_DRV_OBJECTS)

lib/libx86.a:	$(X86_OBJECTS)
	-rm -f lib/libx86.a
	ar crus lib/libx86.a $(X86_OBJECTS)

lib/libdavros.a:	$(DAVROS_OBJECTS)
	-rm -f lib/libdavros.a
	ar crus lib/libdavros.a $(DAVROS_OBJECTS)

lib/libkutil.a:		$(KUTIL_OBJECTS)
	-rm -f lib/libkutil.a
	ar crus lib/libkutil.a $(KUTIL_OBJECTS)

				

clean:
	-rm o/* lib/* bin/*
