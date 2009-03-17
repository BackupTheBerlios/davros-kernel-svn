/*	resume.c - __davros_resume
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
#include "davros/kdebug.h"
#endif

__DAVROS_IDENT("$Id")

/*==============================================================================
 *	__davros_resume - unsuspend a process, making it ready; return the priority
 *==============================================================================
*/
__davros_status_t __davros_resume
(	__davros_process_t *proc,
	boolean_t resch
)
{	
	__arch_intstatus_t ps;
	__davros_status_t	prio;

	KDBG(1, KDBG_BASIC, "__davros_resume(0x%08x,%d)\n", proc, resch);

	ps = __arch_enterkernel();
	if ( proc->state == __DAVROS_PRSUSP )
	{
		prio = proc->priority;
		__davros_ready(proc, resch);
	}
	else
	{
		prio = __DAVROS_SYSERR;
	}

	__arch_leavekernel(ps);

	return(prio);
}
