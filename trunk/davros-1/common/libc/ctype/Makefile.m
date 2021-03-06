#	Makefile.m for davros/common/libc/ctype
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

LIBC_OBJECTS :=	$(LIBC_OBJECTS) \
				o/isdigit.o		\
				o/isxdigit.o	\
				o/isspace.o		\
				o/isprint.o

o/isdigit.o:		libc/ctype/isdigit.c
	$(CC) $(CFLAGS) -o o/isdigit.o libc/ctype/isdigit.c

o/isxdigit.o:		libc/ctype/isxdigit.c
	$(CC) $(CFLAGS) -o o/isxdigit.o libc/ctype/isxdigit.c

o/isspace.o:		libc/ctype/isspace.c
	$(CC) $(CFLAGS) -o o/isspace.o libc/ctype/isspace.c

o/isprint.o:		libc/ctype/isprint.c
	$(CC) $(CFLAGS) -o o/isprint.o libc/ctype/isprint.c
