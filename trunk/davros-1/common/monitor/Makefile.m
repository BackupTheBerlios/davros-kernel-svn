#	Makefile.m for davros/common/monitor
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

o/monitor.o:		monitor/monitor.c
	$(CC) $(CFLAGS) -o o/monitor.o monitor/monitor.c

o/mon-stdio.o:		monitor/mon-stdio.c
	$(CC) $(CFLAGS) -o o/mon-stdio.o monitor/mon-stdio.c

o/mon-srec.o:		monitor/mon-srec.c
	$(CC) $(CFLAGS) -o o/mon-srec.o monitor/mon-srec.c

o/mon-util.o:		monitor/mon-util.c
	$(CC) $(CFLAGS) -o o/mon-util.o monitor/mon-util.c
