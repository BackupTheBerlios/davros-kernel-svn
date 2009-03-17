#	Makefile.m for davros/common/kernel
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

DAVROS_OBJECTS = 	\
	o/chprio.o		\
	o/close.o		\
	o/control.o		\
	o/create.o		\
	o/dcreate.o		\
	o/dequeue.o		\
	o/dequeued.o	\
	o/dfind.o		\
	o/enqueue.o		\
	o/exit.o		\
	o/freemem.o		\
	o/getc.o		\
	o/getmem.o		\
	o/getpid.o		\
	o/getstderr.o	\
	o/getstdin.o	\
	o/getstdout.o	\
	o/init.o		\
	o/initproc.o	\
	o/initqueue.o	\
	o/insert.o		\
	o/insertd.o		\
	o/ioerr.o		\
	o/ionull.o		\
	o/isleep.o		\
	o/kernel.o		\
	o/kill.o		\
	o/open.o		\
	o/psleep.o		\
	o/putc.o		\
	o/read.o		\
	o/ready.o		\
	o/receive.o		\
	o/recvclr.o		\
	o/reschedule.o	\
	o/resume.o		\
	o/scount.o		\
	o/screate.o		\
	o/sdelete.o		\
	o/sreset.o		\
	o/send.o		\
	o/setstdio.o	\
	o/signal.o		\
	o/sleep.o		\
	o/suspend.o		\
	o/test.o		\
	o/tick.o		\
	o/unsleep.o		\
	o/wait.o		\
	o/wakeup.o		\
	o/write.o		\
	o/userinit.o	\
	o/usernull.o

o/chprio.o:		kernel/chprio.c
	$(CC) $(CFLAGS) -o o/chprio.o kernel/chprio.c

o/close.o:		kernel/close.c
	$(CC) $(CFLAGS) -o o/close.o kernel/close.c	

o/control.o:		kernel/control.c
	$(CC) $(CFLAGS) -o o/control.o kernel/control.c

o/create.o:		kernel/create.c
	$(CC) $(CFLAGS) -o o/create.o kernel/create.c

o/dcreate.o:		kernel/dcreate.c
	$(CC) $(CFLAGS) -o o/dcreate.o kernel/dcreate.c

o/dequeue.o:		kernel/dequeue.c
	$(CC) $(CFLAGS) -o o/dequeue.o kernel/dequeue.c

o/dequeued.o:		kernel/dequeued.c
	$(CC) $(CFLAGS) -o o/dequeued.o kernel/dequeued.c

o/dfind.o:		kernel/dfind.c
	$(CC) $(CFLAGS) -o o/dfind.o kernel/dfind.c	

o/enqueue.o:		kernel/enqueue.c
	$(CC) $(CFLAGS) -o o/enqueue.o kernel/enqueue.c

o/exit.o:		kernel/exit.c
	$(CC) $(CFLAGS) -o o/exit.o kernel/exit.c	

o/freemem.o:		kernel/freemem.c
	$(CC) $(CFLAGS) -o o/freemem.o kernel/freemem.c

o/getc.o:		kernel/getc.c
	$(CC) $(CFLAGS) -o o/getc.o kernel/getc.c	

o/getmem.o:		kernel/getmem.c
	$(CC) $(CFLAGS) -o o/getmem.o kernel/getmem.c

o/getpid.o:		kernel/getpid.c
	$(CC) $(CFLAGS) -o o/getpid.o kernel/getpid.c

o/getstderr.o:		kernel/getstderr.c
	$(CC) $(CFLAGS) -o o/getstderr.o kernel/getstderr.c

o/getstdin.o:		kernel/getstdin.c
	$(CC) $(CFLAGS) -o o/getstdin.o kernel/getstdin.c

o/getstdout.o:		kernel/getstdout.c
	$(CC) $(CFLAGS) -o o/getstdout.o kernel/getstdout.c

o/init.o:		kernel/init.c
	$(CC) $(CFLAGS) -o o/init.o kernel/init.c	

o/initproc.o:		kernel/initproc.c
	$(CC) $(CFLAGS) -o o/initproc.o kernel/initproc.c

o/initqueue.o:		kernel/initqueue.c
	$(CC) $(CFLAGS) -o o/initqueue.o kernel/initqueue.c

