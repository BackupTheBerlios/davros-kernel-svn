#	Makefile.m for davros/tricore/arch-drv
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
#	This file should be included into the master Makefile.

ARCH_DRV_OBJECTS =	o/mod-drv.o			\
					o/pwr-drv.o			\
					o/asc-drv.o			\
					o/asc-drv-polled.o	\
					o/gpio-drv.o		\
					o/gptu-drv.o		\
					o/asc-tty-drv.o

o/mod-drv.o:		arch-drv/mod-drv.c
	$(CC) $(CFLAGS) -o o/mod-drv.o arch-drv/mod-drv.c

o/pwr-drv.o:		arch-drv/pwr-drv.c
	$(CC) $(CFLAGS) -o o/pwr-drv.o arch-drv/pwr-drv.c

o/asc-drv.o:		arch-drv/asc-drv.c
	$(CC) $(CFLAGS) -o o/asc-drv.o arch-drv/asc-drv.c

o/asc-drv-polled.o:	arch-drv/asc-drv-polled.c
	$(CC) $(CFLAGS) -o o/asc-drv-polled.o arch-drv/asc-drv-polled.c

o/gpio-drv.o:		arch-drv/gpio-drv.c
	$(CC) $(CFLAGS) -o o/gpio-drv.o arch-drv/gpio-drv.c

o/gptu-drv.o:		arch-drv/gptu-drv.c
	$(CC) $(CFLAGS) -o o/gptu-drv.o arch-drv/gptu-drv.c

o/asc-tty-drv.o:	arch-drv/asc-tty-drv.c
	$(CC) $(CFLAGS) -o o/asc-tty-drv.o arch-drv/asc-tty-drv.c
