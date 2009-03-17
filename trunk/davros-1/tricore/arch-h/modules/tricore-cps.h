/*	tricore-cps.h - Tricore CPS description
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
 *	This file contains a description of Tricore's CPU-Slave interface
 *	module (CPS).
*/

#if !defined(__tricore_cps_h)
#define __tricore_cps_h

#ifdef __cplusplus
extern "C" {
#endif

#include "modules/tricore-mod.h"

#if !defined(__ASSEMBLER__)

typedef struct tricore_cps
{
	tricore_mod_t		cps_hdr;			/* See note below */
	volatile uint32_t	reserved2[44];
	tricore_isr_t		cps_srcsb;			/* Software break ISR */
	volatile uint32_t	reserved3[12];
	tricore_isr_t		cps_src3;			/* CPU ISR 3 */
	tricore_isr_t		cps_src2;			/* CPU ISR 2 */
	tricore_isr_t		cps_src1;			/* CPU ISR 1 */
	tricore_isr_t		cps_src0;			/* CPU ISR 0 */
} tricore_cps_t;

/*	Module header note: In the CPS, the module clc register isn't
 *	implemented, and the id register contains the CPU identification.
*/

#endif

#ifdef __cplusplus
}
#endif

#endif
