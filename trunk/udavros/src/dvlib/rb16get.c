/*	rb16get.c - __dv_rb16_get
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
 *	__dv_rb16_get - get an element from a ring buffer of type uint16
 *==============================================================================
*/
__dv_status_t __dv_rb16_get
(	__dv_ringbuf16_t *rb,
	__dv_uint16_t *elem
)
{
	__dv_status_t result = __DV_ERR;

	if ( rb->count > 0 )
	{
		rb->count--;
		*elem = *rb->out++;
		if ( rb->out >= &rb->buf[rb->len] )
		{
			rb->out = rb->buf;
		}

		result = __DV_OK;
	}

	return result;
}
