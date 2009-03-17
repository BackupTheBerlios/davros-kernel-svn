/*	arch-kernel.h - X86-specifics for Davros kernel
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
*/

#if !defined(__arch_kernel_h)
#define __arch_kernel_h

#include "arch-cpudef.h"
#include "x86-core.h"
#include "kernel-config.h"

#ifdef __cplusplus
extern "C" {
#endif


/* We don't need to reserve a stack for NULL, because we don't
 * switch to it in __arch_setstack().
*/
#define __DAVROS_NULLSTACK	0

#if defined(__ASSEMBLER__)

/*	Offsets of registers in __x86_context struct. For use in assembler.
*/
#define __X86_CTXT_ESP		0x00

#else

typedef uint32_t __arch_intstatus_t;

/*	When a task is removed from the CPU, the registers are saved
 *	into this structure.
 *	FIXME: more to add, eventually!
*/
typedef struct __x86_context
{
	unsigned esp;
} __x86_context_t;

typedef __x86_context_t __arch_ctxtreg_t;

/* Architecture-specific kernel data. */
#if 0	/* FIXME */
#define	__ARCH_KERNEL_DATA	uint32_t __arch_dflt_status
#endif

/* An assembler function that calls exit when a process returns */
extern void __arch_exit(void);

/* What's on the stack when we call the exception handler.
 * These get pushed by the exception handler. See vectors.s
*/
typedef struct esf
{
	uint32_t edi;
	uint32_t esi;
	uint32_t ebp;
	uint32_t edx;
	uint32_t ecx;
	uint32_t ebx;
	uint32_t eax;
	uint32_t flags;
	uint32_t pc;
} esf_t;

#endif

/*	FIXME: this will do for now. Eventually we want to raise the
 *	CPU priority to a (programmable) level to allow interrupts
 *	outside the kernel to continue.
 *	Furthermore, we need to consider if the kernel is running with
 *	interrupts enabled. In this case, arch_enterkernel and
 *	arch_leavekernel will be different.
*/
#define __arch_enableinterrupts enable_interrupts
#define __arch_disableinterrupts disable_interrupts
#define __arch_restoreinterrupts restore_interrupts
#define __arch_enterkernel disable_interrupts

#ifdef __cplusplus
}
#endif

#endif
