/*	deregisterobj.c - __dv_deregisterobj
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
#include <davros/error.h>

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

/*========================================================================================
 *	__dv_deregisterobj - set the objects slot in the object table to "free"
 *========================================================================================
*/
void __dv_deregisterobj(__dv_obj_t *obj)
{
	if ( __dv_objtbl[obj->id] == obj )
	{
		/* Set the slot to "empty"
		*/
		__dv_objtbl[obj->id] = __DV_NULL;

		/* If the next slot to examine for "freeness" isn't free,
		 * set it to this newly-freed slot
		 * Minor optimisation ... is it worthwhile FIXME
		*/
		if ( __dv_objtbl[__dv_nextobj] != __DV_NULL )
		{
			__dv_nextobj = obj->id;
		}

		/* Wipe the object
		*/
		obj->type = __DV_OBJTYPE_NONE;
		obj->id = __DV_OBJID_INVALID;
		__Dv_UnsetMagic(obj);
	}
	else
	{
		/* HELP! The object was never registered
		*/
		__dv_die();
	}
}
