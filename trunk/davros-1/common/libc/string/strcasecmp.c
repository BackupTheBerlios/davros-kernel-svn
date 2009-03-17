/*	strcasecmp.c
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
 *	Case-insensitive string comparison
*/

#include <string.h>
#include <ctype.h>

int strcasecmp(const char *s1, const char *s2)
{
	while ( tolower(*s1) == tolower(*s2) && *s1 != '\0' )
	{
		s1++;
		s2++;
	}
	if ( *s1 < *s2 )
		return(-1);
	if ( *s1 > *s2 )
		return(1);
	return(0);
}
