/*	x86-in8.s - __dv_in8
 *
 *	Copyright 2009 David Haworth
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
*/

#include <x86-asm.h>

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

/*	__dv_in8 - input 8-bit value from specified port using x86 inb instruction
*/
	.global	__dv_in8
	.type	__dv_in8,@function

	.text
	.align	4

__dv_in8:
	movl	4(%esp),%edx
	movl	$0,%eax
	inb		%dx,%al
	ret
