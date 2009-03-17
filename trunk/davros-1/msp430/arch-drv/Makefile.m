#	Makefile.m for davros/msp430/arch-drv
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
#	This file should be included into the master Makefile.
#
#	$Id$
#
#	$Log: Makefile.m,v $
#	Revision 1.1  2004/05/11 20:39:27  dave
#	Files for the MSP430 port.
#	

ARCH_DRV_OBJECTS =	o/timer-a-drv.o	\
					o/unused-vectors.o

o/timer-a-drv.o:		arch-drv/timer-a-drv.c
	$(CC) $(CFLAGS) -o o/timer-a-drv.o arch-drv/timer-a-drv.c

o/unused-vectors.o:		arch-drv/unused-vectors.c
	$(CC) $(CFLAGS) -o o/unused-vectors.o arch-drv/unused-vectors.c
