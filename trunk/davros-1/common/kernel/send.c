/*	send.c - __davros_send
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

__DAVROS_IDENT("$Id")

/*==============================================================================
 *	__davros_send - send a message to another process
 *==============================================================================
*/
__davros_status_t __davros_send
(	__davros_process_t *proc,		/* process to send message to */
	__davros_msg_t msg,			/* message to send */
	boolean_t resch				/* reschedule? */
)
{
	__arch_intstatus_t ps;
	__davros_status_t	result;

	ps = __arch_enterkernel();

	if ( proc == NULL || proc->hasmsg )
	{
		result = __DAVROS_SYSERR;
	}
	else
	{
		proc->hasmsg = TRUE;
		proc->msg = msg;
		if ( proc->state == __DAVROS_PRRECV )
		{
			/* process is wating for the message, so let it run. */
			__davros_ready(proc, resch);
		}

		result = __DAVROS_OK;
	}

	__arch_leavekernel(ps);

	return(result);
}
