/*	stddict.c
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
 *	Implements the standard FORTH dictionary.
*/

#ifndef FULLMEM
#include "unistd.h"
#endif
#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#include "forth/forth.h"
#include "dbg.h"

dict_entry_t *_if;
dict_entry_t *_else;
dict_entry_t *_then;
dict_entry_t *_while;
dict_entry_t *_repeat;

/* This is a quick way to define a function with standard debugging output.
   You still need the opening { after the DEFFUN call, plus you need 2 (two)
   closing }s at the end!
*/
#define DEFFUN(x)	int x(forth_t *forth, int32_t param) \
					{ \
						DBG(30, "Called %s(param = %d)", __PRETTY_FUNCTION__, param);

#ifdef DEBUGGING
/* forth_dbglvl - sets debug level */
DEFFUN(forth_dbglvl)
{
	int32_t v;
	int r;

	if ( (r =  pop_data(&v)) < 0 )
	{
		fprintf(stderr, "!!! Stack underflow!\n");
		return (r);
	}
	__dbglvl = v;
	return (0);
}}
#endif

/* forth_dot - prints top of stack */
DEFFUN(forth_dot)
{
	int32_t v;
	int r;

	if ( (r =  pop_data(&v)) < 0 )
	{
		fprintf(stderr, "!!! Stack underflow!\n");
		return (r);
	}
	if ( param == 0 )
		printf("%d ", v);
	else
		printf("%u ", v);
	return (0);
}}

/* forth_cr - prints newline on output */
DEFFUN(forth_cr)
{
	printf("\n");
	return(0);
}}

/* forth_1op - miscellaneous unary operations */
DEFFUN(forth_1op)
{
	int r;

	if ( data_depth < 1 )
	{
		fprintf(stderr, "!!! Stack underflow!\n");
		return (r);
	}

	switch (param)
	{
	case 0:		/* 0< */
		data_sp[0] = (data_sp[0] < 0);
		break;
	case 1:		/* 0= */
		data_sp[0] = (data_sp[0] == 0);
		break;
	case 2:		/* 0> */
		data_sp[0] = (data_sp[0] > 0);
		break;
	case 3:		/* 1+ */
		data_sp[0]++;
		break;
	case 4:		/* 1- */
		data_sp[0]--;
		break;
	case 5:		/* 2+ */
		data_sp[0] += 2;
		break;
	case 6:		/* 2- */
		data_sp[0] -= 2;
		break;
	case 7:		/* @ */
		data_sp[0] = *(int32_t *)data_sp[0];
		break;
	case 8:		/* abs */
		if ( data_sp[0] < 0 )
			data_sp[0] = -data_sp[0];
		break;
	case 9:		/* negate */
		data_sp[0] = -data_sp[0];
		break;
	}
	return (0);
}}

/* forth_2op - miscellaneous binary operations */
DEFFUN(forth_2op)
{
	int32_t v;
	int r;

	if ( data_depth < 2 )
	{
		fprintf(stderr, "!!! Stack underflow!\n");
		return (r);
	}

	pop_data(&v);
	switch (param)
	{
	case 0:		/* + */
		data_sp[0] += v;
		break;
	case 1:		/* - */
		data_sp[0] -= v;
		break;
	case 2:		/* * */
		data_sp[0] *= v;
		break;
	case 3:		/* / */
		data_sp[0] /= v;
		break;
	case 4:		/* AND */
		data_sp[0] = data_sp[0] & v;
		break;
	case 5:		/* OR */
		data_sp[0] = data_sp[0] | v;
		break;
	case 6:		/* XOR */
		data_sp[0] = data_sp[0] ^ v;
		break;
	case 7:		/* < */
		data_sp[0] = (data_sp[0] < v);
		break;
	case 8:		/* = */
		data_sp[0] = (data_sp[0] == v);
		break;
	case 9:		/* > */
		data_sp[0] = (data_sp[0] > v);
		break;
	case 10:	/* max */
		if ( data_sp[0] < v)
			data_sp[0] = v;
		break;
	case 11:	/* min */
		if ( data_sp[0] > v)
			data_sp[0] = v;
		break;
	case 12:	/* mod */
		data_sp[0] = (data_sp[0] % v);
		break;
	}
	return (0);
}}

