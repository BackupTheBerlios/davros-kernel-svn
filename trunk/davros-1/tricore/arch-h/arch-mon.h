/*	arch-mon.h - monitor functions for tricore
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
 *	This file defines the tricore versions of the architecture-dependent
 *	functions required by the monitor
 *
*/

#ifndef __arch_mon_h
#define __arch_mon_h

#include "tricore.h"
#include "drv/asc-drv.h"

#define arch_mon_init()	asc_polled_init(ASC0)
#define readchar()		asc_polled_getc(ASC0)
#if 0
#define writechar(c)	asc_polled_putc(ASC0, c)
#endif
void writechar(int c);

#define peek8(a)	(*(uint8_t *)(a))
#define peek16(a)	(*(uint16_t *)(a))
#define peek32(a)	(*(uint32_t *)(a))

#define poke8(a,v)	(*(uint8_t *)(a) = (v))
#define poke16(a,v)	(*(uint16_t *)(a) = (v))
#define poke32(a,v)	(*(uint32_t *)(a) = (v))

typedef void (*__funcp)(void);

#define go(a)		((*(__funcp)(a))())

#endif
