/*	reschedule.c - __davros_reschedule
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

#ifndef __DAVROS_ASM_RESCHEDULE

#ifndef __DAVROS_COMPLETE
#include "davros/kernel.h"
#include "davros/kdebug.h"
#endif

__DAVROS_IDENT("$Id$")

/*==============================================================================
 *	__davros_reschedule - reschedule processor to highest priority ready process
 *==============================================================================
*/
/*
 *	Notes:
 *	1.	Upon entry, __davros.currpid gives the current process.
 *		__davros.currpid->state gives correct NEXT state for
 *		current process if other than __DAVROS_PRREADY
 *	2.  The current process is always at the top of the ready
 *		list unless just preempted
*/
__davros_status_t __davros_reschedule(void)
{
	__davros_process_t *oldproc;

	KDBG(1, KDBG_BASIC, "__davros_reschedule()\n");

	/* no switch needed if current process is at top of ready list */
	if ( (__davros_process_t *)(__davros.readyqueue.tail.prev) == __davros.currpid )
		return(__DAVROS_OK);

	/* remember the old process, and mark it READY if it's current.
		NB currpid may be NULL - see kill() */
	oldproc = __davros.currpid;
	if ( oldproc != NULL && oldproc->state == __DAVROS_PRCURR )
	{
		oldproc->state = __DAVROS_PRREADY;
	}

	/* get highest priority process from end of ready list and
	   mark it currently running */
	__davros.currpid = (__davros_process_t *)(__davros.readyqueue.tail.prev);
	__davros.currpid->state = __DAVROS_PRCURR;

	/* do the context switch */
	KDBG(1, KDBG_BASIC, "__davros_reschedule() calling ctxsw(0x%08x, 0x%08x)\n",
			oldproc, __davros.currpid);
	KDBG(2, KDBG_BASIC, "oldproc is %s, newproc is %s\n",
			oldproc->name, __davros.currpid->name);
	__arch_ctxsw((oldproc == NULL) ? NULL : &oldproc->registers,
					&__davros.currpid->registers);

	/* the old process returns here when resumed */

	return(__DAVROS_OK);
}

#endif
