/*	tick.c - __davros_tick
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

#ifndef __DAVROS_ASM_TICK

#ifndef __DAVROS_COMPLETE
#include "davros/kernel.h"
#include "davros/kdebug.h"
#define __STDIO_PRIVATE
#include "stdio.h"
#endif

__DAVROS_IDENT("$Id$")

/*==============================================================================
 *	__davros_tick - called by clock interrupt dispatcher to awaken processes
 *==============================================================================
*/
void __davros_tick(void)
{
	KDBG(1, KDBG_TIMER, "__davros_tick()\n");

	if ( __davros.sleepcount != NULL )
	{
		(*__davros.sleepcount)--;
		if ( *__davros.sleepcount <= 0 )
			__davros_wakeup();
	}
}

#endif
