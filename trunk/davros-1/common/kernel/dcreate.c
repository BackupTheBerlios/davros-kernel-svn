/*	dcreate.c - __davros_dcreate
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
 *	__davros_dcreate - create a new device
 *==============================================================================
*/
__davros_device_t *__davros_dcreate
(	__davros_device_t *dev,		/* device struct to initialise */
	char *name,					/* device name (max	__DAVROS_DVNMLEN) */
	const __davros_devsw_t *sw	/* switch table	for	device */
)
{
	memset(dev, 0, sizeof(__davros_device_t));
	strncpy(dev->name, name, __DAVROS_DVNMLEN);
	dev->dvsw = (__davros_devsw_t *)sw;		/* typcast avoids warning "discards const */
	__davros_enqueue(&dev->devtab_entry, &__davros.devtab);

	return(dev);
}
