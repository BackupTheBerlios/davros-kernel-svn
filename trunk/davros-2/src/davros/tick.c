/*	tick.c - __dv_tick
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
#include <davros/basic-types.h>
#include <davros/time.h>
#include <davros/queue.h>
#include <davros/process.h>

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

/*==============================================================================
 *	__dv_tick - be aware of the passage of time
 *==============================================================================
*/
__dv_uint32_t __dv_tick
(	__dv_uint32_t nticks		/* No of ticks that have passed since last time */
)
{
	__dv_qent_t *qent;

	while ( __dv_sleepqueue.head.next->key <= nticks )
	{
		qent = __dv_dequeue(__dv_sleepqueue.head.next);
		nticks -=  qent->key;

		if ( qent->object->type == __DV_OBJTYPE_PROCESS )
		{
			__dv_ready((__dv_processstate_t *)(qent->object));
		}
		else
		{
		}
	}

	if ( __dv_sleepqueue.head.next != &__dv_sleepqueue.tail )
	{
		__dv_sleepqueue.head.next->key -= nticks;
	}

	return __dv_sleepqueue.head.next->key;
}
