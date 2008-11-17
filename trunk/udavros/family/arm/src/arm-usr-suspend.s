/*	arm-usr-suspend.s - __dv_usr_suspend
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
#include <davros/syscall.h>

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

/*==============================================================================
 *	__dv_usr_suspend - assembler stub for "suspend" system call
 *==============================================================================
*/
	.text
	.balign	4

	.global	DvSuspend
	.global	__dv_usr_suspend

DvSuspend:
__dv_usr_suspend:
	swi		__DV_SC_SUSPEND
	bx		lr

/* Editor settings:
 * vi:set ts=4:
*/
