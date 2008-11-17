/*	arm-vectors.s - arm vector table
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

	.global	__dv_exception_vectors
	.extern __dv_arm_startup
	.extern	__dv_trap_undef
	.extern	__dv_syscall
	.extern	__dv_trap_prefetch_abort
	.extern	__dv_trap_data_abort
	.extern	__dv_trap_reserved
	.extern	__dv_irq
	.extern	__dv_trap_fiq
        

	.section	"Vectors","a"

__dv_exception_vectors:
	ldr		pc, trapaddr_reset
	ldr		pc, trapaddr_undef
	ldr		pc, trapaddr_sbreak
	ldr		pc, trapaddr_prefetch_abort
	ldr		pc, trapaddr_data_abort
	ldr		pc, trapaddr_reserved
	ldr		pc, trapaddr_irq
	ldr		pc, trapaddr_fiq
    

trapaddr_reset:				.word		__dv_arm_startup
trapaddr_undef:				.word		__dv_trap_undef
trapaddr_sbreak:			.word		__dv_syscall
trapaddr_prefetch_abort:	.word		__dv_trap_prefetch_abort
trapaddr_data_abort:		.word		__dv_trap_data_abort
trapaddr_reserved:			.word		__dv_trap_reserved
trapaddr_irq:				.word		__dv_irq
trapaddr_fiq:				.word		__dv_trap_fiq

	.text

/* FIXME: temporary handlers for unused traps
*/
__dv_trap_undef:
__dv_trap_prefetch_abort:
__dv_trap_data_abort:
__dv_trap_reserved:
__dv_trap_fiq:
trap_stop:
	b		trap_stop   

