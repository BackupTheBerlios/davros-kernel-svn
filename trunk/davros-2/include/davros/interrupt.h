/*	interrupt.h - interrupt table header file for davros
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

#ifndef __dv_interrupt_h
#define __dv_interrupt_h

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

#include <davros/basic-types.h>

#define __DV_BASEFILE	interrupt
#include <davros/family-select.h>

typedef void (*__dv_interruptfunc_t)(void *);
typedef struct __dv_interruptentry_s __dv_interruptentry_t;

struct __dv_interruptentry_s
{
	__dv_interruptfunc_t func;
	void *param;
};

__dv_interruptentry_t __dv_interrupt_table[__DV_NUMINT];


void __dv_initint(void);
__dv_status_t __dv_register_interrupt(__dv_unsigned_t, __dv_interruptfunc_t, void*);
__dv_status_t __dv_deregister_interrupt(__dv_unsigned_t);

__dv_status_t __dv_enable_interrupt(__dv_unsigned_t);	/* Provided by CPU */
__dv_status_t __dv_disable_interrupt(__dv_unsigned_t);	/* Provided by CPU */

void __dv_unused_interrupt(void *);

#endif
