/*	x86-syscall.s - __dv_syscall
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
#include <davros/config.h>
#include <x86-asm.h>
#include <x86-core.h>
#include <davros/syscall.h>
#include <davros/process.h>

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

/*==============================================================================
 *	__dv_syscall - system call handler for x86 family processors
 *
 * This routine is entered by a jump from the SWI vector, which in
 * turn is invoked using the SWI instruction. The instruction
 * itself contains more information about the type of system call.
 * We therefore need to retrieve it.
 *
 * When SWI is executed the following things happen:
 *  - the PC is saved in r14_svc
 *  - the CPSR register is saved in SPSR_svc
 *  - the CPSR mode field is set to supervisor (svc) mode
 *  - the CPSR arm/thumb bit is set to 'arm'
 *  - IRQ is disabled
 *  - the SP is R13_svc, thus we automatically switched to kernel stack
 * Davros will be capable of accepting system calls from
 * system and user mode but not from any other mode.
 *
 * On entry the following conditions will be true:
 *  - up to 4 parameters will be passed in registers r0 to r3.
 *
 * We need to:
 *  - set the in-kernel flag (saving the old value)
 *  - re-enable interrupts as they were before the syscall
 *  - extract the system-call index from the instruction
 *  - use the system-call index to get the address of the function
 *    to call, preserving the parameter registers.
 *  - call the function and ensure that the return value is not destroyed
 *  - on return, check if a context switch is needed. If not,
 *    restore old in-kernel and any saved registers and return, leaving
 *    the return value from the sys.function intact.
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
 *  r13    - (Kernel) stack pointer
 *  r14    - Link register (return address; saved on stack)
 *  r15    - PC
 *==============================================================================
*/
	.text

	.global	__dv_syscall

	.extern	__dv_in_kernel
	.extern	__dv_syscall_table

__dv_syscall:
#if 0
	stmdb	r13!,{r4-r7,r14}		/* Push r4-r7 and return address on stack */

#if __DV_CHECK_UNIMPLEMENTED
#error "Not implemented: ensure caller was in sys or usr mode"
#endif

/* Set the in-kernel flag, saving original value. This is so that interrupts occurring
 * during the system call will not switch away from the current process.
 * There is no need to check the old value on exit because system calls are only necessary
 * in process contexts and can only be used there.
*/
	ldr		r5,=__dv_in_kernel		/* r5 = &__dv_in_kernel */
	mov		r6,#1
	ldrb	r4,[r5]					/* r4 = __dv_in_kernel */
	strb	r6,[r5]					/* __dv_in_kernel = 1 */

/* Re-enable interrupts as they were before the syscall
*/
#if 0
	mrs		r7,SPSR
	and		r7,#__DV_PSR_FIQ_IRQ	/* Isolate FIQ and IRQ mask bits in spsr value */
	orr		r7,#__DV_PSR_MODE_SVC	/* ARM & SVC modes */
	msr		CPSR_c,r7				/* Write new value back to cpsr */
#endif

/* Get the 24-bit operand from the SWI instruction
*/
	ldr		r7,=0xffffff			/* 24 bits */
	ldr		r6,[r14,#-4]			/* Get SWI instruction - SYSCALL index is embedded in it */
	and		r6,r6,r7				/* Isolate bottom 24 bits */

#if __DV_CHECK_UNIMPLEMENTED
#error "Not implemented: ensure SWI operand is in range"
#endif

	ldr		r7,=__dv_syscall_table
	ldr		r7,[r7,+r6,lsl #2]		/* Load system call address from table */
	mov		r14,r15					/* Set return address (address of this instruction + 8) */
	bx		r7						/* Call selected system call */

#if 0
	mrs		r7,CPSR					/* Disable IRQ, leave FIQ as it was before the call. */
	orr		r7,#__DV_PSR_IRQ
	msr		CPSR_c,r7
#endif

	stmdb	r13!,{r0-r1}			/* Push return value(s) onto stack */

	ldr		r7,=__dv_schedule		/* Find out what should run */
	mov		r14,r15
	bx		r7

	ldr		r7,=__dv_currproc
	ldr		r3,[r7]					/* r6 = __dv_currproc */
	cmp		r0,r3
	beq		__dv_syscall_return		/* Branch if no change in running process */

	ldmia	r13!,{r0-r1,r4-r7,r14}	/* Restore saved registers */
	cmp		r3,#0					/* Check for dead process */
	beq		__dv_syscall_dispatch

	add		r3,r3,#__DV_REGS		/* r3 = &__dv_current_proc->registers */
	add		r2,r3,#8				/* r2 = address of general-purpose regs */
	stmia	r2,{r0-r14}^			/* Store all user-mode registers */
	mrs		r12,SPSR				/* Get CPSR of process */
	stmia	r3,{r12,r14}			/* Store CPSR and PC of process */

__dv_syscall_dispatch:
	b		__dv_dispatch			/* Jump to scheduler (never returns) */

__dv_syscall_return:
	strb	r4,[r5]					/* __dv_in_kernel = r4 (should be zero) */
	ldmia	r13!,{r0-r1,r4-r7,r14}	/* Restore saved registers */
	movs	pc,r14					/* Return from exception */
#endif
