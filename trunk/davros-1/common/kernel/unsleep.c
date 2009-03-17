/*	unsleep.c - __davros_unsleep
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
 *	__davros_unsleep - remove a process from the sleep queue and ready it
 *==============================================================================
*/
__davros_status_t __davros_unsleep
(	__davros_process_t *pid
)
{
	__arch_intstatus_t ps;

	ps = __arch_enterkernel();

	if ( pid->state == __DAVROS_PRSLEEP )
	{
		__davros_dequeued(&pid->queue_entry);
		if ( __davros.sleepqueue.head.next == &__davros.sleepqueue.tail )
			__davros.sleepcount = NULL;
		else
			__davros.sleepcount = &__davros.sleepqueue.head.next->kd.key;
		__davros_ready(pid, TRUE);
	}

	__arch_leavekernel(ps);

	return(__DAVROS_OK);
}