/* forth_drop - pop stack & discard */
DEFFUN(forth_drop)
{
	int32_t v;
	int r;

	if ( (r =  pop_data(&v)) < 0 )
	{
		fprintf(stderr, "!!! Stack underflow!\n");
		return (r);
	}

	return (0);
}}

/* forth_dup - duplicates top of stack (perhaps conditionally) */
DEFFUN(forth_dup)
{
	int32_t v;
	int r;

	if ( data_depth < 1 )
	{
		fprintf(stderr, "!!! Stack underflow!\n");
		return (r);
	}

	v = data_sp[0];
	if ( param == 0 || v != 0 )
	{
		if ( (r = push_data(v)) < 0 )
		{
			fprintf(stderr, "!!! Stack overflow!\n");
			return (r);
		}
	}
	return (0);
}}

/* forth_2op2 - binary operations with more than 1 result */
DEFFUN(forth_2op2)
{
	int32_t v;
	int r;

	if ( data_depth < 2 )
	{
		fprintf(stderr, "!!! Stack underflow!\n");
		return (r);
	}
#ifdef FULLMEM
	v = *(data_sp-1);
#else
	v = data_sp[1];
#endif
	switch (param)
	{
	case 0:		/* swap */
#ifdef FULLMEM
		*(data_sp-1) = data_sp[0];
#else
		data_sp[1] = data_sp[0];
#endif
		data_sp[0] = v;
		break;
	case 1:		/* over */
		if ( (r = push_data(v)) < 0 )
		{
			fprintf(stderr, "!!! Stack overflow!\n");
			return (r);
		}
		break;
	}
	return (0);
}}

/* forth_store - write to variable */
DEFFUN(forth_store)
{
	int32_t v, *addr;
	int r;

	if ( data_depth < 2 )
	{
		fprintf(stderr, "!!! Stack underflow!\n");
		return (r);
	}

	pop_data((int32_t *)&addr);
	pop_data(&v);
	*addr = v;
	return (0);
}}

/* forth_number - defines a variable or constant */
DEFFUN(forth_number)
{
	int32_t v;
	int r;
	char name[MAX_TOKEN+1];

	if ( (r =  pop_data(&v)) < 0 )
	{
		fprintf(stderr, "!!! Stack underflow!\n");
		return (r);
	}

	if ( (r = read_token(forth, name)) <= 0 )
	{
		return (r);
	}

	if ( param == 0 )
		r = add_to_dict(forth, name, DICT_CONSTANT, NULL, v);
	else
		r = add_to_dict(forth, name, DICT_VARIABLE, NULL, v);
	return (0);
}}

/* forth_forget - clears dictionary entries */
DEFFUN(forth_forget)
{
	int r;
	dict_entry_t *e;
#ifndef FULLMEM
	dict_entry_t *junk;
#endif
	char name[MAX_TOKEN+1];

	if ( (r = read_token(forth, name)) <= 0 )
	{
		return (r);
	}

	e = find_in_dict(forth, name);
	if ( e == NULL )
	{
		fprintf(stderr, "!!! %s not in dictionary!\n", name);
		return (-1);
	}

#ifdef FULLMEM
	forth->dict = e->next;
	forth->dict_p = (uint32_t *)e;
/* FIXME: do we want to move the data stack down? */
#else
	do
	{
		junk = forth->dict;
		forth->dict = junk->next;
		free(junk);
	} while ( junk != e );
#endif

	return (0);
}}

/* forth_redefine - redefines a dictionary entry */
DEFFUN(forth_redefine)
{
	int r;
	dict_entry_t *e, *latest;
	char name[MAX_TOKEN+1];

	if ( (r = read_token(forth, name)) <= 0 )
	{
		return (r);
	}

	latest = forth->dict;
	if ( latest != NULL )
		forth->dict = latest->next;

	e = find_in_dict(forth, name);
	if ( e == NULL )
	{
		fprintf(stderr, "!!! %s not in dictionary!\n", name);
		forth->dict = latest;
		return (-1);
	}

	if ( redefine_dict(forth, e, latest) != 0 )
	{
		forth->dict = latest;
		return(-1);
	}

	return (0);
}}

