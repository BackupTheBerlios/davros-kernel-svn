/*	i8259.h - 8259 interrupt controller
 *
 *	Copyright 2002 David Haworth
 *
 *  This file is part of davros.
 *
 *  davros is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  davros is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with davros.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __i8259_h
#define __i8259_h

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*	This file contains definitions for the intel 8259 interrupt
 *	controller
 *
 *	We define the registers as offsets from a base address for two
 *	reasons:
 *		1 -	the device is often i/o mapped on x86 systems 
 *		2 -	the device registers are sometimes decoded at 16- or 32-bit
 *			intervals instead of the normal 8.
 *	There are really only 2 registers, but they do different things
 *	depending on what's in the data and what has been written
 *	before.
*/

#define i8259_icw1	0	/* D4 = 1 */
#define i8259_icw2	1	/* After ICW1 written */
#define i8259_icw3	1	/* After ICW2, if ICW1 bit 1 is 0 */
#define i8259_icw4	1	/* After ICW3, if ICW1 bit 0 is 1 */
#define i8259_ocw1	1	/* Interrupt mask */
#define i8259_ocw2	0	/* D4 = 0, D3 = 0 */
#define i8259_ocw3	0	/* D4 = 0, D3 = 1 */

#define I8259_ICW1		0x10	/* Selects ICW1 */
#define I8259_ICW1_A7	0x80	/* A7 (8085 mode) */
#define I8259_ICW1_A6	0x40	/* A6 (8085 mode) */
#define I8259_ICW1_A5	0x20	/* A5 (8085 mode) */
#define I8259_ICW1_LTIM	0x08	/* 1 = level trigger, 0 = edge trigger */
#define I8259_ICW1_ADI	0x04	/* Call address interval (8085) 0=8, 1=4 */
#define I8259_ICW1_SNGL	0x02	/* 0 = cascade (==>ICW3), 1 = single mode */
#define I8259_ICW1_IC4	0x01	/* 0 = no ICW4, 1 = ICW4 */

#define I8259_ICW2_BASE	0xf8	/* 8086 mode: base vector */
#define I8259_ICW2_A	0xff	/* 8085 mode: a15..a8 */

#define I8259_ICW3_M_S7	0x80	/* Master: input 7 has slave 8259 attached */
#define I8259_ICW3_M_S6	0x40	/* Master: input 6 has slave 8259 attached */
#define I8259_ICW3_M_S5	0x20	/* Master: input 5 has slave 8259 attached */
#define I8259_ICW3_M_S4	0x10	/* Master: input 4 has slave 8259 attached */
#define I8259_ICW3_M_S3	0x08	/* Master: input 3 has slave 8259 attached */
#define I8259_ICW3_M_S2	0x04	/* Master: input 2 has slave 8259 attached */
#define I8259_ICW3_M_S1	0x02	/* Master: input 1 has slave 8259 attached */
#define I8259_ICW3_M_S0	0x01	/* Master: input 0 has slave 8259 attached */

#define I8259_ICW3_S_ID	0x07	/* Slave: slave id (=master pin conn. to) */

#define I8259_ICW4_SFNM	0x10	/* Special fully nested mode */
#define I8259_ICW4_BUF	0x08	/* Buffered mode */
#define I8259_ICW4_MS	0x04	/* 0 = slave, 1 = master, if bufferd mode */
#define I8259_ICW4_AEOI	0x02	/* Automatic EOI mode */
#define I8259_ICW4_UPM	0x01	/* 0 = 8085 mode, 1 = 8086 mode */

#define I8259_OCW1_M7	0x80	/* Input 7: 0 = enabled, 1 = masked */
#define I8259_OCW1_M6	0x40	/* Input 6: 0 = enabled, 1 = masked */
#define I8259_OCW1_M5	0x20	/* Input 5: 0 = enabled, 1 = masked */
#define I8259_OCW1_M4	0x10	/* Input 4: 0 = enabled, 1 = masked */
#define I8259_OCW1_M3	0x08	/* Input 3: 0 = enabled, 1 = masked */
#define I8259_OCW1_M2	0x04	/* Input 2: 0 = enabled, 1 = masked */
#define I8259_OCW1_M1	0x02	/* Input 1: 0 = enabled, 1 = masked */
#define I8259_OCW1_M0	0x01	/* Input 0: 0 = enabled, 1 = masked */

#define I8259_OCW2				0x00	/* Selects OCW2 */
#define I8259_OCW2_CMD_NSEOI	0x20	/* Non-specific EOI */
#define I8259_OCW2_CMD_SEOI		0x60	/* Specific EOI */
#define I8259_OCW2_CMD_RNSEOI	0xa0	/* Rotate on non-specific EOI */
#define I8259_OCW2_CMD_RAEOIS	0x80	/* Rotate in AEOI mode (set) */
#define I8259_OCW2_CMD_RAEOIC	0x00	/* Rotate in AEOI mode (clear) */
#define I8259_OCW2_CMD_RSEOI	0xe0	/* Rotate on specific EOI */
#define I8259_OCW2_CMD_SETP		0xc0	/* Set priority */
#define I8259_OCW2_CMD_NOP		0x40	/* No operation */
#define I8259_OCW2_LEVEL		0x07	/* Level to operate on */

#define I8259_OCW3		0x08	/* Selects OCW3 */
#define I8259_OCW3_ESMM	0x40	/* Enable SMM bit */
#define I8259_OCW3_SMM	0x20	/* Special mask bit (only if ESMM=1) */
#define I8259_OCW3_P	0x04	/* Poll */
#define I8259_OCW3_RR	0x02	/* Enable RIS bit */
#define I8259_OCW3_RIS	0x01	/* 1 = read ISR next, 0 = read IRR next */

#ifdef __cplusplus
}
#endif

#endif
