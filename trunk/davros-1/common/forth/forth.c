/*	forth.c
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
 *	Implements a forth execution environment
*/

#include "forth/qdftypes.h"
#include "forth/forth.h"
#if 0
#include "unistd.h"
#endif
#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#include "ctype.h"
#include "dbg.h"

#ifdef FIXSTK
uint32_t	dstk[SZ_DATASTK+1];
uint32_t	rstk[SZ_RETNSTK+1];
#endif

#ifdef FULLMEM

#ifdef __linux__
#define MEM_SIZE	8192	/* 8k words */
uint32_t	memory[MEM_SIZE];
#else
extern uint32_t *memory;
extern uint32_t mem_size;
#define MEM_SIZE	mem_size
#endif

#endif

int init_forth(forth_t *forth)
{
#ifdef FULLMEM
	forth->membot = memory;
	forth->memsize = MEM_SIZE;
	forth->rstk_bot = &forth->membot[forth->memsize-1];
	forth->rstk_p = forth->rstk_bot;
	*forth->rstk_p = 0xdeadbeef;
	forth->dstk_bot = &forth->membot[DICT_CHUNK*INITIAL_CHUNKS];
	forth->dstk_p = forth->dstk_bot;
	*forth->dstk_p = 0xdeadbeef;
	forth->dict_p = forth->membot;
#else
	int r;
	if ( (r = init_stack(&forth->data_stack, SZ_DATASTK)) < 0 )
		return (r);
	if ( (r = init_stack(&forth->return_stack, SZ_RETNSTK)) < 0 )
		return (r);
#ifdef FIXSTK
	forth->data_stack.store = dstk;
	forth->data_stack.size = SZ_DATASTK;
	reset_data();
	forth->return_stack.store = rstk;
	forth->return_stack.size = SZ_RETNSTK;
	reset_return();
#endif
#endif
	forth->mode = DICT_COMMAND;
	forth->dict = NULL;
	forth->current_word = NULL;
	forth->current_pos = NULL;
	forth->iaddr = NULL;
	forth->jaddr = NULL;
	forth->frame = NULL;
	return(0);
}

#ifdef FULLMEM
static uint32_t ptr_adj(forth_t *forth, void *ptr, void *limit, int offset)
{
	uint32_t result = (uint32_t)ptr;
	if ( ptr >= limit && ptr < (void *)forth->dict_p )
		result += offset;
	return(result);
}
#endif

