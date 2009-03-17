/*	kill.c - kill
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
#endif

__DAVROS_IDENT("$Id$")

/*==============================================================================
 *	kill - kill	a process and remove it	from the system
 *==============================================================================
*/
__davros_status_t __davros_kill
(	__davros_process_t *proc			/* id of process to	kill  */
)
{
	__arch_intstatus_t ps;

	ps = __arch_enterkernel();

	/*	Remove from the process table */
	__davros_dequeue(&proc->proctab_entry);

	switch ( proc->state )
	{
	case __DAVROS_PRCURR:		/* suicide */
		/* FIXME: we free the memory here, and yet we still use it (implicitly)
		 * in the subsequent calls until __arch_ctxsw is called, because that's
		 * where the stack is.
		 * This is "OK" (i.e. we get away with it) with the Comer-style
		 * rescheduling, but as soon as we start tinkering it will have
		 * to change.                                              dh 17.1.2002
		*/
		__davros_dequeue(&proc->queue_entry);
		__arch_kill(proc);
		__davros_freemem(proc, proc->alloc);
		__davros.currpid = NULL;
		__davros_reschedule();
		/* Never returns. */

	case __DAVROS_PRSLEEP:	/* sleeping process */
		__davros_dequeued(&proc->queue_entry);
		__arch_kill(proc);
		__davros_freemem(proc, proc->alloc);
		break;

	case __DAVROS_PRWAIT:		/*	waiting on semaphore */
		((proc->sem)->count)++;
		/* Fall into ... */

	case __DAVROS_PRREADY:	/*	waiting on ready list */
		__davros_dequeue(&proc->queue_entry);
		/* Fall into ... */

	default:				/*	else (waiting for message, suspended) */
		__arch_kill(proc);
		__davros_freemem(proc, proc->alloc);
		break;
	}

	__arch_leavekernel(ps);

	return(__DAVROS_OK);
}
