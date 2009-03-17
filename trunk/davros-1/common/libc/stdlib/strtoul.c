/*	strtoul.c
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
 *	Convert numeric string to unsigned integer
*/

#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <arch-cpudef.h>

unsigned long strtoul(const char *s, char **e, int b)
{
	int sign = 0;
	int digit = 0;
	int loop = 1;
	unsigned long val = 0;
	char c;
	int cval;
	const char *p = s;

	if ( b < 0 || b == 1 || b > 36 )
	{
		if ( e != NULL )
			*e = (char *)p;
		seterrno(ERANGE);
		return(0);
	}

	while ( isspace(*p) )
		p++;
	if ( *p == '+' )
	{
		sign = 1;
		p++;
	}
	else
	if ( *p == '-' )
	{
		sign = -1;
		p++;
	}
	if ( *p == '0' )
	{
		p++;
		if ( (b == 0 || b == 16) && (*p == 'x' || *p == 'X') )
		{
			b = 16;
			p++;
		}
		else
		{
			digit = 1;
			if ( b == 0 )
				b = 8;
		}
	}
	if ( b == 0 )
		b = 10;
	while ( loop )
	{
		c = *p;
		if ( c >= '0' && c <= '9' )
			cval = c - '0';
		else
		if ( c >= 'a' && c <= 'z' )
			cval = c - 'a' + 10;
		else
		if ( c >= 'A' && c <= 'Z' )
			cval = c - 'A' + 10;
		else
			loop = 0;
		if ( loop && cval < b )
		{
			digit = 1;
			val = val * b + cval;
			p++;
		}
		else
			loop = 0;
	}

	if ( e != NULL )
	{
		if ( digit )
			*e = (char *)p;
		else
			*e = (char *)s;
	}
	if ( sign < 0 )
	{
		if ( val <= LONG_MAX )
			val = (unsigned long)(-(long)val);
		else
		{
			val = ULONG_MAX;
			seterrno(ERANGE);
		}
	}
	return(val);
}
