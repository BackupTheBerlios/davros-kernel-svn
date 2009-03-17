/* types.h - simple Davros typedefs
 *
 *	Copyright 2001 David Haworth
 *
 *	This file is free software; you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation; either version 2, or (at your option)
 *	any later version.
 *
 *	It is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with this program; see the file COPYING.  If not, write to
 *	the Free Software Foundation, 59 Temple Place - Suite 330,
 *	Boston, MA 02111-1307, USA.
 *
 *
*/

#ifndef __davros_types_h
#define __davros_types_h

#include "davros/defines.h"

__DAVROS_IDENT("$Id$")

#include "arch-cpudef.h"

#ifndef __ASSEMBLER__

/*	Defaults for Davros types. These can be overridden in arch/kernel.h
 *	by declaring the appropriate typedef, and defining the corresponding
 *	macro to inhibit the declaration here.
 *	Some "standard" definitions are assumed:
 *	boolean_t, byte_t, int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t,
 *	size_t, memaddr_t.
*/

/* This is the type used for the key value for queues. It must be able to
   contain a process priority, a sleep count.
*/
#ifndef __DAVROS_QKEY_T
typedef int32_t __davros_qkey_t;
#define __DAVROS_QKEY_T
#endif

/* This is the type used for semaphore counts. Must be signed.
*/
#ifndef __DAVROS_SEMCOUNT_T
typedef int32_t __davros_semcount_t;
#define __DAVROS_SEMCOUNT_T
#endif

/* This is the type used for simple message passing. Must be able to
   hold a memory address. Must also be able to hold __DAVROS_SYSERR
*/
#ifndef __DAVROS_MSG_T
typedef int32_t __davros_msg_t;
#define __DAVROS_MSG_T
#endif

/* This type is used for status return values. */
#ifndef __DAVROS_STATUS_T
typedef int32_t __davros_status_t;
#define __DAVROS_STATUS_T
#endif

/* This is the data type of a free-running counter.
*/
#ifndef __DAVROS_FRC_T
typedef uint32_t __davros_frc_t;
#define __DAVROS_FRC_T
#endif

#endif

#endif
