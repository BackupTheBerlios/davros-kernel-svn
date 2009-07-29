/*	x86-interrupt.h - header file for x86 interrupt controller
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

#ifndef __dv_x86_interrupt_h
#define __dv_x86_interrupt_h

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

/* FIXME: eventually we'll have to select the appropriate file based on CPU, board, ...
 * For now we just assume a standard PC arrangement of 8259s
*/
#include <drv/i8259-pic.h>

#endif