int redefine_dict(forth_t *forth, dict_entry_t *entry, dict_entry_t *new_vals)
{
#ifdef FULLMEM
	/* This is an extremely nast piece of code. I ought to be
	 * hung, drawn and quartered for it.
	*/
	dict_entry_t *above, *e, *adj;
	uint32_t newsize, oldsize;
	int nbytes, nwords;
	uint32_t *dict_p, *src, *dest;
	/* Work out how much we need to move the newer dictionary
	 * entries by, and in which direction
	*/
	for ( above = new_vals; above != NULL && above->next != entry; above = above->next )
		;	/* Nothing */
	if ( above == NULL )
	{
		/* Panic! Internal error */
		fprintf(stderr, "!!! Internal error: entry to redefine doesn't exist\n");
		return(-1);
	}
	newsize = (uint32_t)forth->dict_p - (uint32_t)new_vals;
	oldsize = (uint32_t)above - (uint32_t)entry;
	nbytes = newsize - oldsize;
	nwords = nbytes / sizeof(uint32_t);
	if ( nbytes != 0 )
	{
		/* Might need some more dictionary space! */
		if ( nbytes > 0 )
		{
			dict_p = (uint32_t *)alloc_dict(forth, nbytes);
			if ( dict_p == NULL )
			{
				fprintf(stderr, "redefine_dict: alloc_dict() failed. Out of memory.\n");
				return (-1);
			}
		}
		else
		{
			dict_p = forth->dict_p;
			forth->dict_p -= nwords;
		}

		/* Adjust all the pointers in the dictionary */
		for ( e = new_vals, dest = dict_p;  e->next != NULL; )
		{
			adj = e;		/* We're working on this one! */
			e = e->next;	/* Remember the current address of the next */
			if ( (adj->type & DICT_TYPE) == DICT_WORD )
			{
				/* Adjust the addresses of all forth words in the procedure */
				src = (uint32_t *)adj->address;
				while ( src < dest )
				{
					if ( *src == 0 )
						src++;		/* Ignore literal constants */
					else
						*src = ptr_adj(forth, (void *)*src, above, nbytes);
					src++;
				}
			}
			if ( adj >= above )
			{
				/* Adjust the pointers in the dict_entry for these words */
				adj->next = (dict_entry_t *)ptr_adj(forth, adj->next, above, nbytes);
				adj->address = (void *)ptr_adj(forth, adj->address, above, nbytes);
				adj->name = (char *)ptr_adj(forth, adj->name, above, nbytes);
			}
			dest = (uint32_t *)adj;	/* Remember this one for next time round */
		}

		if ( nwords > 0 )
		{
			/* Size increase; copy up by nwords words */
			src = (uint32_t *)dict_p - 1;
			dest = src + nwords;
			while ( src >= (uint32_t *)above )
			{
				*dest-- = *src--;
				nwords--;
			}
			/* New word has also moved */
			new_vals = (dict_entry_t *)((uint32_t *)new_vals + nwords);
		}
		else
		{
			/* Size decrease; copy down by (-nwords) words */
			src = (uint32_t *)above;
			dest = src + nwords;
			while ( src < (uint32_t *)new_vals )
			{
				*dest++ = *src++;
				nwords++;
			}
		}
	}

    entry->type = new_vals->type;
    entry->value = new_vals->value;
    if ( (entry->type & DICT_TYPE) == DICT_VARIABLE )
        entry->address = &entry->value;
    else
        entry->address = new_vals->address;

	newsize = (newsize - sizeof(dict_entry_t))/sizeof(uint32_t);
	src = (uint32_t *)((uint32_t)new_vals + sizeof(dict_entry_t));
	dest = (uint32_t *)((uint32_t)entry + sizeof(dict_entry_t));
	while ( newsize > 0 )
	{
		*dest++ = *src++;
		newsize--;
	}
#else
	free(entry->name);
	if ( (entry->type & DICT_TYPE) == DICT_WORD )
		free(entry->address);
	entry->name = new_vals->name;
    entry->type = new_vals->type;
    entry->value = new_vals->value;
    if ( (entry->type & DICT_TYPE) == DICT_VARIABLE )
        entry->address = &entry->value;
    else
        entry->address = new_vals->address;
	free(new_vals);
#endif
	return (0);
}

int add_to_dict(forth_t *forth, char *name, uint32_t type, void *address, int32_t value)
{
	dict_entry_t *new_entry;
	int l;

	if ( name == NULL || (l = strlen(name)) <= 0 )
	{
		fprintf(stderr, "add_to_dict: NULL or empty name.\n");
		return (-1);
	}

#ifdef FULLMEM
	new_entry = alloc_dict(forth, (sizeof(dict_entry_t) + l + 1));
	if ( new_entry == NULL )
	{
		fprintf(stderr, "add_to_dict: alloc_dict() failed. Out of memory.\n");
		return (-1);
	}
	new_entry->name = (char *)(new_entry+1);
#else
	new_entry = calloc(1, sizeof(dict_entry_t));
	if ( new_entry == NULL )
	{
		fprintf(stderr, "add_to_dict: calloc(dict_entry_t) failed.\n");
		return (-1);
	}

	new_entry->name = calloc(1, l+1);
	if ( new_entry->name == NULL )
	{
		fprintf(stderr, "add_to_dict: calloc(name) failed.\n");
		free(new_entry);
		return (-1);
	}
#endif

	return(insert_in_dict(forth, new_entry, name, type, address, value));
}

int insert_in_dict(forth_t *forth, dict_entry_t *new_entry, char *name, uint32_t type,
						void *address, int32_t value)
{
	strcpy(new_entry->name, name);
	new_entry->type = type;

	/* default modes (if non specified) are command and run */
	if ( ( type & DICT_MODES ) == 0 )
		new_entry->type |= (DICT_COMMAND | DICT_RUN);

	new_entry->value = value;
	if ( type == DICT_VARIABLE )
		new_entry->address = &new_entry->value;
	else
		new_entry->address = address;
	new_entry->next = forth->dict;
	forth->dict = new_entry;
	return(0);
}

