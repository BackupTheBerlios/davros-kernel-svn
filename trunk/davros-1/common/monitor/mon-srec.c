/*	mon-srec.c - monitor s-record handling
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
 *	This file contains S-record handling functions.
*/

#include "arch-cpudef.h"
#include "monitor.h"
#include "ctype.h"
#include "string.h"

#ifdef __LINUX_TEST__
#include "/usr/include/stdio.h"
#endif

/* process_s_record
 *
 * Parameters:
 *
 *	line  - contains the complete S-record. The S is in line[0],
 *			followed immediately by the type, ...
 *	p	  -	a function to poke a byte of memory. This function
 *			should be capable of programming flash if necessary.
 *
 * Return codes:
 *	0	  -	OK
 *	1	  - EOF (S9) record found
 *  <0	  - Bad S-Record
*/

int process_s_record(char *line, pokefunc_t _poke)
{
	int slen;
	memaddr_t addr;
	char *p;
	int len;
	int addrlen = 4;
	int ck;
	int i;

	len = strlen(line);
	p = &line[2];
	switch ( line[1] )
	{
	case '3':
		addrlen += 2;
		/* Fall through */
	case '2':
		addrlen += 2;
		/* Fall through */
	case '1':
#ifdef __LINUX_TEST__
		printf("S%c-record, len = %d\n", line[1], len);
#endif
		if ( len < 10 ||
			 (slen = gethex(&p, 2)) < 3 ||
			 len < 2*slen+4 )
		{
			return(SREC_BADLEN);
		}
		ck = slen;
		for ( i=0; i<slen; i++ )
		{
			if ( isxdigit(*p) && isxdigit(*(p+1)) )
				ck += gethex(&p, 2);
			else
				return(SREC_NONHEX);
		}
		if ( (ck & 0xff) != 0xff )
		{
			return(SREC_BADCK);
		}
		p = &line[4];
		addr = gethex(&p, addrlen);
#ifdef __LINUX_TEST__
		printf("S%c-record, addr = %04x, slen = %02x\n", line[1], addr, slen);
#endif
		slen -= (1 + addrlen/2);		/* Address & Checksum */
		while ( slen > 0 )
		{
			_poke(addr, gethex(&p, 2));
			addr++;
			slen--;
		}
		break;

	case '9':
		return(SREC_EOF);
		break;

	default:
		return(SREC_BADTYP);
		break;
	}
	return(0);
}
