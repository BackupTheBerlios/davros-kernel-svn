/*	i8253-timer.h - header file for i8253 timer
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

#ifndef __i8253_timer_h
#define __i8253_timer_h

#include <davros/basic-types.h>

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

#ifndef __DV_ASM

/*	We define the registers as offsets from a base address for two
 *	reasons:
 *		1 - the device is often i/o mapped on x86 systems 
 *		2 - the device registers are often decoded at 16- or 32-bit
 *			intervals instead of the normal 8.
*/

#define i8253_c0	0		/* Counter 0 */
#define i8253_c1	1		/* Counter 1 */
#define i8253_c2	2		/* Counter 2 */
#define i8253_ctrl	3		/* Common control */

#define I8253_CTRL_SEL	0xc0		/* Counter select */
#define I8253_CTRL_SEL_C0	0x00
#define I8253_CTRL_SEL_C1	0x40
#define I8253_CTRL_SEL_C2	0x80
#define I8254_CTRL_SEL_RB	0x80	/* Readback (8254 only) */
#define I8253_CTRL_RWL	0x30		/* Read/write/latch */
#define I8253_CTRL_RWL_LTCH	0x00	/* Latch present counter value */
#define I8253_CTRL_RWL_M	0x10	/* Read/write MSB only */
#define I8253_CTRL_RWL_L	0x20	/* Read/write LSB only */
#define I8253_CTRL_RWL_LM	0x30	/* Read/write LSB then MSB */
#define I8253_CTRL_MODE	0x0e
#define I8253_CTRL_MODE_ITC	0x00	/* Interrupt on terminal count */
#define I8253_CTRL_MODE_P1S	0x02	/* Programmable one-shot */
#define I8253_CTRL_MODE_RG	0x04	/* Rate generator */
#define I8253_CTRL_MODE_SQW	0x06	/* Square wave generator */
#define I8253_CTRL_MODE_STS	0x08	/* Software triggered strobe */
#define I8253_CTRL_MODE_HTS	0x0a	/* Hardware triggered strobe */
#define I8253_CTRL_MODE_QQ1	0x0c	/* ? reserved */
#define I8253_CTRL_MODE_QQ2	0x0e	/* ? reserved */
#define I8253_CTRL_BCD	0x01		/* 0 = binary, 1 = 4-digit BCD */

/* For davros' system timer we use timer 2 (configured as free-running) for the reference
 * time, and timer 1 (configured as 1 shot) for generating interrupts.
 * The timer is 16-bits, so we must enforce the wrap
 * The timer is a down-counter so we negate if for use in the kernel.
*/
#define __DV_TIMER_INTVEC	__DV_INTNUM_TIMER1

#define __dv_readtimer()	(-__dv_arm_timer_2.timer)
#define __dv_subtimer(x, y)	(((x)-(y))&0xffff)

__dv_status_t __dv_inittimer(void);
__dv_status_t __dv_settimer(__dv_uint32_t, __dv_uint32_t);
__dv_status_t __dv_stoptimer(void);

#endif

#define __DV_MAXINTERVAL		0xc000
#define __DV_DEFINTERVAL		0x8000

#endif
