/*	schedule.c - __dv_schedule
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

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

/*====================================================================
 *	__dv_schedule - return the process most eligible for running
 *
 *  Current assumptions:
 *  1. The current process is *NOT* on the ready queue (differs from
 *     older davros versions)
 *  2. The most eligible process is that with the highest priority
 *  3. There is always a process to run.
 *  4. The ready queue and current process cannot be changed during
 *     this operation.
 *  There may be some implicit single-processor assumptions in this
 *====================================================================
*/
__dv_processstate_t	*__dv_schedule(void)
{
	__dv_processstate_t *best;

	best = (__dv_processstate_t *)(__dv_readyqueue.tail.prev->object);

	if ( (best == __DV_NULL ) ||
		 ( (__dv_currproc != __DV_NULL) &&
		   (__dv_currproc->prio >= best->prio) ) )
	{
		best = __dv_currproc;
	}
		
	return best;
}
