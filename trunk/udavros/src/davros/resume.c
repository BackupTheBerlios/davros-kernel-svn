/*	resume.c - __dv_resume
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

/*==============================================================================
 *	__dv_resume - unsuspend a process, making it ready; return the priority
 *==============================================================================
*/
__dv_status_t __dv_resume
(	__dv_processstate_t *proc
)
{	
	__dv_intstatus_t ps;
	__dv_status_t	prio = 0;

/*	__DV_DEBUG(1, KDBG_BASIC, "__dv_resume(0x%08x,%d)\n", proc, resch);
*/

	ps = __dv_lock();

	if ( proc == __DV_NULL )
	{
		proc = __dv_currproc;
	}
	else
	if ( !__DV_IS_VALID_PROCESS(proc) )
	{
		prio = __DV_ERR;
	}

	if ( prio >= 0 )
	{
		if ( proc->state == __DV_PRSUSP )
		{
			prio = proc->prio;
			__dv_ready(proc);
		}
		else
		{
			prio = __DV_ERR;
		}
	}

	__dv_restore(ps);

	return prio;
}
