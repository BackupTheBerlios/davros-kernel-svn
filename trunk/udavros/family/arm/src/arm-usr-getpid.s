/*	arm-usr-getpid.s - __dv_usr_getpid
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
 *	__dv_usr_getpid - assembler stub for getpid system call
 *==============================================================================
*/
	.text
	.balign	4

	.global	DvGetpid
	.global	__dv_usr_getpid

DvGetpid:
__dv_usr_getpid:
	swi		__DV_SC_GETPID
	bx		lr

/* Editor settings:
 * vi:set ts=4:
*/
