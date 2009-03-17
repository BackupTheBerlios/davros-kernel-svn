/*	timer-a-drv.c - Driver for MSP430 Timer A module
 *
 *	$Id$
 *	Copyright 2004 David Haworth
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
 *	This file contains a driver for MSP430's timer A module. The
 *  module contains a 16-bit counter and 3 capture/compare units.
 *
 *	The timer has 2 useful modes of operation:
 *
 *	 "up" mode: the timer counts upward from zero until the value in
 *      compare register 0 is reached. It then goes back to zero
 *      and generates an interrupt. This mode requires no further
 *      assistance from software, but makes it more difficult to
 *      use the other 2 compare registers for other timing functions.
 *
 *   "continuous" mode: the timer is effectively a free-running
 *      counter. When the timer matches one of the compare registers
 *      an interrupt is generated. It is up to the software to
 *      calculate when the next interrupt should occur and reprogram
 *      the compare register accordingly. In this mode, all 3 compare
 *      units can be used independently.
 *
 *	The other 2 possible modes are "stop" and "up/down". Stop mode
 *	is selected by timer_a_stop(). Up/down doesn't appear to be
 *	useful for davros' purposes.
 *
 *	For the first cut here we'll use "up" mode. We simply write the
 *	desired period into compare register 0 and the put suitable
 *	values into the fields of tctl
 *
 *	$Log: timer-a-drv.c,v $
 *	Revision 1.1  2004/05/11 20:39:27  dave
 *	Files for the MSP430 port.
 *	
*/

#include "kernel-config.h"
#include "arch-cpudef.h"
#include "davros/kernel.h"
#include "drv/timer-a-drv.h"
#include "msp430.h"

/*
 *	timer_a_start() - initialise the timer
 *
 *	This function initialises timer A.
 *  clkhz is the input frequency for the timer.
 *  hz is the desired interrupt frequency
*/
int timer_a_start(void)
{
	timer_a.ctl = 0;		/* Stop the timer */
	timer_a.taccr0 = (__DAVROS_ACLK_HZ/__DAVROS_HZ) - 1;
	timer_a.taccr1 = timer_a.taccr2 = 0xffff;
	timer_a.cctl0 = TCCTL_CCIS_GND | TCCTL_CCIE;
	timer_a.cctl1 = timer_a.cctl2 = TCCTL_CCIS_GND;
	timer_a.ctl = TCTL_TASSEL_ACLK
				| TCTL_ID_1
				| TCTL_MC_UP
				| TCTL_TACLR;

	return 0;
}

/*
 *	timer_a_stop() - stops the timer
 *
 *	This function stops the specified timer by setting the
 *	mode bits to "stop" mode. The interrupt remains enabled.
*/
int timer_a_stop(void)
{
	timer_a.ctl &= ~(TCTL_MC);
	
	return 0;
}

/*
 *	timer_a0_int() - interrupt service
 *
 *	This routine is the interrupt service routine for timer A
 *	compare 0 interrupts. Because the timer is in "up" mode,
 *	no hardware interaction is neede, so we simply call
 *	__davros_tick().
*/
unsigned timer_a_count;		/* Debug stuff */

void __attribute__((interrupt (TIMERA0_VECTOR))) timer_a0_int(void)
{
	timer_a_count++;		/* Debug stuff */
	__davros_tick();
}