/* forth_vlist - lists the dictionary */
DEFFUN(forth_vlist)
{
	dict_entry_t *e;
	int n,l;

	n = 0;
	for ( e = forth->dict;
		  e != NULL;
		  e = e->next )
	{
		l = strlen(e->name);
		if ( n == 0 )
		{
			printf("%s", e->name);
			n = l;
		}
		else
		if ( (n += (l+1)) > 80 )		/* Crude */
		{
			printf("\n%s", e->name);
			n = l;
		}
		else
		{
			printf(" %s", e->name);
		}
	}
	printf("\n");
	return (0);
}}

/* forth_compile - compiles a forth subroutine */
DEFFUN(forth_compile)
{
	dict_entry_t *e;
	char name[MAX_TOKEN+1];
	char token[MAX_TOKEN+1];
	uint32_t len = 0;
	uint32_t v;
	char *p;
	dict_entry_t **code;
	int r;
	uint32_t save_mode;
#ifdef FULLMEM
	dict_entry_t *entry;
	uint32_t *save_dp;
#else
	uint32_t size = 1024;
#endif

	if ( (forth->mode & DICT_MODES) != DICT_COMMAND )
	{
		fprintf(stderr, "!!! Must be in command mode\n");
		return(-1);
	}

	if ( read_token(forth, name) < 0 )
	{
		fprintf(stderr, "!!! End of input while compiling word\n");
		return(-1);
	}
#ifdef FULLMEM
	/* Remember dict. ptr for error recovery */
	save_dp = forth->dict_p;
	len = strlen(name);
	entry = alloc_dict(forth, (sizeof(dict_entry_t) + len + 1));
	if ( entry == NULL )
	{
		fprintf(stderr, "!!! Can't allocate more dictionary\n");
		forth->dict_p = save_dp;
		return(-1);
	}
	entry->name = (char *)(entry+1);
	code = (dict_entry_t **)forth->dict_p;
	len = 0;
	len = 0;
#else
	code = calloc(size, sizeof(dict_entry_t *));
	if ( code == NULL )
	{
		fprintf(stderr, "!!! Can't allocate memory\n");
		return(-1);
	}
#endif
	save_mode = forth->mode;
	forth->mode = (forth->mode & ~DICT_MODES) | DICT_COMPILE;
	while ( (forth->mode & DICT_MODES) == DICT_COMPILE &&
			read_token(forth, token) >= 0 )
	{
#ifndef FULLMEM
		if ( len >= size )
		{
			/* FIXME: code buffer needs to grow */
			fprintf(stderr, "!!! Function too big\n");
			forth->mode = (forth->mode & ~DICT_MODES) | DICT_COMMAND;
			free(code);
			forth->mode = save_mode;
			return(-1);
		}
#endif
		if ( (e = find_in_dict(forth, token)) == NULL )
		{
			/* Not defined - is it a number? */
			v = strtoul(token, &p, 0);
			if ( p == token )
			{
				/* No, it isn't a number! */
				fprintf(stderr, "!!! Unknown word \"%s\"\n", token);
				forth->dict_p = save_dp;
				forth->mode = save_mode;
				return(-1);
			}
#ifdef FULLMEM
			if ( alloc_dict(forth, 2 * sizeof(dict_entry_t *)) == NULL )
			{
				fprintf(stderr, "!!! Can't allocate more dictionary\n");
				forth->dict_p = save_dp;
				forth->mode = save_mode;
				return(-1);
			}
#endif
			code[len] = NULL;
			len++;
			code[len] = (dict_entry_t *)v;
			len++;
		}
		else
		{
			/* It's a defined word - so store it! */
#ifdef FULLMEM
			if ( alloc_dict(forth, sizeof(dict_entry_t *)) == NULL )
			{
				fprintf(stderr, "!!! Can't allocate more dictionary\n");
				forth->dict_p = save_dp;
				forth->mode = save_mode;
				return(-1);
			}
#endif
			code[len] = e;
			if ( e->type & DICT_COMPILE )
				do_dict_entry(forth, e);
			len++;
		}
	}
	if ( (forth->mode & DICT_MODES) == DICT_COMPILE )
	{
		fprintf(stderr, "!!! End of file in compile mode\n");
		forth->mode = save_mode;
#ifdef FULLMEM
		forth->dict_p = save_dp;
#else
		free(code);
#endif
		return(-1);
	}
#ifdef FULLMEM
	r = insert_in_dict(forth, entry, name, DICT_WORD, code, 0);
#else
	r = add_to_dict(forth, name, DICT_WORD, code, 0);
#endif
	if ( r < 0 )
	{
		fprintf(stderr, "!!! Error adding word to dictionary\n");
#ifdef FULLMEM
		forth->dict_p = save_dp;
#else
		free(code);
#endif
		return(r);
	}
	return (0);
}}

