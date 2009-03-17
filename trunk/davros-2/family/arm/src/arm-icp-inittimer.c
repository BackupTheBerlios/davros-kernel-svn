/*	arm-icp-inittimer.c - __dv_inittimer
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
 *	__dv_inittimer - initialise the hardware timer systems on Arm Integrator/CP
 *==============================================================================
*/
__dv_status_t __dv_inittimer(void)
{
	/* Timer 1 (interrupt generator):
	 * Single shot, FRC, 32-bit, prescaler 1, interrupt enable
	 * Leave the timer and interrupt disabled for now.
	*/
	__dv_arm_timer_1.control = __DV_TCTRL_MODE_FRC |
							   __DV_TCTRL_PRESCALE_1 |
							   __DV_TCTRL_TIMER_SIZE_32 |
							   __DV_TCTRL_ONESHOT;
	__dv_arm_timer_1.load = 0;

	/* Timer 2 (time reference):
	 * Wrapping, FRC, 32-bit, prescaler 1, enable, interrupt disabled.
	 * Start at 0. Set load register to 0 as well.
	*/
	__dv_arm_timer_2.control = __DV_TCTRL_ENABLE |
							   __DV_TCTRL_MODE_FRC |
							   __DV_TCTRL_PRESCALE_1 |
							   __DV_TCTRL_TIMER_SIZE_32;
	__dv_arm_timer_2.load = 0;

	return __DV_OK;
}
