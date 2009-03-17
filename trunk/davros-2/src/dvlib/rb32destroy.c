/*	rb32destroy.c - __dv_rb32_destroy
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
 *	__dv_rb32_destroy - destroy a ring buffer for elements of type uint32
 *==============================================================================
*/
__dv_status_t __dv_rb32_destroy
(	__dv_ringbuf32_t *rb
)
{
	return __dv_freemem(rb, sizeof(__dv_ringbuf32_t) + (rb->len-1)*sizeof(__dv_uint32_t));
}
