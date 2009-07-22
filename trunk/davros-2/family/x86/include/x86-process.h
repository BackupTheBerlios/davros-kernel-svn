/*	x86-process.h - process context on the x86 family
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

#ifndef __dv_x86_process_h
#define __dv_x86_process_h

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

#define __DV_PROCESSREGISTERS_T	struct __dv_processregisters_s

#define __DV_REG_eax	0
#define __DV_REG_ebx	1
#define __DV_REG_ecx	2
#define __DV_REG_edx	3
#define __DV_REG_ebp	4
#define __DV_REG_esi	5
#define __DV_REG_edi	6
#define __DV_REG_esp	7
#define __DV_X86_NREGS	8

#ifndef __DV_ASM
struct __dv_processregisters_s
{
	__dv_uint32_t	regs[__DV_X86_NREGS];
};
#endif

/* These are the BYTE OFFSETS of the registers, for use in assembler functions.
*/
#define __DV_CTXT_eax	0
#define __DV_CTXT_ebx	4
#define __DV_CTXT_ecx	8
#define __DV_CTXT_edx	12
#define __DV_CTXT_ebp	16
#define __DV_CTXT_esi	20
#define __DV_CTXT_edi	24
#define __DV_CTXT_esp	28

#endif
