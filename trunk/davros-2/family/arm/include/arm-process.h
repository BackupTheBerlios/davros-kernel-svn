/*	arm-process.h - process context on the arm family
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

#ifndef __dv_arm_process_h
#define __dv_arm_process_h

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

#define __DV_PROCESSREGISTERS_T	struct __dv_processregisters_s

#define __DV_REG_psr	0
#define __DV_REG_r15	1
#define __DV_REG_r0		2
#define __DV_REG_r1		3
#define __DV_REG_r2		4
#define __DV_REG_r3		5
#define __DV_REG_r4		6
#define __DV_REG_r5		7
#define __DV_REG_r6		8
#define __DV_REG_r7		9
#define __DV_REG_r8		10
#define __DV_REG_r9		11
#define __DV_REG_r10	12
#define __DV_REG_r11	13
#define __DV_REG_r12	14
#define __DV_REG_r13	15
#define __DV_REG_r14	16
#define __DV_ARM_NREGS	17	/* psr, r15, r0-r14 */

#ifndef __DV_ASM
struct __dv_processregisters_s
{
	__dv_uint32_t	regs[__DV_ARM_NREGS];
};
#endif

/* These are the BYTE OFFSETS of the registers, for use in assembler functions.
*/
#define __DV_CTXT_psr	0
#define __DV_CTXT_r15	4
#define __DV_CTXT_r0	8
#define __DV_CTXT_r1	12
#define __DV_CTXT_r2	16
#define __DV_CTXT_r3	20
#define __DV_CTXT_r4	24
#define __DV_CTXT_r5	28
#define __DV_CTXT_r6	32
#define __DV_CTXT_r7	36
#define __DV_CTXT_r8	40
#define __DV_CTXT_r9	44
#define __DV_CTXT_r10	48
#define __DV_CTXT_r11	52
#define __DV_CTXT_r12	56
#define __DV_CTXT_r13	60
#define __DV_CTXT_r14	64

#endif
