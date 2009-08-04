/*	x86-pc.h - definitions for the x86 "IBM PC" architecture
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

#ifndef __dv_x86_pc_h
#define __dv_x86_pc_h

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

/* I/O addresses of peripherals
*/
#define __dv_i8253_base		0x40

/* Interrupt assignments
*/
#define __DV_NUMINT			16

#define __DV_INTNUM_TIMER	0
#define __DV_INTNUM_KBD		1
#define __DV_INTNUM_TTY0	4
#define __DV_INTNUM_TTY1	3
#define __DV_INTNUM_FD		6
#define __DV_INTNUM_PAR		7
#define __DV_INTNUM_RTC		8
#define __DV_INTNUM_IDE0	14


#endif
