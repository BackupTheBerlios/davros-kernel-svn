/*	monitor.h - monitor definitions
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
 *	This file contains definitions for monitor.
 *
*/

#ifndef __mon_stdio_h
#define __mon_stdio_h

#define MAXLINE	1024

typedef void (*pokefunc_t)(memaddr_t a, uint8_t b);
#define SREC_EOF	1
#define SREC_BADTYP	-1
#define SREC_BADLEN	-2
#define SREC_NONHEX	-3
#define SREC_BADCK	-4

void monitor(char *prompt);

int process_s_record(char *line, pokefunc_t _poke);

int mprintf(char *fmt, ...);
char *mgets(char *buf, int max);

char *skipspaces(char *p);
int char2hex(char c);
maxword_t gethex(char **pp, int max);

#endif
