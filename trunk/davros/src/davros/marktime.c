/*	marktime.c - __dv_marktime
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
#include <davros/process.h>

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

/*==============================================================================
 *	__dv_marktime - mark the passage of time
 *==============================================================================
*/
void __dv_marktime(void)
{
	__dv_uint32_t now;
	__dv_uint32_t diff;

	__dv_stoptimer();

	/* Repeat until a time in the future is discovered
	*/
	do {
		/* Read latest timer value, compute difference, save latest value for next time
		*/
		now = __dv_readtimer();
		diff = __dv_subtimer(now, __dv_last_timer_value);
		__dv_last_timer_value = now;

		/* Add the difference onto the absolute time
		*/
		__dv_time += diff;

		/* Inform the sleepers of the passage of time
		*/
		diff = __dv_tick(diff);

		/* Try to set an interrupt for the remaining time to next wakeup.
		 * If that fails (already in the past), go round again
		*/
	} while ( __dv_settimer(__dv_last_timer_value, diff) != __DV_OK );
}
