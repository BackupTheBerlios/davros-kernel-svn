/*	processors.h - list of (potentially) supported processors
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
 *
 *	(c)2000 D.R.Haworth
*/

#ifndef __davros_processors_h
#define __davros_processors_h

#error "Obsolete!"

#ifdef __DAVROS_IDENT
__DAVROS_IDENT("$Id$")
#endif

/*	Masks for fields	*/
#define CPU_MASK_FAMILY	0xFF00

#define	CPU_FAMILY_63XX	0x0100		/*	63xx family of CPUs	*/

#define CPU_6301		0x0101
#define CPU_6301X		0x0102
#define CPU_6301Y		0x0103
#define CPU_6303		0x0111
#define CPU_6303X		0x0112
#define CPU_6303Y		0x0113
#define CPU_6801		0x0121


#define CPU_FAMILY_MIPS_LE	0x0200		/* MIPS little-endian family of CPUs */

#define CPU_VR4121		0x0201
#define CPU_VR4122		0x0202

#define CPU_FAMILY_MIPS_BE	0x0300		/* MIPS big-endian family of CPUs */

#define CPU_R4300		0x0301

#endif
