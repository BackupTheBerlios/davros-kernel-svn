/*	inittime.c - __dv_inittime
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
#include <davros/basic-types.h>
#include <davros/constants.h>
#include <davros/queue.h>
#include <davros/time.h>
#include <davros/interrupt.h>

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

/*==============================================================================
 *	Kernel variables
 *==============================================================================
*/
__dv_uint64_t	__dv_time;
__dv_uint32_t	__dv_last_timer_value;
__dv_queue_t	__dv_sleepqueue;


/*==============================================================================
 *	__dv_inittime - initialise the time subsystem
 *==============================================================================
*/
void __dv_inittime(void)
{
	/* Davros time starts at zero. Time-of-day is done by adding an offset to this.
	*/
	__dv_time = 0;

	/* Initialise the sleep queue
	*/
	__dv_initqueue(&__dv_sleepqueue);

	/* Initialise the timer hardware
	*/
	__dv_inittimer();

	/* Initialise the last-known timer value by reading the timer
	*/
	__dv_last_timer_value = __dv_readtimer();

	/* Register __dv_marktime() as interrupt service routine for the timer
	*/
	__dv_register_interrupt(__DV_TIMER_INTVEC, (__dv_interruptfunc_t)__dv_marktime, __DV_NULL);
	__dv_enable_interrupt(__DV_TIMER_INTVEC);

	/* Set an alarm for the "default" interval (typically half a timer round)
	*/
	__dv_settimer(__dv_last_timer_value, __DV_DEFINTERVAL);
}
