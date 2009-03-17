/*	object.h - header file for davros objects
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

#ifndef __dv_object_h
#define __dv_object_h

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

#include <davros/cpu-characteristics.h>
#include <davros/basic-types.h>

/* __dv_magic_t is nearly always unsigned 32-bit to provide some confidence.
 * However, we still permit family-specific override.
 * The magic number can be omitted completely to save space.
*/
#ifndef __DV_MAGIC_T
#define __DV_MAGIC_T		__dv_uint32_t
#define __DV_SIZEOF_MAGIC	4
#endif

#ifndef __DV_MAGIC
#define __DV_MAGIC			0x5CABD00D
#endif

#ifndef __DV_USE_MAGIC
#error "__DV_USE_MAGIC is not defined"
#elif __DV_USE_MAGIC

#define __DV_MAGIC_DECL		__dv_magic_t magic;
#define __Dv_MagicOk(o)		((o)->magic == __DV_MAGIC)
#define __Dv_SetMagic(o)	do { (o)->magic = __DV_MAGIC;	} while(0)
#define __Dv_UnsetMagic(o)	do { (o)->magic = ~__DV_MAGIC;	} while(0)
#define __DV_SIZEOF_OBJ		(__DV_SIZEOF_MAGIC+__DV_SIZEOF_OBJTYPE+__DV_SIZEOF_OBJID)

#else

#define __DV_MAGIC_DECL		
#define __Dv_MagicOk(o)		1
#define __Dv_SetMagic(o)	do { } while(0)
#define __Dv_UnsetMagic(o)	do { } while(0)
#define __DV_SIZEOF_OBJ		(__DV_SIZEOF_OBJTYPE+__DV_SIZEOF_OBJID)

#endif

/* 16 bits will normally suffice for object type and object id.
 * On really small systems could reduce to 8-bit
 * WARNING: __DV_SIZEOF_OBJ might need rounding up!
*/
#ifndef __DV_OBJTYPE_T
#define __DV_OBJTYPE_T		__dv_uint16_t
#define __DV_SIZEOF_OBJTYPE	2
#endif

#ifndef __DV_OBJID_T
#define __DV_OBJID_T		__dv_uint16_t
#define __DV_SIZEOF_OBJID	2
#endif

/* Davros object structure
*/
#ifndef __DV_ASM

typedef __DV_MAGIC_T __dv_magic_t;
typedef __DV_OBJTYPE_T __dv_objtype_t;
typedef __DV_OBJID_T __dv_objid_t;
typedef	struct __dv_obj_s __dv_obj_t;

struct __dv_obj_s
{
	__DV_MAGIC_DECL
	__dv_objtype_t type;
	__dv_objid_t id;
};

/* Object management variables
*/
extern __dv_obj_t **__dv_objtbl;
extern __dv_int_t __dv_nextobj;
extern __dv_int_t __dv_nobj;

/* Prototypes for internal object management functions
*/
void __dv_initobj(void);
__dv_int_t __dv_registerobj(__dv_obj_t*);
void __dv_deregisterobj(__dv_obj_t*);

#endif

/* List of object types known to the kernel
 * 0 is not used, neither is the MAX value (__dv_objtype_t)(-1)
*/
#define __DV_OBJTYPE_NONE			1
#define __DV_OBJTYPE_PROCESS		2

#define __DV_OBJID_INVALID			(__dv_objid_t)(-1)

#define __DV_IS_VALID_OBJECT(o, t)	( ( (o)->type == (t) ) &&			\
									  ( (o)->id < __dv_nobj ) &&		\
									  ( __dv_objtbl[(o)->id] == (o) ) )

#endif
