/*	x86-cstartup.c - __dv_C_startup (for x86 family)
 *
 *	Copyright 2009 David Haworth
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
#include <davros/basic-types.h>
#include <davros/init.h>
#include <x86-interrupt.h>

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

const __dv_stackelement_t *__dv_irq_sp = &__dv_nullstack[DV_CFG_NULLSTACK_LEN];

/*==============================================================================
 *	__dv__C_startup - the C part of the system startup code
 *==============================================================================
*/
void __dv_C_startup(void)
{
	__dv_init_pic();		/* All interrupt sources disabled */
}
