/*	gptu-drv.c - Driver for Tricore GPTU module
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
 *	This file contains a driver for Tricore's general-*	purpose timer
 *	module (GPTU)
 *
 *	The driver is a simple regular-tick interrupt driver. It initialises
 *	either timer 0 or timer 1 of the specified GPTU to give regular
 *	interrupts of the specified priority at the specified frequency in
 *	Hz. It is up to the application to attach an interrupt handler to
 *	the vector.
*/

#include "drv/gptu-drv.h"
#include "drv/mod-drv.h"
#include "drv/pwr-drv.h"

/*
 *	gptu_timer_start() - initialise a timer
 *
 *	This function initialises either timer 0 or timer 1 of the
 *	specified GPTU to generate interrupts at a frequency specified
 *	in hz. The interrupt priority number is inum.
 *	If the GPTU fails to start, or the timer is already in use,
 *	the function returns -1.
 *	The function uses all 4 stages of the timer, even if fewer
 *	could be used. The interrupt is left disabled to allow the
 *	application to attach a handler first.
*/
int gptu_timer_start(tricore_gptu_t *gptu, int timer, int inum, int hz)
{
	/*	Ensure timer module is running. */
	if ( tricore_module_init(&gptu->gptu_hdr, 0, 1) != 0 )
		return(-1);

	/* Rest of code depends on which timer is requested. */
	switch ( timer )
	{
	case 0:
		if ( (gptu->gptu_t012run & GPTU_T0RUN) != 0 )
			return(-1);		/* Already in use */

		/* Set timer to 32-bit counter */
		gptu->gptu_t01irs = (gptu->gptu_t01irs & ~(GPTU_T0INS | GPTU_T0REL)) |
							(GPTU_T0AINS & GPTU_TxyINS_CLK) |
							(GPTU_T0BINS & GPTU_TxyINS_CARRY) |
							(GPTU_T0CINS & GPTU_TxyINS_CARRY) |
							(GPTU_T0DINS & GPTU_TxyINS_CARRY) |
							(GPTU_T0AREL | GPTU_T0BREL | GPTU_T0CREL);

		/* Take all outputs from stage D */
		 gptu->gptu_t01ots = (gptu->gptu_t01ots & ~(GPTU_SALL0)) |
							 (GPTU_SALL0 & GPTU_SS_TxDOFLO);

		/*	Set counter and reload register to desired value */
		gptu->gptu_t0dcba = gptu->gptu_t0rdcba = -(module_clock_rate() / hz);

		/*	Allow all 4 stages of counter to run */
		gptu->gptu_t012run |= GPTU_T0RUN;

		/*	Attach service node 0 to service request 0 */
		gptu->gptu_gtsrsel = (gptu->gptu_gtsrsel & ~GPTU_GTSSR0) |
							 (GPTU_GTSSR0 & GPTU_GTSSRx_SR00);
		gptu->gptu_gtsrc0 = ISR_TOS_CPU | inum;
		break;
	case 1:
		/* FIXME: to do */
		return(-1);
		break;
	default:
		return(-1);
	}
	return(0);
}

/*
 *	gptu_timer_stop() - stops the timer
 *
 *	This function stops the specified timer by setting all the
 *	appropriate run bits to 0. The interrupt remains enabled.
*/
int gptu_timer_stop(tricore_gptu_t *gptu, int timer)
{
	/*	Ensure timer module is running. */
	if ( tricore_module_init(&gptu->gptu_hdr, 0, 1) != 0 )
		return(-1);

	switch ( timer )
	{
	case 0:
		gptu->gptu_t012run &= ~GPTU_T0RUN;
		break;
	case 1:
		gptu->gptu_t012run &= ~GPTU_T1RUN;
		break;
	default:
		return(-1);
	}
	return(0);
}

/*
 *	gptu_timer_enable_int() - enable interrupt for timer
 *
 *	This function enables the interrupt for a timer.
*/
int gptu_timer_enable_int(tricore_gptu_t *gptu, int timer)
{
	switch ( timer )
	{
	case 0:
		gptu->gptu_gtsrc0 |= ISR_SRE;
		break;
	case 1:
		gptu->gptu_gtsrc1 |= ISR_SRE;
		break;
	default:
		return(-1);
	}
	return(0);
}

/*
 *	gptu_timer_disable_int() - disable interrupt for timer
 *
 *	This function disables the interrupt for a timer and cancels
 *	any pending interrupt.
*/
int gptu_timer_disable_int(tricore_gptu_t *gptu, int timer)
{
	switch ( timer )
	{
	case 0:
		gptu->gptu_gtsrc0 = (gptu->gptu_gtsrc0 & ~ISR_SRE) | ISR_CLRR;
		break;
	case 1:
		gptu->gptu_gtsrc1 = (gptu->gptu_gtsrc1 & ~ISR_SRE) | ISR_CLRR;
		break;
	default:
		return(-1);
	}
	return(0);
}
