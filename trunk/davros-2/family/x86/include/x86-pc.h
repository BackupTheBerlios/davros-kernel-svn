/*	x86-pc.h - header file for an x86-based PC
 *
 *	Copyright 2009 David Haworth
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

#ifndef __dv_x86_pc_h
#define __dv_x86_pc_h

#include <x86-core.h>

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

/* I/O addresses of standard PC peripherals
*/
#define __dv_i8259_master	0x20		/* Master interrupt controller */
#define __dv_i8259_slave	0xa0		/* Slave interrupt controller */
#define __dv_i8253_base		0x40		/* Programmable interval timer */
#define __dv_i8250_com1		0x3f8		/* UART COM1 */
#define __dv_i8250_com2		0x2f8		/* UART COM2 */

/* Master interrupt controller:
 *  0 = Timer
 *  1 = Keyboard
 *  2 = Secondary (cascade)
 *  3 = Serial 1 ("COM2")
 *  4 = Serial 0 ("COM1")
 *  5 =
 *  6 = Floppy
 *  7 = Parallel
 *
 * Slave interrupt controller:
 *  0 (8) = RTC
 *  1 (9) =
 *  2 (10) =
 *  3 (11) =
 *  4 (12) =
 *  5 (13) =
 *  6 (14) = IDE0
 *  7 (15) =
*/
#define __DV_NUMINT		16

#define __DV_INTNUM_TIMER	0
#define __DV_INTNUM_KBD		1
#define __DV_INTNUM_TTY0	4
#define __DV_INTNUM_TTY1	3
#define __DV_INTNUM_FD		6
#define __DV_INTNUM_PAR		7
#define __DV_INTNUM_RTC		8
#define __DV_INTNUM_IDE0	14

/* The 8259 and 8253 are I/O-mapped
*/
#define __dv_i8259_read(base, offset)			__dv_in8(base+offset)
#define __dv_i8259_write(base, offset, val)		__dv_out8(base+offset, val)

#define __dv_i8253_read(base, offset)			__dv_in8(base+offset)
#define __dv_i8253_write(base, offset, val)		__dv_out8(base+offset, val)

#endif
