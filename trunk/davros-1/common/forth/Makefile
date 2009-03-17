#	Makefile for qdf
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

#STKTYP=FULLMEM
#STKTYP=FIXSTK
STKTYP=MEMMGR
CFLAGS=-g -Wall -D$(STKTYP) -I../h

qdf:	qdf.o forth.o stack.o stddict.o dbg.o

clean:
	rm *.o qdf


# DO NOT DELETE


dbg.o: /usr/include/_G_config.h /usr/include/bits/pthreadtypes.h
dbg.o: /usr/include/bits/sched.h /usr/include/bits/stdio_lim.h
dbg.o: /usr/include/bits/types.h /usr/include/bits/wchar.h
dbg.o: /usr/include/features.h /usr/include/gconv.h /usr/include/gnu/stubs.h
dbg.o: /usr/include/libio.h /usr/include/stdio.h /usr/include/sys/cdefs.h
dbg.o: /usr/include/wchar.h
dbg.o: /usr/lib/gcc-lib/i486-suse-linux/2.95.2/include/stdarg.h
dbg.o: /usr/lib/gcc-lib/i486-suse-linux/2.95.2/include/stddef.h dbg.h
forth.o: /usr/include/_G_config.h /usr/include/alloca.h
forth.o: /usr/include/bits/confname.h /usr/include/bits/endian.h
forth.o: /usr/include/bits/environments.h /usr/include/bits/posix_opt.h
forth.o: /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h
forth.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
forth.o: /usr/include/bits/stdio_lim.h /usr/include/bits/types.h
forth.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
forth.o: /usr/include/bits/wchar.h /usr/include/bits/wordsize.h
forth.o: /usr/include/ctype.h /usr/include/endian.h /usr/include/features.h
forth.o: /usr/include/gconv.h /usr/include/getopt.h /usr/include/gnu/stubs.h
forth.o: /usr/include/libio.h /usr/include/stdio.h /usr/include/stdlib.h
forth.o: /usr/include/string.h /usr/include/sys/cdefs.h
forth.o: /usr/include/sys/select.h /usr/include/sys/sysmacros.h
forth.o: /usr/include/sys/types.h /usr/include/time.h /usr/include/unistd.h
forth.o: /usr/include/wchar.h /usr/include/xlocale.h
forth.o: /usr/lib/gcc-lib/i486-suse-linux/2.95.2/include/stdarg.h
forth.o: /usr/lib/gcc-lib/i486-suse-linux/2.95.2/include/stddef.h dbg.h
forth.o: forth.h qdftypes.h stack.h
qdf.o: /usr/include/_G_config.h /usr/include/bits/confname.h
qdf.o: /usr/include/bits/endian.h /usr/include/bits/environments.h
qdf.o: /usr/include/bits/posix_opt.h /usr/include/bits/pthreadtypes.h
qdf.o: /usr/include/bits/sched.h /usr/include/bits/select.h
qdf.o: /usr/include/bits/sigset.h /usr/include/bits/stdio_lim.h
qdf.o: /usr/include/bits/types.h /usr/include/bits/wchar.h
qdf.o: /usr/include/bits/wordsize.h /usr/include/endian.h
qdf.o: /usr/include/features.h /usr/include/gconv.h /usr/include/getopt.h
qdf.o: /usr/include/gnu/stubs.h /usr/include/libio.h /usr/include/stdio.h
qdf.o: /usr/include/sys/cdefs.h /usr/include/sys/select.h
qdf.o: /usr/include/sys/sysmacros.h /usr/include/sys/types.h
qdf.o: /usr/include/time.h /usr/include/unistd.h /usr/include/wchar.h
qdf.o: /usr/lib/gcc-lib/i486-suse-linux/2.95.2/include/stdarg.h
qdf.o: /usr/lib/gcc-lib/i486-suse-linux/2.95.2/include/stddef.h forth.h
qdf.o: qdftypes.h stack.h
stack.o: /usr/include/alloca.h /usr/include/bits/confname.h
stack.o: /usr/include/bits/endian.h /usr/include/bits/environments.h
stack.o: /usr/include/bits/posix_opt.h /usr/include/bits/pthreadtypes.h
stack.o: /usr/include/bits/sched.h /usr/include/bits/select.h
stack.o: /usr/include/bits/sigset.h /usr/include/bits/types.h
stack.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
stack.o: /usr/include/bits/wordsize.h /usr/include/endian.h
stack.o: /usr/include/features.h /usr/include/getopt.h
stack.o: /usr/include/gnu/stubs.h /usr/include/stdlib.h
stack.o: /usr/include/sys/cdefs.h /usr/include/sys/select.h
stack.o: /usr/include/sys/sysmacros.h /usr/include/sys/types.h
stack.o: /usr/include/time.h /usr/include/unistd.h /usr/include/xlocale.h
stack.o: /usr/lib/gcc-lib/i486-suse-linux/2.95.2/include/stddef.h qdftypes.h
stack.o: stack.h
stddict.o: /usr/include/_G_config.h /usr/include/alloca.h
stddict.o: /usr/include/bits/confname.h /usr/include/bits/endian.h
stddict.o: /usr/include/bits/environments.h /usr/include/bits/posix_opt.h
stddict.o: /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h
stddict.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
stddict.o: /usr/include/bits/stdio_lim.h /usr/include/bits/types.h
stddict.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
stddict.o: /usr/include/bits/wchar.h /usr/include/bits/wordsize.h
stddict.o: /usr/include/endian.h /usr/include/features.h /usr/include/gconv.h
stddict.o: /usr/include/getopt.h /usr/include/gnu/stubs.h /usr/include/libio.h
stddict.o: /usr/include/stdio.h /usr/include/stdlib.h /usr/include/string.h
stddict.o: /usr/include/sys/cdefs.h /usr/include/sys/select.h
stddict.o: /usr/include/sys/sysmacros.h /usr/include/sys/types.h
stddict.o: /usr/include/time.h /usr/include/unistd.h /usr/include/wchar.h
stddict.o: /usr/include/xlocale.h
stddict.o: /usr/lib/gcc-lib/i486-suse-linux/2.95.2/include/stdarg.h
stddict.o: /usr/lib/gcc-lib/i486-suse-linux/2.95.2/include/stddef.h dbg.h
stddict.o: forth.h qdftypes.h stack.h
