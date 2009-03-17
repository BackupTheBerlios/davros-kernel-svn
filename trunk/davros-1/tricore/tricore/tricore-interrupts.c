/*	tricore-interrupt.c - interrupt manipulation functions
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
 *	This file contains routines to manipulate the interrupt vectors.
 *
*/

#include "tricore.h"
#include "tricore-core.h"
#include "kernel-config.h"
#include "davros/kernel.h"

/*
 *	__davros_attach_interrupt() - attach function to interrupt
 *
 *	This function attaches the given function and parameter to the
 *	specified interrupt vector. If the vector already has a function
 *	attached, or is out of range, -1 is returned, otherwise 0.
 *	The interrupt number will normally be in the range 2..__DAVROS_NVECTORS.
 *	Interrupt 1 is reserved for use by the kernel context switch.
 *	Interrupt 0 cannot occur.
 *
 *	The parameter field of the vector is stored before the handler so
 *	that if an interrupt occurs, the unused interrupt exception happens
 *	rather than the handler being called with a bad parameter.
*/
int __davros_attach_interrupt(int inum, __davros_intfunc_t f, void *p)
{
	interrupt_vector_t *ivec;

	if ( inum < 0 || inum >= __DAVROS_NVECTORS )
		return(-1);

	ivec = &interrupt_table[inum];

	if ( ivec->handler != 0 )
		return(-1);

	ivec->type = 0;		/* For future use */
	ivec->param = (uint32_t)p;
	ivec->handler = (uint32_t)f;

	return(0);
}

/*
 *	__davros_detach_interrupt() - detach function from interrupt
 *
 *	This routine sets the handler field of the vector to zero
*/
int __davros_detach_interrupt(int inum)
{
	interrupt_vector_t *ivec;

	if ( inum < 0 || inum >= __DAVROS_NVECTORS )
		return(-1);

	ivec = &interrupt_table[inum];
	ivec->handler = 0;
	ivec->param = 0;
	ivec->type = 0;		/* For future use */

	return(0);
}

/*
 *	__davros_get_interrupt_handler() - returns the handler of the
 *										specified interrupt
*/
__davros_intfunc_t __davros_get_interrupt_handler(inum)
{
	interrupt_vector_t *ivec;

	if ( inum < 0 || inum >= __DAVROS_NVECTORS )
		return((__davros_intfunc_t)(-1));

	ivec = &interrupt_table[inum];

	return((__davros_intfunc_t)ivec->handler);
}

/*
 *	__davros_get_interrupt_parameter() - returns the parameter of the
 *											specified interrupt
*/
void *__davros_get_interrupt_parameter(inum)
{
	interrupt_vector_t *ivec;

	if ( inum < 0 || inum >= __DAVROS_NVECTORS )
		return((void *)(-1));

	ivec = &interrupt_table[inum];

	return((void *)ivec->handler);
}
