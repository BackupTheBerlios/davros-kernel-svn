/*	msp430-core.h - MSP430 CPU core description
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
 *	This file contains definitions for the MSP430 CPU core.
 *
 *	$Log: msp430-core.h,v $
 *	Revision 1.1  2004/05/11 20:45:56  dave
 *	Files for new msp430 port.
 *	
*/

#if !defined(__msp430_core_h)
#define __msp430_core_h

#ifdef __cplusplus
extern "C" {
#endif

/* Bits in the status register.
*/
#define SR_GC		0x0001
#define SR_Z		0x0002
#define SR_N		0x0004		
#define SR_GIE		0x0008		/* Interrupt enable */
#define SR_CPUOFF	0x0010
#define SR_OSCOFF	0x0020
#define SR_SCG		0x00c0
#define SR_V		0x0100

#ifdef __ASSEMBLER__

/* "Special" registers
*/
#define PC		r0
#define SP		r1
#define	SR		r2
#define ZERO	r3

#else

/*
 *	Function prototypes. Some functions are in msp430-core.c,
 *	the others are in msp430-core-asm.s
*/

uint16_t disable_interrupts(void);
uint16_t enable_interrupts(void);
uint16_t restore_interrupts(uint16_t old);

#endif

#ifdef __cplusplus
}
#endif

#endif