/* forth_return - return from a forth subroutine */
DEFFUN(forth_return)
{
	uint32_t m;
	int r;

	if ( (m = forth->mode & DICT_MODES) == DICT_COMPILE )
	{
		if ( param == 0 )	/* leave compile mode if command is ";" */
			forth->mode = (forth->mode & ~DICT_MODES) | DICT_COMMAND;
	}
	else
	if ( m == DICT_RUN )
    {
		/* Discard any stacked data, loop counts, etc */
		DBG(13, "Return SP was 0x%08x, restoring frame 0x%08x\n", return_sp, forth->frame);
		DBG(20, "Data SP = 0x%08x\n", data_sp);
		return_sp = forth->frame;
		DBG(20, "Data SP = 0x%08x\n", data_sp);

		/* Pop the stack frame */
		if ( (r = pop_return((int32_t *)&forth->frame)) < 0 ||
			 (r = pop_return((int32_t *)&forth->jaddr)) < 0 ||
			 (r = pop_return((int32_t *)&forth->iaddr)) < 0 ||
			 (r = pop_return((int32_t *)&forth->current_pos)) < 0 ||
			 (r = pop_return((int32_t *)&forth->current_word)) < 0 )
		{
			fprintf(stderr, "!!! Return stack underflow\n");
			return(r);
		}
		DBG(20, "Data SP = 0x%08x\n", data_sp);
		DBG(13, "New frame ptr is 0x%08x\n", forth->frame);
    }
	else
	{
		fprintf(stderr, "!!! Mode = %x: May only be used in a function\n", m);
		return(-1);
	}
	return (0);
}}

/* forth_if - conditional statement */
DEFFUN(forth_if)
{
	uint32_t m, cond;
	int r, depth, skipping;
	dict_entry_t *e;

	if ( (m = forth->mode & DICT_MODES) == DICT_COMPILE )
	{
		/* FIXME: nesting checks to do */
	}
	else
	if ( m == DICT_RUN )
    {
		if ( (r = pop_data(&cond)) < 0 )
		{
			fprintf(stderr, "!!! Stack underflow\n");
			return(r);
		}
		if ( cond )
		{
			/* Nothing to do! We continue execution as normal */
		}
		else
		{
			/* We need to skip statements until the matching else or then.
			   However, it's more complicated than that, because we must
			   be aware of nested if statements. We must also ignore the
			   extra data field of a literal entry. */
			depth = 0;
			skipping = 1;
			while ( skipping )
			{
				e = *forth->current_pos++;
				if ( e == NULL )
					forth->current_pos++;	/* skip the data field */
				else
				if ( e == _if )
					depth++;				/* nested if */
				else
				if ( e == _else )
				{
					if ( depth <= 0 )
						skipping = 0;		/* pos = entry after else */
				}
				else
				if ( e == _then )
				{
					if ( depth <= 0 )
						skipping = 0;		/* pos = entry after else */
					else
						depth--;
				}
			}
		}
	}
	else
	{
		fprintf(stderr, "!!! Mode = %x: May only be used in a function\n", m);
		return(-1);
	}
	return (0);
}}

/* forth_else - conditional statement */
DEFFUN(forth_else)
{
	uint32_t m;
	int depth, skipping;
	dict_entry_t *e;

	if ( (m = forth->mode & DICT_MODES) == DICT_COMPILE )
	{
		/* FIXME: nesting checks to do */
	}
	else
	if ( m == DICT_RUN )
    {
		/* We only execute the "else" word if the "if" condition was
		   TRUE, so here we simply skip to the "then". Same precautions
		   as for "if", except we needn't consider "else".
		*/
		depth = 0;
		skipping = 1;
		while ( skipping )
		{
			e = *forth->current_pos++;
			if ( e == NULL )
				forth->current_pos++;	/* skip the data field */
			else
			if ( e == _if )
				depth++;				/* nested if */
			else
			if ( e == _then )
			{
				if ( depth <= 0 )
					skipping = 0;		/* pos = entry after else */
				else
					depth--;
			}
		}
	}
	else
	{
		fprintf(stderr, "!!! Mode = %x: May only be used in a function\n", m);
		return(-1);
	}
	return (0);
}}

