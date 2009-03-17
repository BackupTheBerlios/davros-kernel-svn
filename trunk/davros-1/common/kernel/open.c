/*	open.c - __davros_open
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

#ifndef __DAVROS_COMPLETE
#include "davros/kernel.h"
#include "string.h"
#endif

__DAVROS_IDENT("$Id$")

/*==============================================================================
 *	__davros_open - open a connection to a device
 *==============================================================================
*/
__davros_device_t *__davros_open
(	char *name,
	int	mode
)
{
	__davros_device_t *dev = NULL;

	if ( strncmp(name, "/dev/", 5) == 0 )
	{
		dev = __davros_dfind(&name[5]);
		if ( dev != NULL )
		{
			(*dev->dvsw->dvopen)(dev, name, mode);
		}
	}

	return(dev);
}
