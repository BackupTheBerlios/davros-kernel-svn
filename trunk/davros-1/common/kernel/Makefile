#	Makefile - for kernel
#
#	(c)1999 D.R.Haworth

include $(DAVROS_BASE)/target/make/rules.make

OBJECTS = 	\
	chprio.o	\
	close.o		\
	control.o	\
	create.o	\
	dcreate.o	\
	dequeue.o	\
	dequeued.o	\
	dfind.o		\
	enqueue.o	\
	exit.o		\
	freemem.o	\
	getc.o		\
	getioblk.o	\
	getmem.o	\
	getpid.o	\
	getstderr.o	\
	getstdin.o	\
	getstdout.o	\
	init.o		\
	initproc.o	\
	initqueue.o	\
	insert.o	\
	insertd.o	\
	ioerr.o		\
	ionull.o	\
	isleep.o	\
	kernel.o	\
	kill.o		\
	open.o		\
	psleep.o	\
	putc.o		\
	read.o		\
	ready.o		\
	receive.o	\
	recvclr.o	\
	reschedule.o\
	resume.o	\
	scount.o	\
	screate.o	\
	sdelete.o	\
	send.o		\
	setstdio.o	\
	signal.o	\
	sleep.o		\
	suspend.o	\
	test.o		\
	unsleep.o	\
	wait.o		\
	wakeup.o	\
	write.o

libdavros.a:	$(OBJECTS)
	-rm $@
	$(AR) $(ARFLAGS) $(AR_ADD) $@ $(OBJECTS)
	$(ARCH_CLEAN)

clean:
	-rm *.a *.o
	$(ARCH_CLEAN)