/* forth_then - conditional statement */
DEFFUN(forth_then)
{
	uint32_t m;

	if ( (m = forth->mode & DICT_MODES) == DICT_COMPILE )
	{
		/* FIXME: nesting checks to do */
	}
	else
	if ( m == DICT_RUN )
    {
		/* The "then" statement is just a marker for "if" or "then" to
		   skip to. It doesn't do anything. However, when the condition
		   is FALSE and there's an "else", the "then" statement will
		   actually get executed, so we must gracefully do nothing. */
	}
	else
	{
		fprintf(stderr, "!!! Mode = %x: May only be used in a function\n", m);
		return(-1);
	}
	return (0);
}}

/* forth_begin - start of a loop */
DEFFUN(forth_begin)
{
	uint32_t m;
	int r;
	uint32_t first, limit;

	if ( (m = forth->mode & DICT_MODES) == DICT_COMPILE )
	{
		/* FIXME: nesting checks to do */
	}
	else
	if ( m == DICT_RUN )
    {
		if ( (r = push_return((uint32_t)forth->current_pos)) < 0 )
		{
			fprintf(stderr, "!!! Return stack overflow\n");
			return(r);
		}

		switch ( param )
		{
		case 0:		/* begin */
			/* Nothing else to do */
			break;
		case 1:		/* do */
			if ( (r = pop_data(&first)) < 0 ||
				 (r = pop_data(&limit)) < 0 )
			{
				fprintf(stderr, "!!! Stack underflow\n");
				return(r);
			}
			if ( (r = push_return(limit)) < 0 ||
				 (r = push_return(first)) < 0 ||
				 (r = push_return((uint32_t)forth->jaddr)) < 0 )
			{
				fprintf(stderr, "!!! Return stack overflow\n");
				return(r);
			}
			forth->jaddr = forth->iaddr;
			forth->iaddr = return_sp;
			break;
		}
	}
	else
	{
		fprintf(stderr, "!!! Mode = %x: May only be used in a function\n", m);
		return(-1);
	}
	
	return (0);
}}

