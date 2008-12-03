/*	ringbuf.h - ring buffers
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

#ifndef __dv_ringbuf_h
#define __dv_ringbuf_h

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

#include <davros/basic-types.h>

typedef struct _dv_ringbuf8_s __dv_ringbuf8_t;
typedef struct _dv_ringbuf16_s __dv_ringbuf16_t;
typedef struct _dv_ringbuf32_s __dv_ringbuf32_t;

struct _dv_ringbuf8_s
{
	__dv_uint8_t *in;			/* Place where elemets go in to the buffer */
	__dv_uint8_t *out;			/* Place where elemnts come out of the buffer */
	__dv_int_t len;				/* Length of the buffer */
	__dv_int_t count;			/* No. of elements currently in the buffer */
	__dv_uint8_t buf[1];		/* Placeholder. Correct no. of elements is allocated */
};

struct _dv_ringbuf16_s
{
	__dv_uint16_t *in;			/* Place where elemets go in to the buffer */
	__dv_uint16_t *out;			/* Place where elemnts come out of the buffer */
	__dv_int_t len;				/* Length of the buffer */
	__dv_int_t count;			/* No. of elements currently in the buffer */
	__dv_uint16_t buf[1];		/* Placeholder. Correct no. of elements is allocated */
};

struct _dv_ringbuf32_s
{
	__dv_uint32_t *in;			/* Place where elemets go in to the buffer */
	__dv_uint32_t *out;			/* Place where elemnts come out of the buffer */
	__dv_int_t len;				/* Length of the buffer */
	__dv_int_t count;			/* No. of elements currently in the buffer */
	__dv_uint32_t buf[1];		/* Placeholder. Correct no. of elements is allocated */
};

#endif
