/*	x86-core.h - x86 CPU core description
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
 *	This file contains definitions for the x86 CPU core.
 *
 *	The x86 interrupt vector tabl is a table of addresses of
 *	handler functions - a true vector table. There are 32
 *	reserved vectors for CPU traps, plus up to 192 user-defined
 *	vectors. The kernel parameter __DAVROS_NVECTORS (0..224)
 *	defines how many user vectors we want.
 *	Each vector must point to a special interrupt handler routine
 *	that saves all the registers it uses on the stack on entry and
 *	restores them all before exiting with an iret instruction.
 *	For the 32 reserved vectors we define 32 entry stubs, each of
 *	which saves eax and then loads eax with the trap number
 *	before jumping to a common exception handler to do the
 *	rest.
 *	For the user vectors, we define __DAVROS_NHANDLERS stub
 *	handlers. Each one pushes eax before calling the common
 *	handler. Immediately after the call there are 3 data
 *	fields: the interrupt number (16-bit), the address of
 *	the C handler (32-bit) and a parameter for the C handler
 *	(also 32-bit). Thus the value pushed onto the stack by the
 *	call instruction is the address of these parameter fields,
 *	and is never used as a return address.
 *	One of these stub routines is used for each interrupt that
 *	is in use. They are allocated from the first, in order of
 *	attachment, by the function attach_interrupt.
 *	Unused interrupt vectors point to a special trap routine (trap
 *	0xff)
*/

#if !defined(__x86_core_h)
#define __x86_core_h

#include "arch-cpudef.h"

#ifdef __cplusplus
extern "C" {
#endif

/* EFLAGS register */
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

/* Descriptor Table */
#define DT0_LIMIT		0x0000ffff
#define DT0_BASE		0xffff0000
#define DT1_BASE_HI		0xff000000
#define DT1_G			0x00800000	/* Granularity 0=byte, 1=4k */
#define DT1_DB			0x00400000
#define DT1_AVL			0x00100000
#define DT1_LIMIT		0x000f0000
#define DT1_P			0x00008000	/* Present */
#define DT1_DPL			0x00006000	/* Descriptor privelege level */
#define DT1_S			0x00001000	/* System segment (1=>code or data) */
#define DT1_TYPE		0x00000f00
#define DT1_TYPE_C		0x00000800	/* Code segment */
#define DT1_TYPE_C_C	0x00000400	/* Code - Conforming */
#define DT1_TYPE_C_R	0x00000200	/* Code - Readable */
#define DT1_TYPE_D		0x00000000	/* Data segment */
#define DT1_TYPE_D_E	0x00000400	/* Data - Expand-down */
#define DT1_TYPE_D_W	0x00000200	/* Data - Writable */
#define DT1_TYPE_A		0x00000100	/* Code & Data - Accessed */
#define DT1_BASE_LO		0x000000ff

#define DT1_TYPE_CR		(DT1_TYPE_C|DT1_TYPE_C_R)
#define DT1_TYPE_CCR	(DT1_TYPE_C|DT1_TYPE_C_C|DT1_TYPE_C_R)
#define DT1_TYPE_DW		(DT1_TYPE_D|DT1_TYPE_D_W)

/* Gate descriptor */
#define GD0_SEG			0xffff0000
#define GD0_OFFSET_LO	0x0000ffff	/* (Not for task gates) */
#define GD1_OFFSET_HI	0xffff0000	/* (Not for task gates) */
#define GD1_P			0x00008000	/* Present */
#define GD1_DPL			0x00006000	/* Descriptor privlege level */
#define GD1_D			0x00000800	/* Size: 1=32bit, 0=16 (not task gates) */
#define	GD1_TYPE		0x00000700
#define GD1_TYPE_TASK	0x00000500
#define GD1_TYPE_INT	0x00000600
#define GD1_TYPE_TRAP	0x00000700



#ifdef __ASSEMBLER__
#else

typedef struct interrupt_vector
{
	uint32_t gd0;
	uint32_t gd1;
} interrupt_vector_t;

#define getstub(v)		\
	(((v)->gd0 & GD0_OFFSET_LO) | ((v)->gd1 & GD1_OFFSET_HI))
#define setstub(v,s)	\
	do	\
	{	(v)->gd0 = ((v)->gd0 & ~GD0_OFFSET_LO) | ((s) & GD0_OFFSET_LO);	\
		(v)->gd1 = ((v)->gd1 & ~GD1_OFFSET_HI) | ((s) & GD1_OFFSET_HI);	\
	} while (0)

typedef struct
{
	uint8_t push;		/*	1 - push %eax */
	uint8_t call[5];	/*	5 - call interrupt_handler */
	uint16_t inum;		/*	2 -	.word 0 */
	uint32_t handler;	/*	4 - .long 0 */
	uint32_t param;		/*	4 - .long 0 */
} interrupt_stub_t;

extern interrupt_stub_t handler_table[];
extern void __davros_trap_00(void);
extern void __davros_trap_01(void);
extern void __davros_trap_unknown(void);

/*
 *	Function prototypes. Some functions are in x86-core.c,
 *	the others are in x86-core-asm.s
*/

uint32_t disable_interrupts(void);
uint32_t enable_interrupts(void);
uint32_t restore_interrupts(uint32_t old);
void init_interrupt(void);

void out8(memaddr_t port, uint32_t val);
void out16(memaddr_t port, uint32_t val);
void out32(memaddr_t port, uint32_t val);
uint32_t in8(memaddr_t port);
uint32_t in16(memaddr_t port);
uint32_t in32(memaddr_t port);

void load_idt(void *idt);

#endif

#ifdef __cplusplus
}
#endif

#endif