/* forth_until - condition or end statement of a loop
	param == 0 --> until
			 1 --> while
			 2 --> repeat
			 3 --> loop
			 4 --> +loop
			 5 --> leave
*/
DEFFUN(forth_until)
{
	int r;
	uint32_t m, cond;
	int depth, skipping;
	dict_entry_t *e;

	if ( (m = forth->mode & DICT_MODES) == DICT_COMPILE )
	{
		/* FIXME: nesting checks to do */
	}
	else
	if ( m == DICT_RUN )
    {
		if ( param == 0  || param == 1 || param == 4 )
		{
			if ( (r =  pop_data(&cond)) < 0 )
			{
				fprintf(stderr, "!!! Stack underflow!\n");
				return (r);
			}
		}
		else
			cond = 1;

		if ( return_depth < 1 )
		{
			fprintf(stderr, "!!! Return stack underflow\n");
			return (r);
		}

		switch ( param )
		{
		case 0:		/* until */
			if ( cond )
			{
				/* The loop terminates. Pop the begin address off the return
				   stack and discard it. */
				pop_return(&cond);
				break;
			}
			/* else ... fall through */
		case 2:		/* repeat */
			/* The loop goes around again. Go back to the begin address */
			forth->current_pos = (dict_entry_t **)return_sp[0];
			break;
		case 1:		/* while */
			if ( cond )
			{
				/* Continue execution. The "repeat" does the loop */
			}
			else
			{
				/* The loop terminates. Pop the begin address off the return
				   stack and discard it. */
				pop_return(&cond);

				/* Now we skip all the statments up to and including the
				   matching "repeat", taking any nesting into account.
				   We don't look for a "begin", because that could be
				   terminated with "until". We just look for the "while". */
				depth = 0;
				skipping = 1;
				while ( skipping )
				{
					e = *forth->current_pos++;
					if ( e == NULL )
						forth->current_pos++;	/* skip the data field */
					else
					if ( e == _while )
						depth++;				/* nested while loop */
					else
					if ( e == _repeat )
					{
						if ( depth <= 0 )
							skipping = 0;		/* pos = entry after repeat */
						else
							depth--;
					}
				}
			}
			break;
		case 3:		/* loop */
		case 4:		/* +loop */
			if ( forth->iaddr == NULL )
			{
				fprintf(stderr, "!!! loop/+loop with no matching \"do\"\n");
				return(-1);
			}
			forth->iaddr[1] += cond;
			if ( cond < 0 )
				cond = ( forth->iaddr[1] <= forth->iaddr[2] );
			else
				cond = ( forth->iaddr[1] >= forth->iaddr[2] );
			if ( !cond )
			{
				/* The loop goes around again. Go back to the begin address */
				forth->current_pos = (dict_entry_t **)return_sp[3];
				break;
			}
			/* else ... fall through */
		case 5:		/* leave */
			/* Move jaddr to iaddr, recover old jaddr from stack. Then
			   pop & discard count, limit & loop address */
			forth->iaddr = forth->jaddr;
			if ( (r = pop_return((uint32_t *)&forth->jaddr)) < 0 ||
				 (r = pop_return(&cond)) < 0 ||
				 (r = pop_return(&cond)) < 0 ||
				 (r = pop_return(&cond)) < 0 )
			{
				fprintf(stderr, "!!! Return stack underflow\n");
				return(r);
			}
			break;
		}
	}
	else
	{
		fprintf(stderr, "!!! Mode = %x: May only be used in a function\n", m);
		return(-1);
	}
	
	return (0);
}}

/* forth_loopct - get loop count or limit values */
DEFFUN(forth_loopct)
{
	uint32_t *ptr;
	int offset;
	int r;

	switch (param)
	{
	case 0:		/* i */
		ptr = forth->iaddr;
		offset = 1;
		break;
	case 1:		/* i' */
		ptr = forth->iaddr;
		offset = 2;
		break;
	case 2:		/* j */
		ptr = forth->jaddr;
		offset = 1;
		break;
	case 3:		/* j' */
		ptr = forth->jaddr;
		offset = 2;
		break;
	default:
		return(0);
		break;
	}

	if ( ptr == NULL )
	{
		fprintf(stderr, "!!! Cannot get loop counter - no loop\n");
		return(-1);
	}

	if ( (r = push_data(ptr[offset])) < 0 )
	{
		fprintf(stderr, "!!! Stack overflow\n");
		return(r);
	}

	return(0);
}}

/* forth_loopct - pop dstack, push rstack */
DEFFUN(forth_to_rstack)
{
	uint32_t val, m;
	int r;

	if ( (m = forth->mode & DICT_MODES) == DICT_COMPILE )
	{
		/* FIXME: nesting checks to do */
	}
	else
	if ( m == DICT_RUN )
    {
		if ( (r = pop_data(&val)) < 0 )
		{
			fprintf(stderr, "!!! Stack underflow\n");
			return(r);
		}
		if ( (r = push_return(val)) < 0 )
		{
			fprintf(stderr, "!!! Return stack overflow\n");
			return(r);
		}
	}
	return(0);
}}

/* forth_from_rstack - pop rstack, push dstack */
DEFFUN(forth_from_rstack)
{
	uint32_t val, m;
	int r;

	if ( (m = forth->mode & DICT_MODES) == DICT_COMPILE )
	{
		/* FIXME: nesting checks to do */
	}
	else
	if ( m == DICT_RUN )
    {
		if ( (r = pop_return(&val)) < 0 )
		{
			fprintf(stderr, "!!! Return stack underflow\n");
			return(r);
		}
		if ( (r = push_data(val)) < 0 )
		{
			fprintf(stderr, "!!! Stack overflow\n");
			return(r);
		}
	}
	return(0);
}}

