#	Makefile.m for davros/common/libc/string
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
				o/strlen.o		\
				o/strcpy.o		\
				o/strncpy.o		\
				o/strncmp.o		\
				o/strcasecmp.o	\
				o/memset.o

o/strlen.o:		libc/string/strlen.c
	$(CC) $(CFLAGS) -o o/strlen.o libc/string/strlen.c

o/strcpy.o:		libc/string/strcpy.c
	$(CC) $(CFLAGS) -o o/strcpy.o libc/string/strcpy.c

o/strncpy.o:	libc/string/strncpy.c
	$(CC) $(CFLAGS) -o o/strncpy.o libc/string/strncpy.c

o/strncmp.o:	libc/string/strncmp.c
	$(CC) $(CFLAGS) -o o/strncmp.o libc/string/strncmp.c

o/strcasecmp.o:	libc/string/strcasecmp.c
	$(CC) $(CFLAGS) -o o/strcasecmp.o libc/string/strcasecmp.c

o/memset.o:		libc/string/memset.c
	$(CC) $(CFLAGS) -o o/memset.o libc/string/memset.c
