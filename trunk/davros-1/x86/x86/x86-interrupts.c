/*	x86-interrupt.c - interrupt manipulation functions
 *
 *	Copyright 2002 David Haworth
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

#include "x86.h"
#include "x86-core.h"
#include "kernel-config.h"
#include "davros/kernel.h"
#include "arch-cpudef.h"

/*
 *	__davros_attach_interrupt() - attach function to interrupt
 *
 *	This function attaches the given function and parameter to a free
 *	interrupt stub function and connects the function to the
 *	specified interrupt vector. If the vector already has a function
 *	attached, or is out of range, -1 is returned, otherwise 0.
 *	The interrupt number will be in the range 32..__DAVROS_NVECTORS.
 *	interrupts 0..31 are reserved CPU traps.
 *
*/
int __davros_attach_interrupt(int inum, __davros_intfunc_t f, void *p)
{
	interrupt_vector_t *ivec;
	interrupt_stub_t *istub;
	int i;

	if ( inum < 32 || inum >= (__DAVROS_NVECTORS+32) )
		return(-1);

	ivec = &((interrupt_vector_t *)0)[inum];
	istub = (interrupt_stub_t *)getstub(ivec);

	if ( istub == (interrupt_stub_t *)__davros_trap_unknown )
	{
		/* Need to allocate a stub */
		istub = handler_table;
		for ( i = 0; i < __DAVROS_NHANDLERS && istub->inum != 0; i++, istub++ )
			/*	Nothing */
		if ( i >= __DAVROS_NHANDLERS )
			return(-1);
		setstub(ivec, (uint32_t)istub);
		istub->inum = inum;
	}

	if ( istub->handler != 0 )
		return(-1);

	istub->param = (uint32_t)p;
	istub->handler = (uint32_t)f;

	return(0);
}

/*
 *	__davros_detach_interrupt() - detach function from interrupt
 *
 *	This routine sets the handler field of the vector to zero and
 *	sets the vector back to __davros_trap_unknown.
*/
int __davros_detach_interrupt(int inum)
{
	interrupt_vector_t *ivec;
	interrupt_stub_t *istub;

	if ( inum < 32 || inum >= (__DAVROS_NVECTORS+32) )
		return(-1);

	ivec = &((interrupt_vector_t *)0)[inum];
	istub = (interrupt_stub_t *)getstub(ivec);
	if ( istub == (interrupt_stub_t *)__davros_trap_unknown )
		return(0);
	istub->handler = 0;
	istub->param = 0;
	istub->inum = 0;
	setstub(ivec, (uint32_t)__davros_trap_unknown);

	return(0);
}

/*
 *	__davros_get_interrupt_handler() - returns the handler of the specified interrupt
*/
__davros_intfunc_t __davros_get_interrupt_handler(inum)
{
	interrupt_vector_t *ivec;
	interrupt_stub_t *istub;

	if ( inum < 32 || inum >= (__DAVROS_NVECTORS+32) )
		return((__davros_intfunc_t)(-1));

	ivec = &((interrupt_vector_t *)0)[inum];
	istub = (interrupt_stub_t *)getstub(ivec);
	if ( istub == (interrupt_stub_t *)__davros_trap_unknown )
		return(NULL);

	return((__davros_intfunc_t)istub->handler);
}

/*
 *	__davros_get_interrupt_parameter() - returns the parameter of the specified interrupt
*/
void *__davros_get_interrupt_parameter(inum)
{
	interrupt_vector_t *ivec;
	interrupt_stub_t *istub;

	if ( inum < 32 || inum >= (__DAVROS_NVECTORS+32) )
		return((__davros_intfunc_t)(-1));

	ivec = &((interrupt_vector_t *)0)[inum];
	istub = (interrupt_stub_t *)getstub(ivec);
	if ( istub == (interrupt_stub_t *)__davros_trap_unknown )
		return(NULL);

	return((void *)istub->param);
}

/*
 *	init_interrupt() - initialises the interrupt system
*/

#define INT_CS	0x08
#define EXC_CS	0x08

void init_interrupt(void)
{
	interrupt_vector_t *vec = NULL;
	uint32_t stubaddr = (uint32_t)__davros_trap_00;
	uint32_t stubinc = (uint32_t)__davros_trap_01 - (uint32_t)__davros_trap_00;
	int i;
	uint16_t idt[3];

	for ( i = 0; i < 32; i++ )
	{
		vec->gd0 = EXC_CS << 16;
		vec->gd1 = GD1_P | GD1_DPL | GD1_D | GD1_TYPE_INT;
		setstub(vec, stubaddr);
		vec++;
		stubaddr += stubinc;
	}

	stubaddr = (uint32_t)__davros_trap_unknown;
	for ( i = 0; i < __DAVROS_NVECTORS; i++ )
	{
		vec->gd0 = INT_CS << 16;
		vec->gd1 = GD1_P | GD1_DPL | GD1_D | GD1_TYPE_INT;
		setstub(vec, stubaddr);
		vec++;
	}

	idt[0] = (__DAVROS_NVECTORS + 32) * 8 - 1;
	idt[1] = 0;
	idt[2] = 0;
	load_idt(idt);
}
