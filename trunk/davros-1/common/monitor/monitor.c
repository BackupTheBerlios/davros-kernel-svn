/*	monitor.c - monitor and boot loader
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
 *	This file contains the main program of the boot monitor and loader.
 *
 *  Commands (not case sensitive):
 *		Sn....	- Type n S-Record 
 *		Ba		- display value of byte at location a
 *		Ha		- display value of 16-bit word at location a
 *		Wa		- display value of 32-bit word at location a
 *		Ba=v	- set byte at location a to v
 *		Ha=v	- set 16-bit word at location a to v
 *		Wa=v	- set 32-bit word at location a to v
 *		Da,l,s	- dump l words memory starting at a. Word size is s.
 *		Ma,s	- modify memory starting at a. Word size is s.
 *		Ga		- call subroutine at address a
 *		Q		- quit
 *
 *  Requires architecture-dependent functions or macros:
 *
 *		char readchar(void) - returns next character from input
 *			(serial port or whatever). Waits until available.
 *
 *		void writechar(char c) - writes character c to output (serial port
 *			or whatever). Waits until space available in output buffer.
 *
 *		uint8_t peek8(memaddr_t a) - returns the byte at address a.
 *		uint16_t peek16(memaddr_t a) - returns the 16-bit word at address a.
 *		uint32_t peek32(memaddr_t a) - returns the 32-bit word at address a.
 *
 *		void poke8(memaddr_t a, uint8_t v) - set the byte of memory at address a to v.
 *		void poke16(memaddr_t a, uint16_t v) - set the 16-bit word of memory at address a to v.
 *		void poke32(memaddr_t a, uint32_t v) - set the 32-bit word of memory at address a to v.
 *
 *		void go(memaddr_t a) - calls subroutine at a
 *
 *		ADDRSIZE - size of an address, in bits.
 *
*/

#include "arch-cpudef.h"
#include "arch-mon.h"
#include "monitor.h"
#include "ctype.h"

/*	Messages etc. */
const char what[]		= "What?";
const char how[]		= "How?";
const char sorry[]		= "Sorry :-(";

/*	Local functions */
static void word_op(int s, char *p);
static void go_op(char *p);
static void dump(char *p);
static void modify(char *p);

#ifdef poke8	/* If poke8 is a macro, we can't pass it to process_s_record */
static void mypoke(memaddr_t a, uint8_t b)
{
	poke8(a, b);
}
#else
#define mypoke poke8
#endif

void monitor(char *prompt)
{
	char line[MAXLINE+2];
	char *p;

	for (;;)
	{
		mprintf("%s", prompt);
		mgets(line, MAXLINE);
		p = skipspaces(line);
		switch ( *p )
		{
		case '\0':
			/* Nothing */
			break;

		case 's':
		case 'S':
			switch ( process_s_record(p, mypoke) )
			{
			case 0:		/* OK - no message */
				break;

			case SREC_EOF:
				mprintf("End of S-record file\n");
				break;

			case SREC_BADTYP:
			case SREC_BADLEN:
			case SREC_NONHEX:
			case SREC_BADCK:
				mprintf("Bad S-record: \"%s\"\n", line);
				break;

			}
			break;

		case 'b':
		case 'B':
			word_op(1, p+1);
			break;

		case 'h':
		case 'H':
			word_op(2, p+1);
			break;

		case 'w':
		case 'W':
			word_op(4, p+1);
			break;

		case 'd':
		case 'D':
			dump(p+1);
			break;

		case 'm':
		case 'M':
			modify(p+1);
			break;

		case 'g':
		case 'G':
			go_op(p+1);
			break;

		case 'q':
		case 'Q':
			return;

		default:
			mprintf("%s\n", what);
			break;
		}
	}
}

static void word_op(int s, char *p)
{
	memaddr_t a;
	uint32_t v;

	p = skipspaces(p);
	a = gethex(&p, sizeof(memaddr_t)*2);
	if ( p == NULL )
	{
		mprintf("%s\n", how);
	}
	else
	{
		p = skipspaces(p);
		if ( *p == '\0' )
		{
			switch ( s )
			{
			case 1:
				mprintf("%08x = %02x\n", a, peek8(a));
				break;
			case 2:
				mprintf("%08x = %04x\n", a, peek16(a));
				break;
			case 4:
				mprintf("%08x = %08x\n", a, peek32(a));
				break;
			}
		}
		else
		if ( *p == '=' )
		{
			p = skipspaces(p+1);
			v = gethex(&p, s*2);
			if ( p == NULL ||
				 *(p = skipspaces(p)) != '\0' )
			{
				mprintf("%s\n", how);
			}
			else
			{
				switch ( s )
				{
				case 1:
					poke8(a, v);
					break;
				case 2:
					poke16(a, v);
					break;
				case 4:
					poke32(a, v);
					break;
				}
			}
		}
	}
}

void dump(char *p)
{
	memaddr_t a, ca;
	int l = 16;
	int s = 1;
	int i;
	int c;

	p = skipspaces(p);
	a = gethex(&p, sizeof(memaddr_t)*2);

	if ( p == NULL )
	{
		mprintf("%s\n", how);
		return;
	}

	p = skipspaces(p);
	if ( *p == ',' )
	{
		p = skipspaces(p+1);
		l = gethex(&p, 4);
		if ( p == NULL )
		{
			mprintf("%s\n", how);
			return;
		}
		p = skipspaces(p);
		if ( *p == ',' )
		{
			p = skipspaces(p+1);
			s = gethex(&p, 1);
			if ( p == NULL )
			{
				mprintf("%s\n", how);
				return;
			}
			p = skipspaces(p);
		}
	}

	if ( *p != '\0' )
	{
		mprintf("%s\n", how);
		return;
	}

	if ( !(s == 1 || s == 2 || s == 4) )
	{
		mprintf("%s\n", sorry);
		return;
	}

	while ( l > 0 )
	{
		mprintf("%08x", a);
		i = 16;
		ca = a;
		while ( i > 0 && l > 0 )
		{
			if ( s == 1 && i == 8 )
				mprintf(" -");
			switch ( s )
			{
			case 1:
				mprintf(" %02x", peek8(a));
				break;
			case 2:
				mprintf(" %04x", peek16(a));
				break;
			case 4:
				mprintf(" %08x", peek32(a));
				break;
			}
			a += s;
			i -= s;
			l -= s;
		}
		if ( s == 1 )
		{
			mprintf("   ");
			while ( ca < a )
			{
				c = peek8(ca++);
				if ( c <= 0x20 || c >= 0x7f )
					c = '.';
				mprintf("%c", c);
			}
		}
		mprintf("\n");
	}
}

void modify(char *p)
{
	/* FIXME - to do */
}

void go_op(char *p)
{
	memaddr_t a;

	p = skipspaces(p);
	a = gethex(&p, sizeof(memaddr_t)*2);

	if ( p == NULL )
	{
		mprintf("%s\n", how);
	}
	else
	{
		go(a);
	}
}
