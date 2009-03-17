/*	tricore-mod.h - Tricore module description
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
 *	This file contains a description of the common module interface used
 *	by many Tricore peripheral modules such as ASC, GPTU, etc.
 *	Also included is a description of the interrupt service request
 *	registers that are also commonly used.
 *
*/

#if !defined(__tricore_mod_h)
#define __tricore_mod_h

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(__ASSEMBLER__)

/*	Common module header. Most of the peripheral modules on Tricore
 *	contain one of these, and the module needs initialisation before
 *	the device can be used. We can use common code for this.
*/

typedef struct tricore_mod
{
	volatile uint32_t	clc;		/* Clock control register */
	volatile uint32_t	reserved;	/* Some modules use this! */
	volatile uint32_t	id;		/* Module identification register */
} tricore_mod_t;

#endif

/* Bit definitions for CLC */
#define CLC_RMC		0x0000ff00		/* Clock divider (Rate mode control?) */
#define CLC_FSOE	0x00000020		/* Fast shut-off enable */
#define CLC_SBWE	0x00000010		/* Suspend bit write enable */
#define CLC_EDIS	0x00000008		/* External request disable */
#define CLC_SUSPEN	0x00000004		/* Suspend enable bit */
#define CLC_DISS	0x00000002		/* Disable status bit */
#define CLC_DISR	0x00000001		/* Disable request bit */

/* Bit definitions for ID */
#define ID_MOD		0xffff0000		/* Module identification number */
#define ID_MOD16	0x0000ff00		/* Module id (used to be 16-bit register) */
#define ID_MOD32B	0x0000c000		/* Indicates 32-bit register */
#define ID_REV		0xffff0000		/* Module revision number */


/*	Move an integer value to the appropriate field. */
#define CLC_RMCval(div)	((div) << 8)

/*	Extract the module ident (shifted to LSB) using appropriate field,
 *	taking account of 16/32 bit register types.
*/
#define module_id(v)	( (((v)&ID_MOD16)==ID_MOD32B)	? ((v)>>16) \
														: (((v)>>8)&0xff) )
#if !defined(__ASSEMBLER__)

/*	Interrupt service request node. All generation of interrupts on
 *	Tricore is done through one of these ISR registers. We can use
 *	common code to program the priority, enable/disable, etc.
*/

typedef volatile unsigned long tricore_isr_t;

#endif

/* Bit fields in the ISR */
#define ISR_SETR	0x00008000	/* Request set bit */
#define ISR_CLRR	0x00004000	/* Request clear bit */
#define ISR_SRR		0x00002000	/* Service request bit */
#define ISR_SRE		0x00001000	/* Service request enable */
#define ISR_TOS		0x00000c00	/* Type of service */
#define ISR_TOS_CPU	ISR_TOSval(0)	/* Interrupt the CPU */
#define	ISR_SRPN	0x000000ff	/* Priority */

#define ISR_TOSval(tos)	((tos)<<10)

#ifdef __cplusplus
}
#endif

#endif
