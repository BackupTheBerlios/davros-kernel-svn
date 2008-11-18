/*	startup.c - __dv_startup
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

/* DV_FILE_STARTUP is defined before including davros-config.h. This is so that
 * davros-config.h can include any extra header files it needs for its init macros
 * and/or null loops
*/
#define DV_FILE_STARTUP
#include <davros/config.h>
#include <davros/constants.h>
#include <davros/queue.h>
#include <davros/process.h>
#include <davros/init.h>

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

#if !defined DV_CFG_HEAPBASE || !defined DV_CFG_HEAPSIZE
#error "Configuration does not define bounds of free memory for heap"
#define DV_CFG_HEAPBASE	0
#define DV_CFG_HEAPSIZE	0
#endif

#ifdef DV_CFG_USERINIT
#define __dv_call_user_init()	DV_CFG_USERINIT()
#else
#define __dv_call_user_init()
#endif

#ifdef DV_CFG_USERPROCESS
const __dv_processconfig_t __dv_userproc = { DV_CFG_USERPROCESS };
#define __dv_create_user_process()	__dv_usr_resume(__dv_usr_create(&__dv_userproc, 1))
#else
#define __dv_create_user_process()
#endif

#ifdef DV_CFG_USERNULL
#define __dv_null()		DV_CFG_USERNULL()
#else
#define __dv_null()		for (;;)
#endif

/*==============================================================================
 *	__dv_startup - start up the user's processes etc., then become null process
 *==============================================================================
*/
void __dv_startup(void)
{
	__dv_init(DV_CFG_HEAPBASE, DV_CFG_HEAPSIZE);

	__dv_call_user_init();

	__dv_create_user_process();

	__dv_null();
}
