/*	defines.h - common macros. These NEVER change!
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

#ifndef __davros_defines_h
#define __davros_defines_h

#ifdef __ASSEMBLER__

#define __DAVROS_IDENT(id)	.sbttl id

#else

#define __DAVROS_IDENT(id)

#endif

__DAVROS_IDENT("$Id$")

#ifndef FALSE
#define FALSE   0
#endif
#ifndef TRUE
#define TRUE    1
#endif
#ifndef NULL
#define NULL    0
#endif

#ifndef __DAVROS_COMER_STYLE
#ifndef __DAVROS_INTS_ENABLED
#define __DAVROS_COMER_STYLE	1
#endif
#endif

#endif
