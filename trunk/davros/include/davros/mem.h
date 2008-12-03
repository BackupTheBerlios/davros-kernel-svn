/*	mem.h - header file for davros memory allocation
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

#ifndef __dv_mem_h
#define __dv_mem_h

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

/* This file defines the data structures and constants used by
 * the memory allocation functions in davros.
*/

#include <davros/cpu-characteristics.h>
#include <davros/basic-types.h>

/* MBLOCK_CHUNK is the size in bytes of the memory chunks that can be
 * allocated. It must be a power of 2 (8, 16, 32 etc.) and must be at
 * least sizeof(__dv_mblock_t)
*/
#ifndef __DV_MBLOCK_CHUNK
#define __DV_MBLOCK_CHUNK	8
#endif

/* __DV_MEMROUND rounds a requested memory size UP to the next
 * __DV_MBLOCK_CHUNK. Note: this only works if __DV_MBLOCK_CHUNK
 * is an integral power of 2.
*/
#define	__DV_MEMROUND_MASK	(__DV_MBLOCK_CHUNK - 1)
#define __DV_MEMROUND(l)	(((l) + __DV_MEMROUND_MASK) & ~__DV_MEMROUND_MASK)


#ifndef __DV_ASM

/* Memory allocation/free list type and structure
*/
typedef struct __dv_mblock_s __dv_mblock_t;

struct __dv_mblock_s		/* memory management structure          */
{
	__dv_size_t len;		/* length of this block                 */
	__dv_mblock_t *next;	/* pointer to next block in free list   */
};

/* __dv_memhead is the global free list. It is a block of zero size
 * that "points" to tne first free block.
*/
extern __dv_mblock_t __dv_memhead;

/* Function prototypes
*/
void __dv_initmem(__dv_uint8_t*, __dv_size_t);
void *__dv_getmem(__dv_size_t);
__dv_status_t __dv_freemem(void*, __dv_size_t);

#endif

#endif
