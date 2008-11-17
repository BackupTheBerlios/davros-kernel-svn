/*	arm-core.h - definitions for the arm processor core
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

#ifndef __dv_arm_core_h
#define __dv_arm_core_h

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

/* Bits, fields and values in the processor status registers CPSR and SPSR_xxx
*/

/* The follwing fields are in the _c portion of the register
*/
#define	__DV_PSR_MODE		0x1f
#define	__DV_PSR_MODE_USR	0x10	/* User mode (non-privileged processes) */
#define	__DV_PSR_MODE_SYS	0x1f	/* System mode (privileged processes) */
#define	__DV_PSR_MODE_SVC	0x13	/* Supervisor (SWI trap) */
#define	__DV_PSR_MODE_IRQ	0x12	/* IRQ trap */
#define	__DV_PSR_MODE_FIQ	0x11	/* FIQ trap */
#define	__DV_PSR_MODE_ABT	0x17	/* Data abort trap */
#define	__DV_PSR_MODE_UND	0x1b	/* Undefined opcode trap */

#define __DV_PSR_THUMB		0x20	/* 1 == Processor is in thumb mode */

#define __DV_PSR_FIQ		0x40	/* 1 == FIQ is disabled */
#define __DV_PSR_IRQ		0x80	/* 1 == IRQ is disabled */

#define __DV_PSR_FIQ_IRQ	(__DV_PSR_FIQ+__DV_PSR_IRQ)		/* Both bits */

#define __dv_get_cpsr() \
	({	register __dv_uint32_t __dv_get_cpsr_tmp;						\
		__asm__ volatile ( " mrs %0,cpsr" : "=r" (__dv_get_cpsr_tmp) );	\
		__dv_get_cpsr_tmp;												\
	})

#define __dv_set_cpsr(val) \
	({	register __dv_uint32_t __dv_set_cpsr_tmp = (val);					\
		__asm__ volatile ( " msr cpsr,%0" : : "r" (__dv_set_cpsr_tmp) );	\
	})

#endif
