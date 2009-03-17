#	Makefile for davros/msp430
#
#	Copyright 2004 David Haworth
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
#	This file is the master makefile for the msp430 directory.
#
#	$Id$
#	$Log: Makefile,v $
#	Revision 1.2  2004/05/11 20:34:49  dave
#	Add CVS Id and Log tags.
#	

CPU_CONFIG = -DMSP_CPU=MSP430X149
#OTHER_CONFIG = -D__DAVROS_DEBUGGING

_CONFIG = $(CPU_CONFIG) $(OTHER_CONFIG)

AS = msp430-gcc
CC = msp430-gcc
LD =  msp430-gcc
HPATH = -Iarch-h -Ih
CFLAGS = -g -c -fno-builtin -Wall -mmcu=msp430x149 $(_CONFIG) $(HPATH)
ASFLAGS = -g -c -xassembler-with-cpp -mmcu=msp430x149 $(_CONFIG) $(HPATH)
LDFLAGS = -g -mmcu=msp430x149 -L/gnu/msp430/lib/gcc-lib/msp430/3.3.3

default:	bin/async

all:	bin/davros bin/synchro bin/async

include boot/Makefile.m
include msp430/Makefile.m
#include monitor/Makefile.m
#include forth/Makefile.m
include libc/ctype/Makefile.m
include libc/stdio/Makefile.m
include libc/string/Makefile.m
include libc/stdlib/Makefile.m
include kernel/Makefile.m
include kernel-utils/Makefile.m
include drv/Makefile.m
include arch-drv/Makefile.m
include test/Makefile.m

bin/kerntest:	\
				o/boot-kernel.o o/kerntest.o \
				o/proctest.o o/semtest.o o/msgtest.o \
				lib/libkutil.a lib/libdavros.a lib/libmsp430.a \
				lib/libdrv.a lib/libc.a
	$(LD) $(LDFLAGS) \
				-o bin/kerntest \
				o/boot-kernel.o o/kerntest.o \
				o/proctest.o o/semtest.o o/msgtest.o \
				lib/libkutil.a lib/libdavros.a lib/libmsp430.a \
				lib/libdrv.a lib/libdavros.a lib/libc.a

# Bare kernel
bin/davros:		o/boot-kernel.o \
				lib/libdavros.a lib/libmsp430.a lib/libdrv.a lib/libc.a
	$(LD) $(LDFLAGS) \
                -o bin/davros \
				o/boot-kernel.o \
				lib/libdavros.a lib/libmsp430.a lib/libdrv.a \
				lib/libdavros.a lib/libc.a -lgcc

# Check out the synchronous kernel
bin/synchro:	o/boot-kernel.o \
				o/synchro.o \
				o/unused-vectors.o \
				lib/libdavros.a lib/libmsp430.a lib/libdrv.a lib/libc.a
	$(LD) $(LDFLAGS) \
                -o bin/synchro \
				o/boot-kernel.o \
				o/synchro.o \
				o/unused-vectors.o \
				lib/libdavros.a lib/libmsp430.a lib/libdrv.a \
				lib/libdavros.a lib/libc.a -lgcc

# Check out the asynchronous kernel
bin/async:		o/boot-kernel.o \
				o/async.o \
				o/unused-vectors.o \
				lib/libdavros.a lib/libmsp430.a lib/libdrv.a lib/libc.a
	$(LD) $(LDFLAGS) \
                -o bin/async \
				o/boot-kernel.o \
				o/async.o \
				o/unused-vectors.o \
				lib/libdavros.a lib/libmsp430.a lib/libdrv.a \
				lib/libdavros.a lib/libc.a -lgcc


lib/libc.a:			$(LIBC_OBJECTS)
	-rm -f lib/libc.a
	ar crus lib/libc.a $(LIBC_OBJECTS)

lib/libdrv.a:	$(DRV_OBJECTS) $(ARCH_DRV_OBJECTS)
	-rm -f lib/libdrv.a
	ar crus lib/libdrv.a $(DRV_OBJECTS) $(ARCH_DRV_OBJECTS)

lib/libmsp430.a:	$(MSP430_OBJECTS)
	-rm -f lib/libmsp430.a
	ar crus lib/libmsp430.a $(MSP430_OBJECTS)

lib/libdavros.a:	$(DAVROS_OBJECTS)
	-rm -f lib/libdavros.a
	ar crus lib/libdavros.a $(DAVROS_OBJECTS)

lib/libkutil.a:		$(KUTIL_OBJECTS)
	-rm -f lib/libkutil.a
	ar crus lib/libkutil.a $(KUTIL_OBJECTS)

				

clean:
	-rm o/* lib/* bin/*
