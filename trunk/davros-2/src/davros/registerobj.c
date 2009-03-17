/*	getobjid.c - __dv_getobjid
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

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

/*========================================================================================
 *	__dv_registerobj - get a free object ID (== slot in object table) and put object in it
 *========================================================================================
*/
__dv_int_t __dv_registerobj(__dv_obj_t *obj)
{
	__dv_int_t i;
	__dv_int_t result = -1;

	for ( i = 0; (result < 0) && (i < __dv_nobj); i++ )
	{
		/* Examine next object in table. If it's free, occupy it
		 * and set the return value.
		*/
		if ( __dv_objtbl[__dv_nextobj] == __DV_NULL )
		{
			__dv_objtbl[__dv_nextobj] = obj;
			obj->id = __dv_nextobj;
			__Dv_SetMagic(obj);
			result = __dv_nextobj;
		}

		/* Move to the next object. This speeds things up - we know that the "current"
		 * object has been taken. At startup, the "next" object is always free
		*/
		__dv_nextobj++;
		if ( __dv_nextobj >= __dv_nobj )
		{
			__dv_nextobj = 0;
		}
	}

	return result;
}
