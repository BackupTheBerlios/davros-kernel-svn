#	Makefile for davros/tricore
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
#	This file is the master makefile for the tricore directory.

CPU_CONFIG = -DTRICORE_BOARD=TRIBOARD -DTRICORE_CPU=TC10GP
#OTHER_CONFIG = -D__DAVROS_DEBUGGING

_CONFIG = $(CPU_CONFIG) $(OTHER_CONFIG)

AS = tricore-gcc
CC = tricore-gcc
LD =  tricore-ld
HPATH = -Iarch-h -Ih
CFLAGS = -g -c -mrider-b -Wall -fno-builtin $(_CONFIG) $(HPATH)
ASFLAGS = -g -c -mrider-b -xassembler-with-cpp $(_CONFIG) $(HPATH)
LDFLAGS = -g -X -N

default:	bin/davros

all:	bin/monitor bin/qdf bin/davros

include boot/Makefile.m
include tricore/Makefile.m
include monitor/Makefile.m
include forth/Makefile.m
include libc/ctype/Makefile.m
include libc/stdio/Makefile.m
include libc/string/Makefile.m
include libc/stdlib/Makefile.m
include kernel/Makefile.m
include kernel-utils/Makefile.m
include drv/Makefile.m
include arch-drv/Makefile.m
include test/Makefile.m

bin/monitor:	\
				o/rom-entry.o o/tricore-core-asm.o o/boot-monitor.o \
				o/monitor.o o/mon-stdio.o o/mon-srec.o o/mon-util.o \
				o/mod-drv.o o/asc-drv.o o/asc-drv-polled.o \
				o/pwr-drv.o o/gpio-drv.o \
				o/xprintf.o \
				o/isspace.o o/isdigit.o o/strlen.o o/isxdigit.o
	$(LD) $(LDFLAGS) -T script/tricore.ldscript.ram \
				-e rom_entry -o bin/monitor \
				o/rom-entry.o o/tricore-core-asm.o o/boot-monitor.o \
				o/monitor.o o/mon-stdio.o o/mon-srec.o o/mon-util.o \
				o/mod-drv.o o/asc-drv.o o/asc-drv-polled.o \
				o/pwr-drv.o o/gpio-drv.o \
				o/xprintf.o \
				o/isspace.o o/isdigit.o o/strlen.o o/isxdigit.o

bin/qdf:		\
				o/rom-entry.o o/tricore-core-asm.o o/boot-qdf.o \
				o/forth.o o/stddict.o \
				o/stdio.o o/fprintf.o \
				o/mod-drv.o o/asc-drv.o o/asc-drv-polled.o \
				o/pwr-drv.o o/gpio-drv.o \
				o/xprintf.o \
				o/isspace.o o/isdigit.o o/isxdigit.o o/isprint.o \
				o/strlen.o o/strcpy.o o/strcasecmp.o \
				o/strtoul.o
	$(LD) $(LDFLAGS) -T script/tricore.ldscript.ram \
				-e rom_entry -o bin/qdf \
				o/rom-entry.o o/tricore-core-asm.o o/boot-qdf.o \
				o/forth.o o/stddict.o \
				o/stdio.o o/fprintf.o \
				o/mod-drv.o o/asc-drv.o o/asc-drv-polled.o \
				o/pwr-drv.o o/gpio-drv.o \
				o/xprintf.o \
				o/isspace.o o/isdigit.o o/isxdigit.o o/isprint.o \
				o/strlen.o o/strcpy.o o/strcasecmp.o \
				o/strtoul.o

bin/kerntest:		\
                o/rom-entry.o o/boot-kernel.o o/kerntest.o \
				o/proctest.o o/semtest.o o/msgtest.o \
				lib/libkutil.a lib/libdavros.a lib/libtricore.a \
				lib/libdrv.a lib/libc.a
	$(LD) $(LDFLAGS) -T script/tricore.ldscript.ram \
                -e rom_entry -o bin/kerntest \
                o/rom-entry.o o/boot-kernel.o o/kerntest.o o/tricore-kernel.o \
				o/proctest.o o/semtest.o o/msgtest.o \
				lib/libkutil.a lib/libdavros.a lib/libtricore.a \
				lib/libdrv.a lib/libdavros.a lib/libc.a

bin/davros:		\
                o/rom-entry.o o/boot-kernel.o o/start-qdf.o \
				o/tricore-kernel.o o/forth.o o/stddict.o \
				lib/libdavros.a lib/libtricore.a lib/libdrv.a lib/libc.a
	$(LD) $(LDFLAGS) -T script/tricore.ldscript.ram \
                -e rom_entry -o bin/davros \
                o/rom-entry.o o/boot-kernel.o o/start-qdf.o \
				o/tricore-kernel.o o/forth.o o/stddict.o \
				lib/libdavros.a lib/libtricore.a lib/libdrv.a \
				lib/libdavros.a lib/libc.a

lib/libc.a:			$(LIBC_OBJECTS)
	-rm -f lib/libc.a
	ar crus lib/libc.a $(LIBC_OBJECTS)

lib/libdrv.a:	$(DRV_OBJECTS) $(ARCH_DRV_OBJECTS)
	-rm -f lib/libdrv.a
	ar crus lib/libdrv.a $(DRV_OBJECTS) $(ARCH_DRV_OBJECTS)

lib/libtricore.a:	$(TRICORE_OBJECTS)
	-rm -f lib/libtricore.a
	ar crus lib/libtricore.a $(TRICORE_OBJECTS)

lib/libdavros.a:	$(DAVROS_OBJECTS)
	-rm -f lib/libdavros.a
	ar crus lib/libdavros.a $(DAVROS_OBJECTS)

lib/libkutil.a:		$(KUTIL_OBJECTS)
	-rm -f lib/libkutil.a
	ar crus lib/libkutil.a $(KUTIL_OBJECTS)

				

clean:
	-rm o/* lib/* bin/*
