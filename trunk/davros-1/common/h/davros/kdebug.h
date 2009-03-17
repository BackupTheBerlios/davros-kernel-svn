/*	kdebug.h - some kernel debug stuff
 *
 *	Copyright 2001 David Haworth
 *
 *	This file is free software; you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation; either version 2, or (at your option)
 *	any later version.
 *
 *	It is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with this program; see the file COPYING.  If not, write to
 *	the Free Software Foundation, 59 Temple Place - Suite 330,
 *	Boston, MA 02111-1307, USA.
 *
 *
*/

#ifndef __davros_kdebug_h
#define __davros_kdebug_h

#ifdef __DAVROS_DEBUGGING

int kprintf( const char *fmt, ...);
extern int __dbglvl;
extern int __dbgflg;

#define KDBG(l,f,args...)	\
	if ( (__dbglvl >= l) && (__dbgflg & f))	\
		kprintf(## args)

/* Flags */
#define	KDBG_BASIC	0x00000001		/* Reschedule, suspend, resume, create */
#define	KDBG_SEM	0x00000002		/* Semaphore operations */
#define KDBG_MSG	0x00000004		/* Message send & receive */
#define KDBG_TIMER	0x00000008		/* Message send & receive */
#define KDBG_DEV	0x00000010		/* Device subsystem */

#else

#define KDBG(l,f,args...)

#endif

#endif
