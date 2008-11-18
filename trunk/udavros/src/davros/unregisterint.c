/*	unregisterint.c - __dv_unregister_interrupt
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
#include <davros/basic-types.h>
#include <davros/constants.h>
#include <davros/interrupt.h>

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

/*==============================================================================
 *	__dv_unregister_interrupt - unregister a handler for an interrupt
 *==============================================================================
*/
__dv_status_t __dv_unregister_interrupt
(	__dv_unsigned_t intno
)
{
	__dv_status_t result = __DV_ERR;
	__dv_interruptentry_t *isr;

	if ( intno < __DV_NUMINT )
	{
		isr = &__dv_interrupt_table[intno];
		isr->func = __dv_unused_interrupt;
		isr->param = (void *)intno;
		result = __DV_OK;
	}

	return result;
}
