/*	forth.h
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
 *	Implements a forth execution environment
*/

#if !defined(__forth_h)
#define __forth_h

#include "qdftypes.h"

#ifdef FULLMEM

#define DICT_CHUNK	32	/* No of words of dictionary space to reserve each time */
#define DICT_SAFETY	4	/* Minimum gap between dictionary and data stack */
#define STACK_GAP	2	/* Minimum gap between data stack and return stack */
#define INITIAL_CHUNKS	4	/* No of chunks to reserve to start with */

#define push_data(x)    pushdata(forth,x)
#define pop_data(x)     popdata(forth,x)
#define rst_data()		(forth->dstk_p = forth->dstk_bot)
#define data_sp			forth->dstk_p
#define data_depth		(forth->dstk_p-forth->dstk_bot)
#define push_return(x)  pushretn(forth,x)
#define pop_return(x)   popretn(forth,x)
#define rst_return()	(forth->rstk_p = forth->rstk_bot)
#define return_sp		forth->rstk_p
#define return_depth	(forth->rstk_bot-forth->rstk_p)

#else

#include "stack.h"

#define	SZ_DATASTK	1024
#define	SZ_RETNSTK	1024

#define push_data(x)	push(&forth->data_stack,x)
#define pop_data(x)		pop(&forth->data_stack,x)
#define rst_data()		reset_stack(&forth->data_stack)
#define data_sp			(forth->data_stack.sp)
#define data_depth		(forth->data_stack.depth)
#define push_return(x)	push(&forth->return_stack,x)
#define pop_return(x)	pop(&forth->return_stack,x)
#define rst_return()	reset_stack(&forth->return_stack)
#define return_sp		(forth->return_stack.sp)
#define return_depth	(forth->return_stack.depth)

#endif

typedef struct dict_entry
{
	char *name;
	uint32_t type;
	void *address;
	int32_t value;
	struct dict_entry *next;
} dict_entry_t;

#define DICT_TYPE		0x00ff		/* entry type */
#define 	DICT_CONSTANT	0x01	/* value goes on stack */
#define 	DICT_VARIABLE	0x02	/* address goes on stack */
#define 	DICT_FUNCTION	0x03	/* executes function at address */
#define 	DICT_WORD		0x04	/* interpret FORTH word */
#define DICT_MODES		0xff00		/* mask for modes */
#define DICT_COMMAND	0x0100		/* can be called in command mode */
#define DICT_COMPILE	0x0200		/* can be called in compile mode */
#define DICT_RUN		0x0400		/* can be called in run mode */

typedef struct forth
{
#ifdef FULLMEM
	uint32_t *membot;				/* array of uint32_t */
	uint32_t memsize;				/* size in uint32_ts */
	uint32_t *rstk_bot;				/* first entry in return stack - contains 0xdeadbeef */
	uint32_t *rstk_p;				/* current return stack ptr - return stk grows down */
	uint32_t *dstk_bot;				/* first entry in data stack - contains 0xdeadbeef */
	uint32_t *dstk_p;				/* current data stack ptr - data stk grows up */
	uint32_t *dict_p;				/* next free dictionary entry */
#else
	stack_t data_stack;
	stack_t return_stack;
#endif
	dict_entry_t *dict;
	uint32_t mode;					/* command, run, compile */
	dict_entry_t *current_word;		/* run context */
	dict_entry_t **current_pos;		/* run context */
	uint32_t *iaddr;
	uint32_t *jaddr;
	uint32_t *frame;
} forth_t;

#define MAX_TOKEN	256

typedef int (*forth_function_t)(forth_t *forth, uint32_t param);

int init_forth(forth_t *forth);
int add_to_dict(forth_t *forth, char *name, uint32_t type, void *address, int32_t value);
int insert_in_dict(forth_t *forth, dict_entry_t *new_entry, char *name, uint32_t type,
						void *address, int32_t value);
dict_entry_t *find_in_dict(forth_t *forth, char *name);
int redefine_dict(forth_t *forth, dict_entry_t *entry, dict_entry_t *new_vals);
int do_forth(forth_t *forth);
int interpret_stream(forth_t *forth);
int read_token(forth_t *forth, char *buf);
int do_forth_word(forth_t *forth, dict_entry_t *word);
int do_dict_entry(forth_t *forth, dict_entry_t *e);

int add_standard_dict(forth_t *forth);

#ifdef FULLMEM

int pushdata(forth_t *forth, int32_t val);
int popdata(forth_t *forth, int32_t *dest);
int pushretn(forth_t *forth, int32_t val);
int popretn(forth_t *forth, int32_t *dest);

dict_entry_t *alloc_dict(forth_t *forth, int nwords);

#endif

#endif
