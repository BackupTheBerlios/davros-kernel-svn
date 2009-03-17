/*	mon-stdio.c - stdio for monitor
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
 *	This file contains a limited stdio for the monitor
 *
 *  Requires architecture-dependent functions or macros:
 *
 *		char readchar(void) - returns next character from input
 *			(serial port or whatever). Waits until available.
 *
 *		void writechar(char c) - writes character c to output (serial port
 *			or whatever). Waits until space available in output buffer.
 *
*/

#include "arch-cpudef.h"
#include "arch-mon.h"
#include "monitor.h"

#include "stdarg.h"
#include "ctype.h"

#define __STDIO_PRIVATE
#include "stdio.h"

static int isreturn(char c)
{
	return ( c == '\n' || c == '\r' );
}

char *mgets(char *buf, int max)
{
	char c;
	char *p = buf;
	int i = 0;

	while ( !isreturn(c = readchar()) )
	{
		if ( c == BS ||
			 c == DEL )
		{
			if ( i > 0 )
			{
				i--;
				p--;
				writechar(BS);
				writechar(' ');
				writechar(BS);
			}
			else
				writechar(BEL);
		}
		else
		if ( i < max && c >= ' ' && c < 0x7f )
		{
			writechar(c);
			*p++ = c;
			*p = '\0';
			i++;
		}
		else
			writechar(BEL);
	}
	writechar('\r');
	writechar('\n');
	return(buf);
}

static int __putc(int c, void *dev)
{
	writechar(c);
	return(0);
}

int mprintf(char *fmt, ...)
{
	int n;
	va_list ap;
	va_start(ap,fmt);

	n = __xprintf(__putc, NULL, fmt, ap);

	va_end(ap);

	return(n);
}
