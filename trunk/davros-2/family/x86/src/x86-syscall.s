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

/*	__dv_syscall - system call handler for x86 family processors
 *
 * The address of this routine is loaded into MSR 0x176 at startup. This means
 * that a SYSENTER instruction will cause a jump here.
 *
 * When SYSENTER is executed the following things happen:
 *  MSR 0x174 is copied to %cs
 *  MSR 0x175 is copied to %esp
 *  MSR 0x176 is copied to %eip
 *  The system is switched to privileged mode and interrupts are disabled.
 *
 * Thus the processor will continue executing at __dv_syscall in privileged mode
 * on the kernel stack.
 *
 * Note that no registers are saved. This means that in order to work properly, the
 * system-call stub function must load the following registers:
 *
 *  %esi   - system-call index
 *  %ebp   - stack pointer - points at return address
 *  %eax   - first parameter (if present)
 *  %ebx   - second parameter (if present)
 *  %ecx   - third parameter (if present)
 *  %edx   - fourth parameter (if present)
 *
 * We need to:
 *  - reserve a stack frame
 *  - save the context (pc/sp in edi/ebp) in the stack frame
 *  - store the parameters into the stack frame where expected by the kernel function
 *  - set the in-kernel flag (saving the old value in the stack frame)
 *  - re-enable interrupts as they were before the SYSENTER
 *  - use the system-call index to get the address of the function to call.
 *  - call the function and ensure that the return value is not destroyed
 *  - on return, check if a context switch is needed. If not,
 *    restore old in-kernel and any saved registers and return, leaving
 *    the return value from the sys.function intact.
 *  - if a context switch is needed, registers will need saving
 *    in the current task (if any) context.
 *  - to return, a "jump" to __dv_usr_return, which is essentially the "return" from
 *    the assembler stub. If the process is non-trusted, this is achieved by a SYSEXIT.
 *    For a trusted process we just restore the stack pointer and jump there.
*/
	.text

	.global	__dv_syscall

	.extern	__dv_in_kernel
	.extern	__dv_syscall_table
	.extern	__dv_usr_return_from_syscall

#define __DV_SYSCALL_EAX		0		/* Param 0 */
#define __DV_SYSCALL_EBX		4		/* Param 1 */
#define __DV_SYSCALL_ECX		8		/* Param 2 */
#define __DV_SYSCALL_EDX		12		/* Param 3 */
#define __DV_SYSCALL_OIK		16
#define __DV_SYSCALL_ESI		20		/* System-call index */
#define __DV_SYSCALL_ESP		24		/* Process stack pointer */

__dv_syscall:
	sub		$__DV_SYSCALL_FRAME,%esp		/* Reserve stack frame */

	mov		%eax,$__DV_SYSCALL_EAX(%esp)	/* Save parameters */
	mov		%ebx,$__DV_SYSCALL_EBX(%esp)
	mov		%ecx,$__DV_SYSCALL_ECX(%esp)
	mov		%edx,$__DV_SYSCALL_EDX(%esp)

	mov		%ebp,$__DV_SYSCALL_ESP(%esp)	/* Save caller's stack pointer */

	mov		__dv_in_kernel,%al				/* Save in_kernel flag and set to 1 */
	mov		%eax,$__DV_SYSCALL_OIK(%esp)
	mov		$1,__dv_in_kernel

	cli										/* Enable interrupts */

	mov		$__dv_unknowncall,%eax			/* Preload unknown syscall handler */
	cmpl	$(__DV_N_SYSCALLS-1),%esi		/* Check range of syscall index */
	ja		.range							/* Jump if out -of-range */

	mov		__dv_syscall_table(,%esi,4),%eax	/* Load syscall func from table at index */

.range:
	call	*%eax							/* Call the function */

	mov		%eax,$__DV_SYSCALL_RETVAL(%esp)	/* Save the return value */

	sei										/* Disable interrupts */

	call	__dv_schedule					/* Find out what should run */

	cmpl	%eax,__dv_currproc
	jeq		__dv_syscall_return				/* Jump if no change in running process */

	cmpl	$0,__dv_currproc				/* Check for dead process */
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
