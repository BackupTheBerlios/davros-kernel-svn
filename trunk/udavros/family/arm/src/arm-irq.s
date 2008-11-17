/*	arm-irq.s - __dv_irq
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
#include <davros/process.h>
#include <arm-core.h>

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

/*==============================================================================
 *	__dv_irq - this is the IRQ interrupt handler
 *
 * This routine is entered by a jump from the IRQ vector, which in
 * turn is invoked when an IRQ interrupt occurs.
 *
 * When an IRQ occurs the following things happen:
 *  - the PC is saved in r14_irq
 *  - the CPSR register is saved in SPSR_irq
 *  - the CPSR mode field is set to irq mode
 *  - the CPSR arm/thumb bit is set to 'arm'
 *  - IRQ is disabled
 *  - the SP is R13_irq, thus we automatically switched to interrupt stack
 *
 * We need to:
 *  - set the in-kernel flag (saving the old value)
 *  ( re-enable interrupts as they were before the irq )
 *  - call the irq dispatcher
 *  - on return, check if a context switch is needed. If not,
 *    restore old in-kernel and any saved registers and return.
 *  - if a context switch is needed, registers will need saving
 *    in the current task (if any) context, not forgetting the
 *    R13_usr and R14_usr registers.
 *
 * Register allocation:
 *	r0-r1  - before kernel function: parameters; afterwards: return value
 *  r2-r3  - before kernel function: parameters; afterwards: scratch
 *  r4     - nonvolatile: saved on stack; old __dv_in_kernel
 *  r5     - nonvolatile: saved on stack; address of __dv_in_kernel
 *  r6-r7  - nonvolatile: saved on stack; working registers
 *  r8-r11 - nonvolatile
 *  r12    - Intra-Procedure-call scratch register.
 *  r13    - (Irq) stack pointer
 *  r14    - Link register (return address; saved on stack)
 *  r15    - PC
 *==============================================================================
*/
	.global		__dv_irq
	.extern		__dv_dispatch_irq

#define	SF_r14	54
#define	SF_r12	48
#define	SF_r11	44
#define	SF_r10	40
#define	SF_r9	36
#define	SF_r8	32
#define	SF_r7	28
#define	SF_r6	24
#define	SF_r5	20
#define	SF_r4	16
#define	SF_r3	12
#define	SF_r2	8
#define	SF_r1	4
#define SF_r0	0

	.text

__dv_irq:

	sub		r14, r14, #4				/* Fix up the return address */

										/* FIXME: saves all registers for now */
	stmdb	sp!,{r0-r12,r14}			/* Save scratch & working registers on IRQ stack */

/* Set the in-kernel flag, saving original value. This is so that interrupts occurring
 * during the system call will not switch away from the current process.
 * There is no need to check the old value on exit because system calls are only necessary
 * in process contexts and can only be used there.
*/
	ldr		r5,=__dv_in_kernel			/* r5 = &__dv_in_kernel */
	mov		r0,#1
	ldrb	r4,[r5]						/* r4 = __dv_in_kernel */
	strb	r0,[r5]						/* __dv_in_kernel = 1 */

	ldr		r1, =__dv_dispatch_irq
	mov		r14,r15						/* Set return address (address of this instruction + 8) */
	bx		r1							/* Call the IRQ dispatcher */

	orrs	r4,r4,r4					/* test old inKernel */
	bne		__dv_irq_return

	ldr		r0,=__dv_schedule			/* Find out what should run */
	mov		r14,r15
	bx		r0

	ldr		r1,=__dv_currproc
	ldr		r3,[r1]						/* r6 = __dv_currproc */
	cmp		r0,r3
	beq		__dv_irq_return				/* Branch if no change in running process */

	cmp		r3,#0						/* Check for dead process */
	beq		__dv_irq_dispatch

	ldmia	sp!,{r6-r12}				/* Restore 7 saved registers r0..r6 into r6..r12*/
	add		r3,r3,#__DV_REGS			/* r3 = &__dv_current_proc->registers */
	add		r2,r3,#__DV_CTXT_r0			/* r2 = address of general-purpose regs */
	stmia	r2!,{r6-r12}				/* Store registers r0-r6 */
	ldmia	sp!,{r6-r11,r14}			/* Restore 7 saved registers r7..r12,r14 into r6..r11,r14 */
	stmia	r2,{r6-r11,r13-r14}^		/* Store registers r7-r12 and *user-mode* r13..r14 */
	mrs		r12,SPSR					/* Get CPSR of process */
	stmia	r3,{r12,r14}				/* Store CPSR and PC of process */

__dv_irq_dispatch:
	ldr		r3, =__dv_irq_sp			/* Reset IRQ stack pointer */
	ldr		sp, [r3]
	msr		cpsr_c, #(__DV_PSR_MODE_SVC+__DV_PSR_IRQ+__DV_PSR_FIQ)	/* Switch to supervisor */
	b		__dv_dispatch				/* Jump to dispatcher (never returns) */

__dv_irq_return:
	strb	r4,[r5]						/* __dv_in_kernel = r4 (should be zero) */
	ldmia	sp!, {r0-r12,r14}			/* Restore saved regs */
	movs	pc,r14						/* Return from exception */

