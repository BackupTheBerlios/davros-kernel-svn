/*	rb8put.c - __dv_rb8_put
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
#include <dvlib/ringbuf.h>

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

/*==============================================================================
 *	__dv_rb8_put - put an element into a ring buffer of type uint8
 *==============================================================================
*/
__dv_status_t __dv_rb8_put
(	__dv_ringbuf8_t *rb,
	__dv_uint8_t elem
)
{
	__dv_status_t result = __DV_ERR;

	if ( rb->count < rb->len )
	{
		rb->count++;
		*rb->in++ = elem;
		if ( rb->in >= &rb->buf[rb->len] )
		{
			rb->in = rb->buf;
		}

		result = __DV_OK;
	}

	return result;
}
