/*	kprintf.c - formatted output to terminal (polled driver)
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
 *	This file contains kprintf. kprintf prints formatted output
 *	on the console using the driver's polled mode.
 *
*/

#include "arch-cpudef.h"
#include "stdarg.h"

#define __STDIO_PRIVATE
#include "stdio.h"

int kprintf(const char *fmt, ...)
{
	int nprinted;
	va_list ap;
	int modesave;

	va_start(ap, fmt);

	modesave = kmode(KPOLLED);
	nprinted = __xprintf(kputc, NULL, fmt, ap);
	kmode(modesave);
	va_end(ap);

	return(nprinted);
}
