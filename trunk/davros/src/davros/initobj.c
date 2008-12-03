/*	initobj.c - __dv_initobj
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
#include <davros/object.h>
#include <davros/mem.h>
#include <davros/error.h>

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

/*==============================================================================
 *	Kernel variables
 *==============================================================================
*/
__dv_obj_t	**__dv_objtbl;
__dv_int_t __dv_nextobj;
__dv_int_t __dv_nobj;

/*==============================================================================
 *	__dv_initobj - initialise the davros object management system
 *
 * Prerequisite: the memory pool is already initialised.
 *==============================================================================
*/
void __dv_initobj(void)
{
	__dv_int_t i;

	__dv_objtbl = (__dv_obj_t **)__dv_getmem(DV_CFG_N_OBJECTS * sizeof(__dv_obj_t*));

	if ( __dv_objtbl == __DV_NULL )
	{
		__dv_die();
	}

	for ( i = 0; i < DV_CFG_N_OBJECTS; i++ )
	{
		__dv_objtbl[i] = __DV_NULL;
	}

	__dv_nextobj = 0;
	__dv_nobj = DV_CFG_N_OBJECTS;
}
