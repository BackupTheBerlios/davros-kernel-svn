/*	ctype.h - character types
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
 *	This file contains functions and macros to identify character types.
 *
*/

#ifndef __ctype_h
#define __ctype_h

#include <arch-cpudef.h>

/* Names for ASCII control codes */

#define NUL		0x00
#define SOH		0x01
#define STX		0x02
#define ETX		0x03
#define EOT		0x04
#define ENQ		0x05
#define ACK		0x06
#define BEL		0x07
#define BS		0x08
#define HT		0x09
#define LF		0x0a
#define VT		0x0b
#define FF		0x0c
#define CR		0x0d
#define SO		0x0e
#define SI		0x0f
#define DLE		0x10
#define DC1		0x11
#define DC2		0x12
#define DC3		0x13
#define DC4		0x14
#define NAK		0x15
#define SYN		0x16
#define ETB		0x17
#define CAN		0x18
#define EM		0x19
#define SUB		0x1A
#define ESC		0x1B
#define FS		0x1C
#define GS		0x1D
#define RS		0x1E
#define US		0x1F
#define SPACE	0x20
#define DEL		0x7f

#define	toupper(c)	(((c) >= 'a' && (c) <= 'z') ? ((c) - 0x20) : (c))
#define	tolower(c)	(((c) >= 'A' && (c) <= 'Z') ? ((c) + 0x20) : (c))

boolean_t isdigit(int c);
boolean_t isxdigit(int c);
boolean_t isspace(int c);
boolean_t isprint(int c);

#endif
