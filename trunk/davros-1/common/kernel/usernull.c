/*	usernull.c - __user_nullproc
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
 *	This file contains a default version of __user_nullproc()
*/

#ifndef __DAVROS_COMPLETE
#include "davros/kernel.h"
#endif

__DAVROS_IDENT("$Id$")

/*==============================================================================
 *	__user_nullproc - idling function
 *==============================================================================
*/
void __user_nullproc(void)
{
}
