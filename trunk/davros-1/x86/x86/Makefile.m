#	Makefile.m for davros/x86/x86
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

X86_OBJECTS =			\
	o/x86-core-asm.o	\
	o/x86-kernel-asm.o	\
	o/x86-kernel.o		\
	o/x86-interrupts.o	\
	o/vectors.o

o/x86-core-asm.o:	x86/x86-core-asm.s
	$(AS) $(ASFLAGS) -o o/x86-core-asm.o x86/x86-core-asm.s

#o/x86-core.o:		x86/x86-core.c
#	$(CC) $(CFLAGS) -o o/x86-core.o x86/x86-core.c

o/x86-kernel-asm.o:	x86/x86-kernel-asm.s
	$(AS) $(ASFLAGS) -o o/x86-kernel-asm.o x86/x86-kernel-asm.s

o/x86-kernel.o:		x86/x86-kernel.c
	$(CC) $(CFLAGS) -o o/x86-kernel.o x86/x86-kernel.c

o/x86-interrupts.o:	x86/x86-interrupts.c
	$(CC) $(CFLAGS) -o o/x86-interrupts.o x86/x86-interrupts.c

o/vectors.o:		x86/vectors.s
	$(AS) $(ASFLAGS) -o o/vectors.o x86/vectors.s
