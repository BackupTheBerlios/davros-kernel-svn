#	Makefile.m for davros/common/libc/stdio
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

LIBC_OBJECTS := $(LIBC_OBJECTS) \
				o/xprintf.o		\
				o/fprintf.o		\
				o/dbg.o			\
				o/kprintf.o

o/xprintf.o:		libc/stdio/xprintf.c
	$(CC) $(CFLAGS) -o o/xprintf.o libc/stdio/xprintf.c

o/kprintf.o:		libc/stdio/kprintf.c
	$(CC) $(CFLAGS) -o o/kprintf.o libc/stdio/kprintf.c

o/fprintf.o:		libc/stdio/fprintf.c
	$(CC) $(CFLAGS) -o o/fprintf.o libc/stdio/fprintf.c

#o/stdio.o:			libc/stdio/stdio.c
#	$(CC) $(CFLAGS) -o o/stdio.o libc/stdio/stdio.c

o/dbg.o:			libc/stdio/dbg.c
	$(CC) $(CFLAGS) -o o/dbg.o libc/stdio/dbg.c
