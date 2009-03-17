/*	stdio.h - stdio (subset of)
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
 *	This file contains the "stdio" functions
 *
*/

#ifndef __stdio_h
#define __stdio_h

#include "davros/kernel.h"

#ifndef NULL
#define NULL	((void *)0)
#endif

#define EOF (-1)

#define stdin	__davros_getstdin()
#define stdout	__davros_getstdout()
#define stderr	__davros_getstderr()

int fprintf(void *stream, const char *fmt, ...);
int fgetc(void *stream);
int fputc(int c, void *stream);

#define printf(f...)	fprintf(stdout, ## f)
#define getc(s)			fgetc(s)

#ifdef __STDIO_PRIVATE

/* Private stuff */

#include "stdarg.h"

typedef int (*__xprintf_putc)(int,void *);

int __xprintf(__xprintf_putc __putc, void *dev, const char *fmt, va_list ap);

/*	Functions for kprintf.
 *	kprintf is in the library
 *	kputc must be provided by the board drivers. It puts a single character
 *	to the console (in polled mode).
 *	kmode must be provided by the board drivers. It puts the console into
 *	the given mode and returns the old mode. The only specified value
 *	of mode is 0 (KPOLLED)
*/
int kprintf( const char *fmt, ...);
int kputc(int c, void *stream);
int kmode(int m);
#define KPOLLED 0
#define KINTR	1

#endif

#endif
