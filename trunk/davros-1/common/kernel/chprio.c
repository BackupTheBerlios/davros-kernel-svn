/*	chprio.c - __davros_chprio
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

/*====================================================================
 *	__davros_chprio - change the priority of a process
 *====================================================================
*/
byte_t __davros_chprio
(	__davros_process_t *proc,	/* process to change	*/
	byte_t newprio				/* new priority */
)								/* returns old priority	of process */
{
	__arch_intstatus_t ps;
	byte_t oldprio;

	ps = __arch_enterkernel();

	oldprio = proc->priority;
	proc->priority = newprio;

	if ( proc->state == __DAVROS_PRREADY || proc->state == __DAVROS_PRCURR )
	{	__davros_insert(__davros_dequeue(&proc->queue_entry),&__davros.readyqueue,newprio);
		__davros_reschedule();
	}

	__arch_leavekernel(ps);

	return(oldprio);
}