/*	msp430.h - MSP430 CPU and board variants
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
 *	This file contains definitions for the core, microcontroller and
 *	board variants of msp430.
 *
 *	$Log: msp430.h,v $
 *	Revision 1.1  2004/05/11 20:45:56  dave
 *	Files for new msp430 port.
 *	
*/

#if !defined(__msp430_h)
#define __msp430_h

/* MSP430 microcontroller parts. MSP_CPU should be one of these.
 *
 * No real need for board definitions, because there's no external
 * bus on the msp430.
*/
#define MSP430X149		1	/* 64-pin */

#if MSP_CPU==MSP430X149
#define RAM_START	0x0200
#define RAM_SIZE	0x0800

#if 1
#if !defined(__ASSEMBLER__)
#include <msp430x14x.h>		/* From gcc */
#endif
#else
#define TIMERA0_VECTOR 12
#endif

#endif

#endif
