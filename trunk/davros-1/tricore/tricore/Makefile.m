#	Makefile.m for davros/tricore/boot
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

TRICORE_OBJECTS =			\
	o/tricore-core-asm.o	\
	o/tricore-core.o		\
	o/tricore-kernel-asm.o	\
	o/tricore-kernel.o		\
	o/tricore-interrupts.o	\
	o/vectors.o

o/tricore-core-asm.o:	tricore/tricore-core-asm.s
	$(AS) $(ASFLAGS) -o o/tricore-core-asm.o tricore/tricore-core-asm.s

o/tricore-core.o:	tricore/tricore-core.c
	$(CC) $(CFLAGS) -o o/tricore-core.o tricore/tricore-core.c

o/tricore-kernel-asm.o:	tricore/tricore-kernel-asm.s
	$(AS) $(ASFLAGS) -o o/tricore-kernel-asm.o tricore/tricore-kernel-asm.s

o/tricore-kernel.o:	tricore/tricore-kernel.c
	$(CC) $(CFLAGS) -o o/tricore-kernel.o tricore/tricore-kernel.c

o/tricore-interrupts.o:	tricore/tricore-interrupts.c
	$(CC) $(CFLAGS) -o o/tricore-interrupts.o tricore/tricore-interrupts.c

o/vectors.o:	tricore/vectors.s
	$(AS) $(ASFLAGS) -o o/vectors.o tricore/vectors.s
