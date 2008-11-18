/*	chprio.c - __dv_chprio
 *
 *	Copyright 2008 David Haworth
 *
 *	This file is part of davros.
 *
 *	davros is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	davros is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with davros.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <davros/config.h>
#include <davros/constants.h>
#include <davros/process.h>
#include <davros/cpu-intlock.h>

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

/*====================================================================
 *	__dv_chprio - change the priority of a process
 *====================================================================
*/
__dv_int_t __dv_chprio
(	__dv_processstate_t *proc,	/* process to change	*/
	__dv_pprio_t newprio		/* new priority */
)								/* returns old priority	of process */
{
	__dv_intstatus_t ps;
	__dv_int_t oldprio = 0;

	ps = __dv_lock();

	if ( proc == __DV_NULL )
	{
		/* Change the priority of the current process.
		 * The current process is never anything other than PRCURR.
		*/
		oldprio = __dv_currproc->prio;
		__dv_currproc->prio = newprio;
	}
	else
	if ( __DV_IS_VALID_PROCESS(proc) )
	{
		/* Change the priority of the specified process
		*/
		oldprio = proc->prio;
		proc->prio = newprio;

		if ( proc->state == __DV_PRREADY )
		{
			/* The process is on the ready list so we need to dequeue it an re-insert it
			 * so that it moves to the correct place in the queue.
			*/
			__dv_insert(__dv_dequeue(&proc->qent), &__dv_readyqueue, newprio);
		}
	}
	else
	{
		oldprio = __DV_ERR;
	}

	__dv_restore(ps);

	return oldprio;
}