dict_entry_t *find_in_dict(forth_t *forth, char *name)
{
	dict_entry_t *e;

	for ( e = forth->dict;
		  e != NULL && strcasecmp(e->name, name) != 0;
		  e = e->next)
	{
		/* Nothing */
	}

	return (e);
}

int do_forth(forth_t *forth)
{
	/* FIXME: doesn't clean up! */
	int r;

#ifndef FULLMEM
	if ( forth == NULL )
		forth = calloc(1, sizeof(forth_t));
#endif
	if ( forth == NULL )
		return (-1);

	if ( (r = init_forth(forth)) < 0 )
		return(r);
	if ( (r = add_standard_dict(forth)) < 0 )
		return(r);

	r = interpret_stream(forth);

	return(r);
}

int interpret_stream(forth_t *forth)	/* Better name */
{
	dict_entry_t *e;
	char token[MAX_TOKEN+1];
	uint32_t v;
	char *p;

	while ( read_token(forth, token) >= 0 )
	{
	 	DBG(20, "token: %s", token);
		if ( (e = find_in_dict(forth, token)) == NULL )
		{
			/* Not defined - is it a number? */
			v = strtoul(token, &p, 0);
			if ( p == token )
			{
				/* No, it isn't a number! */
				fprintf(stderr, "!!! Unknown word \"%s\"\n", token);
			}
			else
				push_data(v);
		}
		else
		{
			/* It's a defined word - so do it! */
			do_dict_entry(forth, e);
		}
	}
	return(0);
}

int do_dict_entry(forth_t *forth, dict_entry_t *e)
{
	int r;

	switch ( e->type & DICT_TYPE )
	{
	case DICT_CONSTANT:
		if ( (r = push_data(e->value)) < 0 )
			fprintf(stderr, "!!! Data stack overflow\n");
		break;
	case DICT_VARIABLE:
		if ( (r = push_data((int32_t)e->address)) < 0 )
			fprintf(stderr, "!!! Data stack overflow\n");
		break;
	case DICT_FUNCTION:
		r = ((forth_function_t)e->address)(forth, e->value);
		break;
	case DICT_WORD:
		r = do_forth_word(forth, e);
		break;
	default:
		fprintf(stderr, "Unknown dictionary entry type %d!\n", e->type);
		r = -1;
		break;
	}
	return(r);
}

int read_token(forth_t *forth, char *buf)
{
	int n = 0;
	char *p = buf;
	int c;

	*p = '\0';
	while ( (c = getc(stdin)) != EOF )
	{
		if ( isspace(c) )
		{
			if ( n > 0 )
				return(n);
			/* else drop the character */
		}
		else
		if ( isprint(c) )
		{
			if ( n < MAX_TOKEN )
			{
				*p++ = c;
				*p = '\0';
				n++;
			}
		}
		/* else drop the character */
	}
	if ( n == 0 )
		return(-1);
	return(n);
}

char *modenames[] = { "Command", "Compile", "ERROR", "Run" };

