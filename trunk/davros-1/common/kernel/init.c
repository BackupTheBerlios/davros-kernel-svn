/*	init.c - __davros_init
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

#ifndef __DAVROS_COMPLETE
#include "davros/kernel.h"
#include "string.h"
#include "davros/kdebug.h"
#endif

__DAVROS_IDENT("$Id$")

/*==============================================================================
 *	__davros_init - initialise all DAVROS data structures
 *==============================================================================
*/
void __davros_init
(	memaddr_t membot,		/* Bottom of free memory */
	memaddr_t memtop		/* Top of free memory */
)
{
	KDBG(1, KDBG_BASIC, "__davros_init(0x%08x, 0x%08x)\n", membot, memtop);

	__davros.membot = membot;
	__davros.memtop = memtop;

	__davros.numproc = 0;
	__davros.clkpres = TRUE;
	__davros.frc = 0;

	/* The process entry and stack for the null process is carved out
	 * of the bottom of free memory. */
	__davros.currpid = (__davros_process_t *)membot;
	membot += sizeof(__davros_process_t)+__DAVROS_NULLSTACK+__DAVROS_EXTRASTACK;

	__davros.memhead.next = (__davros_mblock_t *)membot;
	__davros.memhead.len  = 0;

	__davros.memhead.next->next = NULL;
	__davros.memhead.next->len = memtop - membot;

	__davros_initqueue(&__davros.proctab);
	__davros_initqueue(&__davros.readyqueue);
	__davros_initqueue(&__davros.sleepqueue);
	__davros_initqueue(&__davros.devtab);

	__davros.sleepcount = NULL;

#ifdef __ARCH_KERNEL_DATA
	__arch_initkernel(&__davros);
#endif

	__davros_initproc(__davros.currpid);
	__davros_enqueue(&__davros.currpid->proctab_entry, &__davros.proctab);
	__davros.currpid->stacksize = __DAVROS_NULLSTACK + __DAVROS_EXTRASTACK;
	__davros.currpid->state = __DAVROS_PRCURR;
	strncpy(__davros.currpid->name, "_null", __DAVROS_PNMLEN);

	__davros_insert(&__davros.currpid->queue_entry, &__davros.readyqueue, 0);

	__arch_setstack(((memaddr_t)__davros.currpid) +
						sizeof(__davros_process_t) +
						__davros.currpid->stacksize);

	__arch_init();
	__user_init();
	while (1)
	{
		__user_nullproc();
	}
}
