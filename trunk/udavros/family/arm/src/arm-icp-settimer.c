/*	arm-icp-settimer.c - __dv_settimer
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
#include <arm-icp-timer.h>

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

/*==============================================================================
 *	__dv_settimer - sets the timer to generate an interrupt after a given delta
 *==============================================================================
*/
__dv_status_t __dv_settimer(__dv_uint32_t last, __dv_uint32_t delta)
{
	__dv_uint32_t elapsed =  __dv_readtimer() - last;
	__dv_status_t result = __DV_ERR;

	if ( elapsed < delta )
	{
		delta -= elapsed;
		__dv_arm_timer_1.control = __DV_TCTRL_ENABLE |
								   __DV_TCTRL_MODE_RELOAD |
								   __DV_TCTRL_IE |
								   __DV_TCTRL_PRESCALE_1 |
								   __DV_TCTRL_TIMER_SIZE_32 |
								   __DV_TCTRL_ONESHOT;
		__dv_arm_timer_1.load = delta;
		result = __DV_OK;
	}

	return result;
}
