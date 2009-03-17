#	Makefile.m for davros/x86/boot
#
#	Copyright 2002 David Haworth
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

o/entry.o:			boot/entry.s
	$(AS) $(ASFLAGS) -o o/entry.o boot/entry.s
	
o/boot-kernel.o:	boot/boot-kernel.c
	$(CC) $(CFLAGS) -o o/boot-kernel.o boot/boot-kernel.c
	
o/start-qdf.o:		boot/start-qdf.c
	$(CC) $(CFLAGS) -o o/start-qdf.o boot/start-qdf.c
