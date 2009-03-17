/*	mon-util.c - monitor and boot loader odds'n'sods
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
 *	This file contains some odds'n'ends used by the monitor and in other
 *	places.
 *
*/

#include "arch-cpudef.h"
#include "arch-mon.h"
#include "monitor.h"
#include "ctype.h"

char *skipspaces(char *p)
{
	while ( isspace(*p) )
		p++;
	return(p);
}

int char2hex(char c)
{
	if ( c >= '0' && c <= '9' )
		return(c - '0');
	if ( c >= 'A' && c <= 'F' )
		return(c - 'A' + 10);
	if ( c >= 'a' && c <= 'f' )
		return(c - 'a' + 10);
	return(-1);
}

maxword_t gethex(char **pp, int max)
{
	char *p = *pp;
	memaddr_t a = 0;
	int v = 0;

	while ( max > 0 && v >= 0 && *p != '\0' )
	{
		v = char2hex(*p);
		if ( v < 0 )
		{
			if ( p == *pp )
			{
				*pp = NULL;
				return(0);
			}
		}
		else
		{
			a = ( a << 4 ) | ( v & 0x0f );
			p++;
		}
		max--;
	}

	*pp = p;
	return(a);
}
