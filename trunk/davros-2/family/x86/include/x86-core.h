/*	x86-core.h - definitions for the x86 processor core
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

#ifndef __dv_x86_core_h
#define __dv_x86_core_h

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

/* Bits, fields in the EFLAGS register
*/
#define FLAG_ID		0x00200000		/* Identification */
#define FLAG_VIP	0x00100000		/* Virtual interrupt pending */
#define FLAG_VIF	0x00080000		/* Virtual interrupt enable */
#define FLAG_AC		0x00040000		/* Alignment check */
#define FLAG_VM		0x00020000		/* Virtual 8086 mode */
#define FLAG_RF		0x00010000		/* Resume flag */
#define FLAG_NT		0x00004000		/* Nested task */
#define FLAG_IOPL	0x00003000		/* I/O privelege level */
#define FLAG_OF		0x00000800		/* Overflow ??? */
#define FLAG_DF		0x00000400		/* ??? */
#define FLAG_IF		0x00000200		/* Interrupt flag */
#define FLAG_TF		0x00000100		/* Trace flag */
#define FLAG_SF		0x00000080		/* Sign flag ??? */
#define FLAG_ZF		0x00000040		/* Zero flag */
#define FLAG_AF		0x00000010		/* ??? */
#define FLAG_PF		0x00000004		/* ??? */
#define FLAG_CF		0x00000001		/* Carry flag ??? */
#define FLAG_1		0x00000002		/* These bits must be 1 */

/* Descriptor Table definitions
*/
#define DT0_LIMIT			0x0000ffff
#define DT0_BASE			0xffff0000
#define DT1_BASE_HI			0xff000000
#define DT1_G				0x00800000	/* Granularity 0=byte, 1=4k */
#define DT1_DB				0x00400000
#define DT1_AVL				0x00100000
#define DT1_LIMIT			0x000f0000
#define DT1_P				0x00008000	/* Present */
#define DT1_DPL				0x00006000	/* Descriptor privelege level */
#define DT1_S				0x00001000	/* System segment (1=>code or data) */
#define DT1_TYPE			0x00000f00
#define DT1_TYPE_C			0x00000800	/* Code segment */
#define DT1_TYPE_C_C		0x00000400	/* Code - Conforming */
#define DT1_TYPE_C_R		0x00000200	/* Code - Readable */
#define DT1_TYPE_D			0x00000000	/* Data segment */
#define DT1_TYPE_D_E		0x00000400	/* Data - Expand-down */
#define DT1_TYPE_D_W		0x00000200	/* Data - Writable */
#define DT1_TYPE_A			0x00000100	/* Code & Data - Accessed */
#define DT1_BASE_LO			0x000000ff

#define DT1_TYPE_CR			(DT1_TYPE_C|DT1_TYPE_C_R)
#define DT1_TYPE_CCR		(DT1_TYPE_C|DT1_TYPE_C_C|DT1_TYPE_C_R)
#define DT1_TYPE_DW			(DT1_TYPE_D|DT1_TYPE_D_W)

/* Gate descriptor */
#define GD0_SEG				0xffff0000
#define GD0_OFFSET_LO		0x0000ffff	/* (Not for task gates) */
#define GD1_OFFSET_HI		0xffff0000	/* (Not for task gates) */
#define GD1_P				0x00008000	/* Present */
#define GD1_DPL				0x00006000	/* Descriptor privlege level */
#define GD1_D				0x00000800	/* Size: 1=32bit, 0=16 (not task gates) */
#define GD1_TYPE			0x00000700
#define GD1_TYPE_TASK		0x00000500
#define GD1_TYPE_INT		0x00000600
#define GD1_TYPE_TRAP		0x00000700

#ifndef __DV_ASM
/* Input/output operations
*/
__dv_uint32_t __dv_in8(__dv_uint32_t);
__dv_uint32_t __dv_in16(__dv_uint32_t);
__dv_uint32_t __dv_in32(__dv_uint32_t);
void __dv_out8(__dv_uint32_t, __dv_uint32_t);
void __dv_out16(__dv_uint32_t, __dv_uint32_t);
void __dv_out32(__dv_uint32_t, __dv_uint32_t);
#endif

#endif
