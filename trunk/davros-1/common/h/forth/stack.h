/*	stack.h
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
 *	Implements a stack.
*/

#if !defined(__stack_h)
#define __stack_h

#include "qdftypes.h"

typedef struct stack
{
	int32_t *store;		/* Where the stack is stored */
	int32_t *sp;		/* Current pointer (points to most recent push) */
	uint32_t size;		/* Current no of elements in store */
	uint32_t depth;		/* Current stack depth (no of pushes) */
} stack_t;

#define END_MARKER	0xdeadbeef

int init_stack(stack_t *stack, int sz);
int push(stack_t *stack, int32_t val);
int pop(stack_t *stack, int32_t *dest);
int reset_stack(stack_t *stack);
int stack_resize(stack_t *stack, int newsz);

#endif
