/*	arm-ctxtsw.s - __dv_ctxtsw
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

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif


/*==============================================================================
 *	__dv_ctxtsw - context switch, loads saved process registers
 *
 * On entry, parameter (address of register block) in r0
 *
 * Needs to:
 *   - set inKernel to 0
 *   - reset supervisor stack pointer to start
 *   - get process PC to r14_svc and process cpsr to spsr
 *   - load all user-mode registers r0-r14
 *==============================================================================
*/
	.text

	.global	__dv_ctxtsw

	.extern	__dv_in_kernel
	.extern	__dv_kernel_sp

__dv_ctxtsw:
	ldr		r5,=__dv_in_kernel
	mov		r6,#0
	strb	r6,[r5]					/* __dv_in_kernel = 1 */

	ldr		r7, [r0], #+4			/* Get PSR */
	ldr		r14, [r0], #+4			/* Get PC */

	ldr		r9,=__dv_kernel_sp		/* Prepare to reset kernel SP */

	msr		SPSR, r7				/* Put process PSR in SPSR ready for return from exeception */

	ldr		r13, [r9]				/* Reset kernel SP */
	
	ldmia	r0,{r0-r14}^			/* Restore user registers from process bank */
	movs	pc,r14					/* Return from exception */
