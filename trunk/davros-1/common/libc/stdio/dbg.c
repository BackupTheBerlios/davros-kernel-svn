/*	dbg.c
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
 *	Selectable, configurable debugging
*/

#include "dbg.h"
#ifdef DEBUGGING

#include <stdio.h>
#include <stdarg.h>

int __dbglvl = 12;

int __dbg_func(char *f, ...)
{
	int r;
	va_list ap;
	va_start(ap, f);
	r = fprintf(stderr, "-- DBG: ");
	r += vfprintf(stderr, f, ap);
	r += fprintf(stderr, "\n");
	va_end(ap);
	return(r);
}
#endif