int do_forth_word(forth_t *forth, dict_entry_t *word)
{
	int r = 0;
	dict_entry_t *e;
	uint32_t *save_sp;

	if ( word == NULL || ( word->type & forth->mode & DICT_MODES ) == 0 )
	{
		fprintf(stderr, "%s cannot be used in %s mode\n", word->name,
								modenames[((forth->mode&DICT_MODES)>>8)-1]);
		return(-1);
	}

	if ( (forth->mode & DICT_MODES) == DICT_COMMAND )
	{
		/* Initialise the run environment */
		forth->current_word = NULL;
		forth->current_pos = NULL;
		forth->iaddr = NULL;
		forth->jaddr = NULL;
		forth->frame = NULL;
		rst_return();
	}

	save_sp = return_sp;
	if ( (r = push_return((int32_t)forth->current_word)) < 0 ||
		 (r = push_return((int32_t)forth->current_pos)) < 0 ||
		 (r = push_return((int32_t)forth->iaddr)) < 0 ||
		 (r = push_return((int32_t)forth->jaddr)) < 0 ||
		 (r = push_return((int32_t)forth->frame)) < 0 )
	{
		fprintf(stderr, "!!! Return stack overflow\n");
		return_sp = save_sp;
		return(r);
	}
	DBG(13, "Frame ptr was 0x%08x, setting to 0x%08x\n", forth->frame, return_sp);
	forth->frame = return_sp;
	forth->current_word = word;
	forth->current_pos = word->address;
	if ( forth->mode & DICT_COMMAND )
	{
		forth->mode = (forth->mode & ~DICT_MODES) | DICT_RUN;
		while ( r == 0 && forth->current_word != NULL )
		{
			DBG(14, "BEFORE: Data sp = 0x%08x, depth = %d\n", data_sp, data_depth);
			e = *forth->current_pos++;
			if ( e == NULL )
			{
				/* Literal value */
				if ( ( r = push_data((uint32_t)(*forth->current_pos++)) ) < 0 )
				{
					fprintf(stderr, "!!! Stack overflow\n");
				}
			}
			else
			{
				DBG(10, "Calling do_dict_entry(%s)", e->name);
				r = do_dict_entry(forth, e);
			}
			DBG(14, "AFTER: Data sp = 0x%08x, depth = %d\n", data_sp, data_depth);
		}
		forth->mode = (forth->mode & ~DICT_MODES) | DICT_COMMAND;
	}
	return(r);
}

#ifdef FULLMEM

/* Data stack grows UP from end of dictionary, return stack grows DOWN from
 * top of memory. This way, the return stack never moves, which is important
 * since we store the address of stack frames etc.
*/

int pushdata(forth_t *forth, int32_t val)
{
	if ( forth->dstk_p >= forth->rstk_p - STACK_GAP )
		return(-1);
	forth->dstk_p++;
	*forth->dstk_p = val;
	DBG(11, "Pushed 0x%08x on data stack, depth now %d\n", val, data_depth);
	return (0);
}

int popdata(forth_t *forth, int32_t *dest)
{
	*dest = *forth->dstk_p;
	if ( forth->dstk_p <= forth->dstk_bot )
		return(-1);
	forth->dstk_p--;
	DBG(11, "Popped 0x%08x off data stack, depth now %d\n", *dest, data_depth);
	return(0);
}

int pushretn(forth_t *forth, int32_t val)
{
	if ( forth->dstk_p >= forth->rstk_p - STACK_GAP )
		return(-1);
	forth->rstk_p--;
	*forth->rstk_p = val;
	return (0);
}

int popretn(forth_t *forth, int32_t *dest)
{
	*dest = *forth->rstk_p;
	if ( forth->rstk_p >= forth->rstk_bot )
		return(-1);
	forth->rstk_p++;
	return (0);
}

dict_entry_t *alloc_dict(forth_t *forth, int nbytes)
{
	int nwords = (nbytes + sizeof(uint32_t) - 1) / sizeof(uint32_t);
	int nfree = forth->dstk_bot - forth->dict_p;
	int n;
	uint32_t *new_dstk_bot;
	uint32_t *new_dstk_p;
	uint32_t *s, *d;

	DBG(12,"alloc_dict: request %d bytes, %d words, %d free\n", nbytes, nwords, nfree);
	
	if ( nfree < nwords + DICT_SAFETY )
	{
		/* Not enough space - better steal more from stack */
		n = (((nwords + DICT_SAFETY - nfree + DICT_CHUNK - 1)/DICT_CHUNK))*DICT_CHUNK;
		DBG(12, "Reserving %d more words in dictionary\n", n);
		new_dstk_bot = forth->dstk_bot + n;
		new_dstk_p = forth->dstk_p + n;
		if ( new_dstk_p >= forth->rstk_p - STACK_GAP )
			return(NULL);		/* Not enough room */
		s = forth->dstk_p;
		d = new_dstk_p;
		while ( d >= new_dstk_bot )
			*d-- = *s--;
		forth->dstk_p = new_dstk_p;
		forth->dstk_bot = new_dstk_bot;
	}
	s = forth->dict_p;
	forth->dict_p += nwords;
	return((dict_entry_t *)s);
}

#endif
