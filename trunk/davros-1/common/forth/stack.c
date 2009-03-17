/*	stack.c
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
 *	Implements a stack.
*/
#ifndef FULLMEM

#include "unistd.h"
#include "stdlib.h"
#include "stack.h"

int init_stack(stack_t *stack, int sz)
{
	stack->store = NULL;
	return(stack_resize(stack, sz));
}
	
int push(stack_t *stack, int32_t val)
{
	if ( stack->depth >= stack->size )
		return(-1);

	stack->depth++;
	stack->sp--;
	*stack->sp = val;
	return (0);
}

int pop(stack_t *stack, int32_t *dest)
{
	*dest = *stack->sp;
	if ( stack->depth <= 0 )
		return(-1);
	stack->depth--;
	stack->sp++;
	return (0);
}

#if 0
int put(stack_t *stack, int32_t pos, int32_t val)
{
	if ( pos >= stack->depth )
		return(-1);
	*stack->sp[pos] = val;
	return (0);
}

int get(stack_t *stack, int32_t pos, int32_t *dest)
{
	if ( pos >= stack->depth )
		return(-1);
	*depth = *stack->sp[pos];
	return (0);
}
#endif

int reset_stack(stack_t *stack)
{
	stack->sp = &stack->store[stack->size];
	*stack->sp = END_MARKER;
	stack->depth = 0;
	return(0);
}

int stack_resize(stack_t *stack, int newsz)
{
#ifdef FIXSTK
	return(stack->store != NULL);
#else
	uint32_t *tmp = calloc(newsz+1, sizeof(int32_t));
	if ( tmp == NULL )
		return(-1);
	if ( stack->store != NULL )
		free(stack->store);
	stack->store = tmp;
	stack->size = newsz;
	stack->sp = &stack->store[stack->size];
	*stack->sp = END_MARKER;
	stack->depth = 0;
	return(0);
#endif
}

#endif
