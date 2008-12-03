/*	rb8create.c - __dv_rb8_create
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
#include <davros/constants.h>
#include <davros/mem.h>
#include <dvlib/ringbuf.h>

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

/*==============================================================================
 *	__dv_rb8_create - create a ring buffer for elements of type uint8
 *==============================================================================
*/
__dv_ringbuf8_t *__dv_rb8_create
(	__dv_int_t len
)
{
	__dv_ringbuf8_t *rb;

	rb = (__dv_ringbuf8_t *)__dv_getmem(sizeof(__dv_ringbuf8_t) + (len-1)*sizeof(__dv_uint8_t));

	if ( rb != __DV_NULL )
	{
		rb->in = rb->buf;
		rb->out = rb->buf;
		rb->count = 0;
		rb->len = len;
	}

	return rb;
}
