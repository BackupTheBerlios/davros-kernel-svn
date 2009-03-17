/*	i8253.h - 8253 counter/timer and derivatives, including 8254
 *
 *	Copyright 2002 David Haworth
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
 *	This file contains definitions for the intel 8253 counter/timer
 *
*/

#ifndef __i8253_h
#define __i8253_h

/*	We defined the registers as offsets from a base address for two
 *	reasons:
 *		1 -	the device is often i/o mapped on x86 systems 
 *		2 -	the device registers are often decoded at 16- or 32-bit
 *			intervals instead of the normal 8.
*/

#define i8253_c0	0		/* Counter 0 */
#define	i8253_c1	1		/* Counter 1 */
#define	i8253_c2	2		/* Counter 2 */
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


#endif
