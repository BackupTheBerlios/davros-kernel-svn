#	Makefile.m for davros/common/test
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

o/kerntest.o:		test/kerntest.c
	$(CC) $(CFLAGS) -o o/kerntest.o test/kerntest.c

o/proctest.o:		test/proctest.c
	$(CC) $(CFLAGS) -o o/proctest.o test/proctest.c

o/semtest.o:		test/semtest.c
	$(CC) $(CFLAGS) -o o/semtest.o test/semtest.c

o/msgtest.o:		test/msgtest.c
	$(CC) $(CFLAGS) -o o/msgtest.o test/msgtest.c

# Below here is the trial code for bringing up a new architecture port
o/devtest1.o:		test/bootstrap/devtest1.c
	$(CC) $(CFLAGS) -o o/devtest1.o test/bootstrap/devtest1.c

o/devtest2.o:		test/bootstrap/devtest2.c
	$(CC) $(CFLAGS) -o o/devtest2.o test/bootstrap/devtest2.c

o/devtest3.o:		test/bootstrap/devtest3.c
	$(CC) $(CFLAGS) -o o/devtest3.o test/bootstrap/devtest3.c

#o/semtest.o:		test/semtest.c
#	$(CC) $(CFLAGS) -o o/semtest.o test/semtest.c
#
#o/msgtest.o:		test/msgtest.c
#	$(CC) $(CFLAGS) -o o/msgtest.o test/msgtest.c
#
#o/excptest.o:		test/excptest.c
#	$(CC) $(CFLAGS) -o o/excptest.o test/excptest.c
#
#o/ttytest.o:		test/ttytest.c
#	$(CC) $(CFLAGS) -o o/ttytest.o test/ttytest.c
