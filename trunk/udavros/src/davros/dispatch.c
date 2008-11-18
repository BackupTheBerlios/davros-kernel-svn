/*	dispatch.c - __dv_dispatch
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
#include <davros/basic-types.h>
#include <davros/init.h>
#include <davros/process.h>
#include <davros/queue.h>

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

/*====================================================================
 *	__dv_dispatch - dispatch the process at the tail of the readyqueue
 *
 * Incoming process is at head of ready queues, needs to be dequeued.
 * Outgoing process is __dv_currproc, needs to be enqueued.
 * Outgoing process' state has been saved already.
 *====================================================================
*/
void __dv_dispatch(__dv_int_t disp_sync)
{
	__dv_qent_t *qent = __dv_dequeue(__dv_readyqueue.tail.prev);

	if ( __dv_currproc != __DV_NULL )
	{
		__dv_currproc->state = __DV_PRREADY;
		__dv_insert(&__dv_currproc->qent, &__dv_readyqueue, __dv_currproc->prio);
	}

	__dv_currproc = (__dv_processstate_t *)qent->object;
	__dv_currproc->state = __DV_PRCURR;

	__dv_in_kernel = 0;
	__dv_ctxtsw(&__dv_currproc->registers);		/* Never returns */
}
