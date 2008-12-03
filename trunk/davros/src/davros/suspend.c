/*	suspend.c - __dv_suspend
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
#include <davros/process.h>
#include <davros/cpu-intlock.h>
#include <davros/constants.h>

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

/*====================================================================
 *	__dv_suspend - suspend a process, placing it in hibernation
 *====================================================================
*/
__dv_status_t	__dv_suspend
(	__dv_processstate_t *proc		/* process to suspend	*/
)									/* returns priority	of process */
{
	__dv_intstatus_t ps;
	__dv_status_t prio = 0;

	ps = __dv_lock();

	if ( proc == __DV_NULL )
	{
		proc = __dv_currproc;
	}
	else
	if ( __DV_IS_VALID_PROCESS(proc) )
	{
		prio = __DV_ERR;
	}

	if ( prio >= 0 )
	{
		switch ( proc->state )
		{
		case __DV_PRREADY:
			__dv_dequeue(&proc->qent);
			/* Fall into ... */

		case __DV_PRCURR:
			proc->state = __DV_PRSUSP;
			prio = proc->prio;
			break;

		default:
			prio = __DV_ERR;
			break;
		}
	}

	__dv_restore(ps);

	return prio;
}