#ifdef VARSTK
/* forth_stacksize - resize a stack. COMMAND MODE ONLY - destroys stack */
DEFFUN(forth_stacksize)
{
	uint32_t newsz;
	int r;

	if ( (r = pop_data(&newsz)) < 0 )
	{
		fprintf(stderr, "!!! Stack underflow\n");
		return(r);
	}
	if ( newsz < 1024 )
	{
		fprintf(stderr, "!!! New stack size is too small\n");
		return(r);
	}
	if ( newsz >= 0x80000000 )
	{
		fprintf(stderr, "!!! New stack size is too large\n");
		return(r);
	}
	r = stack_resize(param == 0 ? &forth->data_stack : &forth->return_stack, newsz);
	if ( r != 0 )
	{
		fprintf(stderr, "!!! Insufficient memory for new stack\n");
		return(r);
	}
	return(0);
}}
#endif

/* forth_stackdump - dump a stack */
DEFFUN(forth_stackdump)
{
	uint32_t *ptr;
	int n, i;
#ifdef FULLMEM
	int inc;
#endif

	if ( param == 0 )
	{
		ptr = data_sp;
		n = data_depth;
#ifdef FULLMEM
		inc = -1;
#endif
	}
	else
	{
		ptr = return_sp;
		n = return_depth;
#ifdef FULLMEM
		inc = 1;
#endif
	}

	i = 4;

	while ( n > 0 )
	{
		printf("0x%08x", *ptr);
		n--;
		i--; 
#ifdef FULLMEM
		ptr += inc;
#else
		ptr++;
#endif
		if ( i <= 0 || n <= 0 )
		{
			printf("\n");
			i = 4;
		}
		else
			printf(" ");
	}
	
	return(0);
}}

