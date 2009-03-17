/*	sleep.c - __dv_sleep
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
#include <davros/queue.h>
#include <davros/time.h>
#include <davros/process.h>
#include <davros/constants.h>

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

/*==============================================================================
 *	__dv_sleep - delay caller for the specified number of timer ticks
 *==============================================================================
*/
__dv_status_t __dv_sleep
(	__dv_uint32_t nticks
)
{
	__dv_status_t result = __DV_OK;
	__dv_uint32_t now, diff;

	/* If no. of ticks is higher than max we return an error. If it's lower than
	 * min we silently don't sleep
	*/
	if ( nticks > DV_CFG_MAXSLEEP )
	{
		result = __DV_ERR;
	}
	else
	if ( nticks >= DV_CFG_MINSLEEP )
	{
		/* Read the current timer value and determine how much time has elapsed
		 * since we last read the timer
		*/
		now = __dv_readtimer();
		diff = __dv_subtimer(now, __dv_last_timer_value);

		if ( __dv_sleepqueue.head.next->next == __DV_NULL )
		{
			/* The sleep queue is empty, so we just reset the interrupt for the delta.
			 * If that succeeds, we insert the caller into the queue and set it sleeping.
			 * If it fails (time in the past) we just continue; the process remains current.
			*/
			__dv_last_timer_value = now;
			__dv_time += diff;
			if ( __dv_settimer(now, nticks) == __DV_OK )
			{
				__dv_insertd(&__dv_currproc->qent, &__dv_sleepqueue, nticks);
				__dv_currproc->state = __DV_PRSLEEP;
			}
		}
		else
		{
			/* The sleep queue is not empty. The entry at the head of the sleep queue has been
			 * waiting for a while. Somehow we need to account for the ticks that have elapsed
			 * since the last-known timer value.
			*/
			if ( (0xfffffffe - nticks) >= diff )
			{
				/* Easy case (and probably the most frequent) - we can account for all the ticks
				 * by adding them to the required delay. We don't need to start waking up the
				 * sleepers.
				*/
				__dv_insertd(&__dv_currproc->qent, &__dv_sleepqueue, nticks+diff);
				__dv_currproc->state = __DV_PRSLEEP;
			}
			else
			{
				/* This shouldn't happen if MAXSLEEP is configured correctly, but just in
				 * case we'll return an error.
				*/
				result = __DV_ERR;
			}
		}
	}

	return result;
}
