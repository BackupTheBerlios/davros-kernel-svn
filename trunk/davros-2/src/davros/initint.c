/*	initint.c - __dv_initint
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
#include <davros/interrupt.h>

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

/*==============================================================================
 *	Kernel variables
 *==============================================================================
*/
__dv_interruptentry_t __dv_interrupt_table[__DV_NUMINT];

/*==============================================================================
 *	__dv_initint - initialise the davros interrupt table
 *==============================================================================
*/
void __dv_initint(void)
{
	__dv_int_t i;
	__dv_interruptentry_t *isr;

	isr = __dv_interrupt_table;
	for ( i = 0; i < __DV_NUMINT; i++ )
	{
		isr->func = __dv_unused_interrupt;
		isr->param = (void *)i;
		isr++;
	}
}