int add_standard_dict(forth_t *forth)
{
	int r = 0;

#ifdef DEBUGGING
	r += add_to_dict(forth, "dbglvl", DICT_FUNCTION, forth_dbglvl, 0);
#endif

	r += add_to_dict(forth, "vlist", DICT_FUNCTION, forth_vlist, 0);
#ifdef VARSTK
	r += add_to_dict(forth, "dsize", DICT_FUNCTION|DICT_COMMAND, forth_stacksize, 0);
	r += add_to_dict(forth, "rsize", DICT_FUNCTION|DICT_COMMAND, forth_stacksize, 1);
#endif
	r += add_to_dict(forth, "ddump", DICT_FUNCTION, forth_stackdump, 0);
	r += add_to_dict(forth, "rdump", DICT_FUNCTION, forth_stackdump, 1);
	r += add_to_dict(forth, "cr", DICT_FUNCTION, forth_cr, 0);
	r += add_to_dict(forth, ".", DICT_FUNCTION, forth_dot, 0);
	r += add_to_dict(forth, "u.", DICT_FUNCTION, forth_dot, 1);

	r += add_to_dict(forth, "0<", DICT_FUNCTION, forth_1op, 0);
	r += add_to_dict(forth, "0=", DICT_FUNCTION, forth_1op, 1);
	r += add_to_dict(forth, "0>", DICT_FUNCTION, forth_1op, 2);
	r += add_to_dict(forth, "1+", DICT_FUNCTION, forth_1op, 3);
	r += add_to_dict(forth, "1-", DICT_FUNCTION, forth_1op, 4);
	r += add_to_dict(forth, "2+", DICT_FUNCTION, forth_1op, 5);
	r += add_to_dict(forth, "2-", DICT_FUNCTION, forth_1op, 6);
	r += add_to_dict(forth, "@", DICT_FUNCTION, forth_1op, 7);
	r += add_to_dict(forth, "abs", DICT_FUNCTION, forth_1op, 8);
	r += add_to_dict(forth, "negate", DICT_FUNCTION, forth_1op, 9);

	r += add_to_dict(forth, "+", DICT_FUNCTION, forth_2op, 0);
	r += add_to_dict(forth, "-", DICT_FUNCTION, forth_2op, 1);
	r += add_to_dict(forth, "*", DICT_FUNCTION, forth_2op, 2);
	r += add_to_dict(forth, "/", DICT_FUNCTION, forth_2op, 3);
	r += add_to_dict(forth, "and", DICT_FUNCTION, forth_2op, 4);
	r += add_to_dict(forth, "or", DICT_FUNCTION, forth_2op, 5);
	r += add_to_dict(forth, "xor", DICT_FUNCTION, forth_2op, 6);
	r += add_to_dict(forth, "<", DICT_FUNCTION, forth_2op, 7);
	r += add_to_dict(forth, "=", DICT_FUNCTION, forth_2op, 8);
	r += add_to_dict(forth, ">", DICT_FUNCTION, forth_2op, 9);
	r += add_to_dict(forth, "max", DICT_FUNCTION, forth_2op, 10);
	r += add_to_dict(forth, "min", DICT_FUNCTION, forth_2op, 11);
	r += add_to_dict(forth, "mod", DICT_FUNCTION, forth_2op, 12);

	r += add_to_dict(forth, "drop", DICT_FUNCTION, forth_drop, 0);
	r += add_to_dict(forth, "dup", DICT_FUNCTION, forth_dup, 0);
	r += add_to_dict(forth, "?dup", DICT_FUNCTION, forth_dup, 1);

	r += add_to_dict(forth, "swap", DICT_FUNCTION, forth_2op2, 0);
	r += add_to_dict(forth, "over", DICT_FUNCTION, forth_2op2, 1);

	r += add_to_dict(forth, "!", DICT_FUNCTION, forth_store, 0);

	r += add_to_dict(forth, "constant", DICT_FUNCTION, forth_number, 0);
	r += add_to_dict(forth, "variable", DICT_FUNCTION, forth_number, 1);
	r += add_to_dict(forth, "forget", DICT_FUNCTION, forth_forget, 0);
	r += add_to_dict(forth, "redefine", DICT_FUNCTION, forth_redefine, 0);
	r += add_to_dict(forth, ":", DICT_FUNCTION, forth_compile, 0);
	r += add_to_dict(forth, ";", DICT_FUNCTION|DICT_COMPILE|DICT_RUN, forth_return, 0);
	r += add_to_dict(forth, "exit", DICT_FUNCTION, forth_return, 1);
	r += add_to_dict(forth, "if", DICT_FUNCTION|DICT_COMPILE|DICT_RUN, forth_if, 0);
	r += add_to_dict(forth, "else", DICT_FUNCTION|DICT_COMPILE|DICT_RUN, forth_else, 0);
	r += add_to_dict(forth, "then", DICT_FUNCTION|DICT_COMPILE|DICT_RUN, forth_then, 0);
	r += add_to_dict(forth, "begin", DICT_FUNCTION|DICT_COMPILE|DICT_RUN, forth_begin, 0);
	r += add_to_dict(forth, "do", DICT_FUNCTION|DICT_COMPILE|DICT_RUN, forth_begin, 1);
	r += add_to_dict(forth, "until", DICT_FUNCTION|DICT_COMPILE|DICT_RUN, forth_until, 0);
	r += add_to_dict(forth, "while", DICT_FUNCTION|DICT_COMPILE|DICT_RUN, forth_until, 1);
	r += add_to_dict(forth, "repeat", DICT_FUNCTION|DICT_COMPILE|DICT_RUN, forth_until, 2);
	r += add_to_dict(forth, "loop", DICT_FUNCTION|DICT_COMPILE|DICT_RUN, forth_until, 3);
	r += add_to_dict(forth, "+loop", DICT_FUNCTION|DICT_COMPILE|DICT_RUN, forth_until, 4);
	r += add_to_dict(forth, "leave", DICT_FUNCTION|DICT_COMPILE|DICT_RUN, forth_until, 5);
	r += add_to_dict(forth, "i", DICT_FUNCTION, forth_loopct, 0);
	r += add_to_dict(forth, "i'", DICT_FUNCTION, forth_loopct, 1);
	r += add_to_dict(forth, "j", DICT_FUNCTION, forth_loopct, 2);
	r += add_to_dict(forth, "j'", DICT_FUNCTION, forth_loopct, 3);
	r += add_to_dict(forth, ">r", DICT_FUNCTION, forth_to_rstack, 0);
	r += add_to_dict(forth, "r>", DICT_FUNCTION, forth_from_rstack, 0);

	/* Make a note of some special words (conditionals, loops, etc) */
	_if = find_in_dict(forth, "if");
	_else = find_in_dict(forth, "else");
	_then = find_in_dict(forth, "then");
	_while = find_in_dict(forth, "while");
	_repeat = find_in_dict(forth, "repeat");
	return(r);
}