o/insert.o:		kernel/insert.c
	$(CC) $(CFLAGS) -o o/insert.o kernel/insert.c

o/insertd.o:		kernel/insertd.c
	$(CC) $(CFLAGS) -o o/insertd.o kernel/insertd.c

o/ioerr.o:		kernel/ioerr.c
	$(CC) $(CFLAGS) -o o/ioerr.o kernel/ioerr.c	

o/ionull.o:		kernel/ionull.c
	$(CC) $(CFLAGS) -o o/ionull.o kernel/ionull.c

o/isleep.o:		kernel/isleep.c
	$(CC) $(CFLAGS) -o o/isleep.o kernel/isleep.c

o/kernel.o:		kernel/kernel.c
	$(CC) $(CFLAGS) -o o/kernel.o kernel/kernel.c

o/kill.o:		kernel/kill.c
	$(CC) $(CFLAGS) -o o/kill.o kernel/kill.c	

o/open.o:		kernel/open.c
	$(CC) $(CFLAGS) -o o/open.o kernel/open.c	

o/psleep.o:		kernel/psleep.c
	$(CC) $(CFLAGS) -o o/psleep.o kernel/psleep.c

o/putc.o:		kernel/putc.c
	$(CC) $(CFLAGS) -o o/putc.o kernel/putc.c	

o/read.o:		kernel/read.c
	$(CC) $(CFLAGS) -o o/read.o kernel/read.c	

o/ready.o:		kernel/ready.c
	$(CC) $(CFLAGS) -o o/ready.o kernel/ready.c	

o/receive.o:		kernel/receive.c
	$(CC) $(CFLAGS) -o o/receive.o kernel/receive.c

o/recvclr.o:		kernel/recvclr.c
	$(CC) $(CFLAGS) -o o/recvclr.o kernel/recvclr.c

o/reschedule.o:		kernel/reschedule.c
	$(CC) $(CFLAGS) -o o/reschedule.o kernel/reschedule.c

o/resume.o:		kernel/resume.c
	$(CC) $(CFLAGS) -o o/resume.o kernel/resume.c

o/scount.o:		kernel/scount.c
	$(CC) $(CFLAGS) -o o/scount.o kernel/scount.c

o/screate.o:		kernel/screate.c
	$(CC) $(CFLAGS) -o o/screate.o kernel/screate.c

o/sdelete.o:		kernel/sdelete.c
	$(CC) $(CFLAGS) -o o/sdelete.o kernel/sdelete.c

o/sreset.o:			kernel/sreset.c
	$(CC) $(CFLAGS) -o o/sreset.o kernel/sreset.c

o/send.o:		kernel/send.c
	$(CC) $(CFLAGS) -o o/send.o kernel/send.c	

o/setstdio.o:		kernel/setstdio.c
	$(CC) $(CFLAGS) -o o/setstdio.o kernel/setstdio.c

o/signal.o:		kernel/signal.c
	$(CC) $(CFLAGS) -o o/signal.o kernel/signal.c

o/sleep.o:		kernel/sleep.c
	$(CC) $(CFLAGS) -o o/sleep.o kernel/sleep.c	

o/suspend.o:		kernel/suspend.c
	$(CC) $(CFLAGS) -o o/suspend.o kernel/suspend.c

o/test.o:		kernel/test.c
	$(CC) $(CFLAGS) -o o/test.o kernel/test.c	

o/tick.o:		kernel/tick.c
	$(CC) $(CFLAGS) -o o/tick.o kernel/tick.c	

o/unsleep.o:		kernel/unsleep.c
	$(CC) $(CFLAGS) -o o/unsleep.o kernel/unsleep.c

o/wait.o:		kernel/wait.c
	$(CC) $(CFLAGS) -o o/wait.o kernel/wait.c	

o/wakeup.o:		kernel/wakeup.c
	$(CC) $(CFLAGS) -o o/wakeup.o kernel/wakeup.c

o/write.o:		kernel/write.c
	$(CC) $(CFLAGS) -o o/write.o kernel/write.c

o/userinit.o:	kernel/userinit.c
	$(CC) $(CFLAGS) -o o/userinit.o kernel/userinit.c

o/usernull.o:	kernel/usernull.c
	$(CC) $(CFLAGS) -o o/usernull.o kernel/usernull.c
