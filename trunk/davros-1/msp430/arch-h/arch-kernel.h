/*	arch-kernel.h - MSP430-specifics for Davros kernel
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
 *	This file defines msp430-specific data types for davros.
 *	msp430 is 16-bit with limited resources, so we override
 *	a lot of the default 32-bit definitions.
 *
 *	$Log: arch-kernel.h,v $
 *	Revision 1.1  2004/05/11 20:45:55  dave
 *	Files for new msp430 port.
 *	
*/

#if !defined(__arch_kernel_h)
#define __arch_kernel_h

#include "arch-cpudef.h"
#include "msp430-core.h"
#include "kernel-config.h"

#ifdef __cplusplus
extern "C" {
#endif

#define __DAVROS_MAXINT  0x7fff
#define __DAVROS_MININT  0x8000

#if defined(__ASSEMBLER__)

/*	Offsets of registers in __msp_context struct. For use in assembler.
*/
#define __MSP_CTXT_SP		0

#else

typedef uint16_t __arch_intstatus_t;

/*	When a task is removed from the CPU, the registers are saved
 *	into this structure.
 *	Only the SP is saved - the rest are pushed.
*/
typedef struct __msp_context
{
	unsigned sp;
} __msp_context_t;

typedef __msp_context_t __arch_ctxtreg_t;

/* Define these values as 16-bit values for the msp430
*/
typedef int16_t __davros_qkey_t;
#define __DAVROS_QKEY_T
typedef int16_t __davros_semcount_t;
#define __DAVROS_SEMCOUNT_T
typedef int16_t __davros_msg_t;
#define __DAVROS_MSG_T
typedef int16_t __davros_status_t;
#define __DAVROS_STATUS_T
typedef uint16_t __davros_frc_t;
#define __DAVROS_FRC_T

/* Architecture-specific kernel data. */
#if 0	/* FIXME */
#define	__ARCH_KERNEL_DATA	uint32_t __arch_dflt_status
#endif

#endif

/*	There's only a single global interrupt enable bit.
*/
#define __arch_enableinterrupts enable_interrupts
#define __arch_disableinterrupts disable_interrupts
#define __arch_restoreinterrupts restore_interrupts
#define __arch_enterkernel disable_interrupts

#ifdef __cplusplus
}
#endif

#endif
