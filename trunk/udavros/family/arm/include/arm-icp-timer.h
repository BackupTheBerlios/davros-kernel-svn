/*	arm-icp-timer.h - header file for arm "integrator/cp" timer
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

#ifndef __arm_icp_timer_h
#define __arm_icp_timer_h

#include <davros/basic-types.h>
#include <arm-icp-pic.h>

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

#ifndef __DV_ASM
/* This data structure represents a timer register block. The
 * fields declared as __dv_reg32_t are those that automatically update
 * without software intervention. The other fields are registers that
 * are set by software
*/
typedef struct __dv_arm_timer_s __dv_arm_timer_t;

struct __dv_arm_timer_s
{
	__dv_uint32_t	load;				/* The (re)load value for single-shot and periodic modes */
	__dv_reg32_t	timer;				/* The current value of the timer */
	__dv_uint32_t	control;			/* Timer control register; mode, int enable, etc. */
	__dv_uint32_t	int_clear;			/* Write only; clears interrupt */
	__dv_reg32_t	int_status_raw;		/* Interrupt status before masking (LSB only) */
	__dv_uint32_t	int_status_masked;	/* Interrupt status after masking (LSB only) */
	__dv_uint32_t	bg_load;			/* Same as load, but doesn't affect the timer */
};

/* There are 3 of these timer blocks on the Integrator/CP FPGA
 * Timer 0 runs at the system bus frequency.
 * Timers 1 and 2 run at 1 MHz.
 * (On qemu all three appear to run at 1 MHz)
*/
extern __dv_arm_timer_t __dv_arm_timer_0;
extern __dv_arm_timer_t __dv_arm_timer_1;
extern __dv_arm_timer_t __dv_arm_timer_2;

#define __DV_TCTRL_ENABLE		0x80
#define __DV_TCTRL_MODE			0x40
#define __DV_TCTRL_MODE_FRC			0x00
#define __DV_TCTRL_MODE_RELOAD		0x40
#define __DV_TCTRL_IE			0x20
#define __DV_TCTRL_PRESCALE		0x0C
#define __DV_TCTRL_PRESCALE_1		0x00
#define __DV_TCTRL_PRESCALE_16		0x04
#define __DV_TCTRL_PRESCALE_256		0x08
#define __DV_TCTRL_PRESCALE_UNDEF	0x0C
#define __DV_TCTRL_TIMER_SIZE	0x02
#define __DV_TCTRL_TIMER_SIZE_16	0x00
#define __DV_TCTRL_TIMER_SIZE_32	0x02
#define __DV_TCTRL_ONESHOT		0x01

/* For davros' system timer we use timer 2 (configured as free-running) for the reference
 * time, and timer 1 (configured as 1 shot) for generating interrupts.
 * The timer is full 32-bits, so no wrapping problems.
 * The timer is a down-counter so we negate if for use in the kernel.
*/
#define __DV_TIMER_INTVEC	__DV_INTNUM_TIMER1

#define __dv_readtimer()	(-__dv_arm_timer_2.timer)
#define __dv_subtimer(x, y)	((x)-(y))

__dv_status_t __dv_inittimer(void);
__dv_status_t __dv_settimer(__dv_uint32_t, __dv_uint32_t);

#endif

#if 0
#define __DV_MAXINTERVAL		0xc0000000
#define __DV_DEFINTERVAL		0x80000000
#else
/* For testing let's keep things quick
*/
#define __DV_MAXINTERVAL		1000000
#define __DV_DEFINTERVAL		500000
#endif

#endif
