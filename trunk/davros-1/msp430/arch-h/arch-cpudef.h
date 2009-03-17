/*	arch-cpudef.h - MSP430 CPU definition
 *
 *	$Id$
 *	Copyright 2004 David Haworth
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
 *	This file contains basic architecture-independent data types
 *	defined as required for msp430
 *
 *	$Log: arch-cpudef.h,v $
 *	Revision 1.1  2004/05/11 20:45:55  dave
 *	Files for new msp430 port.
 *	
*/

#if !defined(__arch_cpudef_h)
#define __arch_cpudef_h

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(__ASSEMBLER__)

/* Basic types of given size */
#if 0
typedef signed char		int8_t;
typedef unsigned char	uint8_t;
typedef int				int16_t;
typedef unsigned int	uint16_t;
typedef long			int32_t;
typedef unsigned long	uint32_t;
#else
#include <sys/inttypes.h>
#endif

/* Some types defining the machine */
typedef uint16_t		memaddr_t;		/* Integer that can hold address */
typedef uint16_t		maxword_t;		/* Largest possible integer */
typedef int16_t			boolean_t;		/* Best size for a boolean */
typedef	uint16_t		size_t;			/* Size of memory chunks, etc. */
typedef uint8_t			byte_t;			/* Davros needs this */

/* If NULL hasn't been supplied, do it now */
#if !defined(NULL)
#define NULL	((void *)0)
#endif

/* MSP430 is little-endian */
#define LITTLE_ENDIAN
#undef BIG_ENDIAN

/* MSP430's stack grows down from a high address */
#define STACK_GROWS_DOWN
#undef STACK_GROWS_UP

/* These are used to convert a long to an int, and an int to a short */
#define	LONGtoINT	0xffff
#define INTtoSHORT	0xffff

/* Max and min values for data types */
#define ULONG_MAX	0xffffffff
#define ULONG_MIN	0
#define LONG_MAX	0x7fffffff
#define LONG_MIN	0x80000000

#endif

#ifdef __cplusplus
}
#endif

#endif
