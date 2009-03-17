/*	wait.c - __davros_wait
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

/*==============================================================================
 *	__davros_wait - make the current process wait on a semaphore
 *==============================================================================
*/
__davros_status_t __davros_wait
(	__davros_semaphore_t *sem
)
{
	__arch_intstatus_t ps;

	ps = __arch_enterkernel();

	if ( --(sem->count) < 0 )
	{
		__davros.currpid->state = __DAVROS_PRWAIT;
		__davros.currpid->sem = sem;
		__davros_enqueue(__davros_dequeue(&__davros.currpid->queue_entry), &sem->queue);
		__davros_reschedule();
	}
	__arch_leavekernel(ps);
	return(__DAVROS_OK);
}
