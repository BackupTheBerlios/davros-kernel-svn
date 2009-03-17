/*	create.c - __davros_create
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

/*==============================================================================
 *	__davros_create - create a process to start running a procedure
 *==============================================================================
*/
__davros_process_t *__davros_create
(	__davros_procentry_t procaddr,	/* procedure address */
	size_t stksize,					/* stack size in bytes */
	byte_t prio,					/* priority	>0 */
	char *name,						/* process name */
	__davros_device_t *in,			/* stdin for process */
	__davros_device_t *out,			/* stdout for process */
	__davros_device_t *err,			/* stderr for process */
	int nargs,						/* no of arguments */
	int *args						/* list of arguments */
)
{
	__davros_process_t *proc;
	__arch_intstatus_t ps;
	byte_t *tmpptr;
	int *argp;
	size_t alloc;

	KDBG(1, KDBG_BASIC, "__davros_create(%s)\n", name);

	ps = __arch_enterkernel();

	/*	Allocate memory for process and stack all together. This means that
		if the process overflows its stack, the first thing it hits is
		its own process entry.
		There are two arrangement here; one for processors whose stack grows
		DOWN from a HIGH address and one for processors whose stack grows UP.
	*/
	alloc = sizeof(__davros_process_t) + nargs*sizeof(int) +
                                stksize + __DAVROS_EXTRASTACK;
	tmpptr = __davros_getmem(alloc);
	if ( tmpptr == NULL )
	{
		proc = NULL;
	}
	else
	{
#ifdef __DAVROS_STACKGROWSUP
		proc = (__davros_process_t *)&tmpptr[stksize+__DAVROS_EXTRASTACK];
#else
		proc = (__davros_process_t *)tmpptr;
		tmpptr += sizeof(__davros_process_t) + stksize + __DAVROS_EXTRASTACK;
#endif
		__davros_initproc(proc);
		proc->alloc = alloc;
		proc->start = procaddr;
		proc->nargs = nargs;
		proc->args = (nargs == 0) ? NULL : (int *)(proc+1);
		argp = proc->args;
		while ( nargs > 0 )
		{
			*argp++ = *args++;
			nargs--;
		}
		
		__davros_enqueue(&proc->proctab_entry, &__davros.proctab);
		proc->state = __DAVROS_PRSUSP;
		proc->priority = prio;
		proc->stacksize = stksize + __DAVROS_EXTRASTACK;
		__davros_setstdio(proc, in, out, err);
		strncpy(proc->name, name, __DAVROS_PNMLEN);

		__arch_initproc(proc, (memaddr_t)tmpptr);
	}

	__arch_leavekernel(ps);

	return(proc);
}
