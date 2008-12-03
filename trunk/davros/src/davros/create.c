/*	create.c - __dv_create
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
#include <davros/mem.h>
#include <davros/object.h>
#include <davros/constants.h>

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

/*==============================================================================
 *	__dv_create - create a process that runs a given function
 *==============================================================================
*/
__dv_processstate_t *__dv_create
(	const __dv_processconfig_t *pconfig,
	__dv_pprio_t prio
)
{
	__dv_processstate_t *proc;
	__dv_intstatus_t ps;
	__dv_uchar_t *tmpptr;
	__dv_size_t prcsize;
	__dv_size_t stksize;

/*	KDBG(1, KDBG_BASIC, "__dv_create(%s)\n", name);
*/

	ps = __dv_lock();

	/* Allocate memory for process and stack all together. This means that
	 * if the process overflows its stack, the first thing it hits is
	 * its own process entry.
	 * There are two arrangement here; one for processors whose stack grows
	 * DOWN from a HIGH address and one for processors whose stack grows UP.
	*/
	prcsize = __DV_STACKROUND(sizeof(__dv_processstate_t));
	stksize = __DV_STACKROUND(pconfig->stacksize + __DV_EXTRASTACK);
	tmpptr = __dv_getmem(prcsize + stksize);

	if ( tmpptr == __DV_NULL )
	{
		proc = __DV_NULL;
	}
	else
	{
#if __DV_STACKGROWS == __DV_STACKGROWSUP
#error "Probably needs work"
		proc = (__dv_processstate_t *)&tmpptr[stksize+__DV_EXTRASTACK];
#else
		proc = (__dv_processstate_t *)tmpptr;
		tmpptr += prcsize;
#endif

		proc->obj.type = __DV_OBJTYPE_PROCESS;

		if ( __dv_registerobj(&proc->obj) < 0 )
		{
			__dv_freemem(tmpptr, prcsize + stksize);
			proc = __DV_NULL;
		}
		else
		{
			__dv_initqent(&proc->qent, &proc->obj);
		
			proc->config = pconfig;
			proc->stack = (__dv_stackelement_t *)tmpptr;
			proc->nalloc = prcsize + stksize;
			proc->state = __DV_PRSUSP;
			proc->prio = prio;

			__dv_initialregisters(proc);
		}
	}

	__dv_restore(ps);
	
	return proc;
}
