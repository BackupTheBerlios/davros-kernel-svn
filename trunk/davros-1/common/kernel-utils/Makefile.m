#	Makefile.m for davros/common/kernel-utils
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

KUTIL_OBJECTS =		\
	o/getmeminfo.o	\
	o/lsmem.o		\
	o/lsdev.o		\
	o/lsproc.o

o/getmeminfo.o:		kernel-utils/getmeminfo.c
	$(CC) $(CFLAGS) -o o/getmeminfo.o kernel-utils/getmeminfo.c

o/lsmem.o:			kernel-utils/lsmem.c
	$(CC) $(CFLAGS) -o o/lsmem.o kernel-utils/lsmem.c

o/lsdev.o:			kernel-utils/lsdev.c
	$(CC) $(CFLAGS) -o o/lsdev.o kernel-utils/lsdev.c

o/lsproc.o:			kernel-utils/lsproc.c
	$(CC) $(CFLAGS) -o o/lsproc.o kernel-utils/lsproc.c
