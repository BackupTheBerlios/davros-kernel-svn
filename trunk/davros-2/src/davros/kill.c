/*	kill.c - __dv_kill
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
#include <davros/queue.h>
#include <davros/process.h>
#include <davros/cpu-intlock.h>
#include <davros/constants.h>
#include <davros/mem.h>

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

/*==============================================================================
 *	__dv_kill - kill the specified process
 *==============================================================================
*/
__dv_status_t __dv_kill
(	__dv_processstate_t *proc			/* id of process to	kill  */
)
{
	__dv_intstatus_t ps = __dv_lock();
	__dv_status_t result = __DV_OK;

	if ( proc == __DV_NULL )
	{
		proc = __dv_currproc;
	}
	else
	if ( !__DV_IS_VALID_PROCESS(proc) )
	{
		result = __DV_ERR;
	}

	if ( result == __DV_OK )
	{
		/*	Remove from the object table */
		__dv_deregisterobj(&proc->obj);

		switch ( proc->state )
		{
		case __DV_PRCURR:		/* suicide */
			/* CAVEAT: this only works cleanly because we're running on the kernel stack
			*/
#if 0 /* FIXME */
			__arch_kill(proc);
#endif
			__dv_freemem(proc, proc->nalloc);
			__dv_currproc = __DV_NULL;
			break;

#if 0
		case __DAVROS_PRSLEEP:	/* sleeping process */
			__davros_dequeued(&proc->queue_entry);
			__arch_kill(proc);
			__davros_freemem(proc, proc->alloc);
			break;

		case __DAVROS_PRWAIT:		/*	waiting on semaphore */
			((proc->sem)->count)++;
			/* Fall into ... */
#endif

		case __DV_PRREADY:		/*	waiting on ready list */
			__dv_dequeue(&proc->qent);
			/* Fall into ... */

		default:				/*	else (waiting for message, suspended) */
#if 0 /* FIXME */
			__arch_kill(proc);
#endif
			__dv_freemem(proc, proc->nalloc);
			break;
		}
	}

	__dv_restore(ps);

	return result;
}
