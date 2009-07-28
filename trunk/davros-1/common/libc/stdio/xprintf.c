/*	xprintf.c - generalised formatted output
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
 *	This file contains the generalised formatted output function used by
 *	the whole family of *printf functions.
 *
*/

#include "arch-cpudef.h"
#include "ctype.h"
#include "stdarg.h"
#include "string.h"

#define __STDIO_PRIVATE
#include "stdio.h"

#define __XPRT_MAXSTR 15
static char *_prt10(unsigned long val, char *str);
static char *_prt16(unsigned long val, char *str, char *hexdgt);

int __xprintf
(	int (*__putc)(int, void *),
	void *dev,
	const char *fmt,
	va_list ap
)
{
	char ch, fill, string[__XPRT_MAXSTR+1], *str;
	uint8_t fmin, fmax, len, sign, ljust, longarg;
	uint8_t i, leading;
	int nprinted;
	long num;

	nprinted = 0;

	while ( (ch = *fmt++) != '\0' )
	{
		if ( ch != '%' )
		{
			(*__putc)(ch, dev);
			nprinted++;
		}
		else
		{
			sign = ljust = longarg = 0;
			fmin = 0;
			fmax = 255;
			fill = ' ';
			ch = *fmt++;

			if ( ch == '-' )
			{
				ljust = 1;
				ch = *fmt++;
			}
			if ( ch == '0' )
			{
				fill = '0';
				ch = *fmt++;
			}
			if ( ch == '*' )
			{
				fmin = va_arg(ap,int);
				ch = *fmt++;
			}
			else
			while ( isdigit(ch) )
			{
				fmin = fmin * 10 + (ch - '0');
				ch = *fmt++;
			}
			if ( ch == '.' )
			{
				ch = *fmt++;
				if ( ch == '*' )
				{
					fmax = va_arg(ap,int);
					ch = *fmt++;
				}
				else
				{
					fmax = 0;
					while ( isdigit(ch) )
					{
						fmax = fmax * 10 + (ch - '0');
						ch = *fmt++;
					}
				}
			}
			if ( ch == 'l' )
			{
				longarg = 1;
				ch = *fmt++;
			}
			str = string;

			switch (ch)
			{
			case '\0':
				(*__putc)('%', dev);
				nprinted++;
				return(nprinted);
				break;

			case 'c':
				if ( longarg )
					string[0] = (char) va_arg(ap, long);
				else
					string[0] = (char) va_arg(ap, int);
				string[1] = '\0';
				break;

			case 's':
				str = va_arg(ap, char*);
				break;

			case 'd':
			case 'u':
			case 'x':
			case 'X':
				if ( longarg )
					num = va_arg(ap, long);
				else
					num = va_arg(ap, int);
				if ( ch == 'd' && num < 0 )
				{
					sign = 1;
					num = -num;
				}
				if ( !longarg )
					num &= LONGtoINT;
				if ( ch == 'd' || ch == 'u' )
					str = _prt10(num, str);
				else
					str = _prt16(num, str, ch=='x' ? "abcdef" : "ABCDEF");
				break;

			default:
				str = "***";
				break;
			}
			leading = 0;
			len = strlen(str);
			if ( len > fmax )
				len = fmax;
			if ( len < fmin )
				leading = fmin - len - sign;
			nprinted += len + leading + sign;
			if ( sign && ( fill == '0' ) )
			{
				sign = 0;
				(*__putc)('-', dev);
			}
			if ( !ljust )
				for ( i=leading; i>0; i-- )
					(*__putc)(fill, dev);
			if ( sign )
				(*__putc)('-', dev);
			for ( i=len; i>0; i-- )
				(*__putc)(*str++, dev);
			if ( ljust )
				for ( i=leading; i>0; i-- )
					(*__putc)(fill, dev);
		}
	}
	return(nprinted);
}

static char *_prt10(unsigned long val, char *str)
{
	unsigned long tmp;

	str += __XPRT_MAXSTR;
	*str = '\0';
	do
	{
		tmp = val / 10L;
		*(--str) = (val - tmp*10L) + '0';
		val = tmp;
	} while ( val != 0 );
	return(str);
}

static char *_prt16(unsigned long val, char *str, char *hexdgt)
{
	uint8_t tmp;

	str += __XPRT_MAXSTR;
	*str = '\0';
	do
	{
		tmp = ((uint8_t)val) & 0xF;
		if ( tmp < 10 )
			tmp += '0';
		else
			tmp = hexdgt[tmp-10];
		*(--str) = tmp;
		val = val >> 4;
	} while ( val != 0 );
	return(str);
}

/* Workaround for broken/non-standard gcc behaviour
*/
void __stack_chk_fail(void)
{
}
