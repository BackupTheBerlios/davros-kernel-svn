/*	arm-startup.s - __dv_arm_startup
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
#include <davros/config.h>
#include <arm-asm.h>
#include <arm-core.h>
#include <davros/process.h>

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

/*==============================================================================
 *	__dv_arm_startup - assembler startup code for arm family processors
 *==============================================================================
*/
	.global	__dv_arm_startup
	.extern	__dv_C_startup
	.extern	__dv_startup
	.extern __dv_kernel_sp
	.extern __dv_irq_sp

	.extern	__dv_exception_vectors		/* Force existence of vector table */

	.text

__dv_arm_startup:

/* Enter irq mode, disable IRQ and FIQ.
 * Then set the irq stack pointer
*/
	msr		cpsr_c, #(__DV_PSR_MODE_IRQ+__DV_PSR_IRQ+__DV_PSR_FIQ)
	ldr		r3, =__dv_irq_sp
	add		r3, r3, #0x400
	mov		sp, r3

/* Enter supervisor mode, disable IRQ and FIQ.
 * Then set the supervisor (kernel) stack pointer
*/
	msr		cpsr_c, #(__DV_PSR_MODE_SVC+__DV_PSR_IRQ+__DV_PSR_FIQ)
	ldr		r3, =__dv_kernel_sp
	ldr		sp, [r3]

/* Enter system mode, disable IRQ and FIQ.
 * Then set the system/user stack pointer
*/
	msr		cpsr_c, #(__DV_PSR_MODE_SYS+__DV_PSR_IRQ+__DV_PSR_FIQ)
	ldr		r3, =__dv_irq_sp
	ldr		sp, [r3]

/* call __dv_C_startup
*/
	ldr		lr, =__dv_return_1
	ldr		r0, =__dv_C_startup
	bx		r0
__dv_return_1:

/* call __dv_startup
 *
 * If __dv_startup returns, go round again (return address is preset)
*/
	ldr		lr, =__dv_arm_startup
	ldr		r0, =__dv_startup
	bx		r0
