/*	start-qdf.c - start a qdf compiler/interpreter
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
 *	This file contains the code that starts a qdf compiler/interpreter
 *	as a Davros process.
 *
*/

#include "davros/kernel.h"
#include "forth/forth.h"
#include <ctype.h>
#include <stdio.h>

#define __MEM_SIZE	8192	/* 8k words */
uint32_t	__memory[__MEM_SIZE];
uint32_t *memory = __memory;
uint32_t mem_size = __MEM_SIZE;
forth_t forth_env;

int forth_process(int argc, int *argv)
{
	fprintf(stdout, "\n");
	fprintf(stdout, "qdf version 0.1, copyright 2001 David Haworth\n");
	fprintf(stdout, "qdf comes with ABSOLUTELY NO WARRANTY. It is free software,\n");
	fprintf(stdout, "and you are welcome to redistribute it under certain conditions.\n");
	fprintf(stdout, "Please read the file COPYING for details.\n");
	fprintf(stdout, "\n");

	for (;;)
		do_forth(&forth_env);

	return 0;
}

/*
 *	__user_init() - start the process
 *
 *  This function is from davros startup. It opens the tty
 *	and then starts the qdf task.
 *
*/
void __user_init(void)
{
	__davros_device_t *tty;
	__davros_process_t *p;

	tty = __davros_open("/dev/tty/0", 0);

	p = __davros_create
	(	forth_process,
		2000,
		10,
		"qdf",
		tty,
		tty,
		tty,
		0,
		NULL
	);
	__davros_resume(p, 1);
}

/* fgetc function for qdf */
static char line[1026] = { '\0' };
static char *next = line;
static int len = 0;
static int tty_cooked = 1;

int fgetc(void *stream)
{
	int loop;
	char c;

	if ( tty_cooked )
	{
		if ( *next == '\0' )
		{
			next = line;
			len = 0;
			loop = 1;
			while ( loop )
			{
				c = __davros_getc((__davros_device_t *)stream);
				if ( c == BS )
				{
					if ( len > 0 )
					{
						len--;
						next--;
						fputc(BS, stream);
						fputc(' ', stream);
						fputc(BS, stream);
					}
					else
						fputc(BEL, stream);
				}
				else
				if ( c == '\r' || c == '\n' )
				{
					*next++ = '\n';
					*next = '\0';
					next = line;
					loop = 0;
					fputc('\n', stream);
				}
				else
				if ( len < 1024 )
				{
					*next++ = c;
					len++;
					fputc(c, stream);
				}
				else
					fputc(BEL, stream);
			}
		}
		return(*next++);
	}
	else
		return(__davros_getc((__davros_device_t *)stream));
}
