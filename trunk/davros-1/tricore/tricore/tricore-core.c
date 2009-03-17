/*	tricore-core.c - routines to manipulate the CPU core
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
 *	This file contains routines related to the Tricore CPU core,
 *	such as context/address (& v.v.) conversion.
 *
*/

#include "tricore.h"
#include "tricore-core.h"

/*
 *	context_to_address() - converts a context to an address
 *
 *	This routine converts a context segment/index as used in
 *	the PCXI/LCX/FCX registers into an absolute address.
 *
 *	csa_t *context_to_address(uint32_t cx);
*/
csa_t *context_to_address(uint32_t cx)
{
	return (csa_t *)( ((cx << CX_SEG_SHIFT) & CX_ADDR_SEG) |
		    ((cx << CX_OFF_SHIFT) & CX_ADDR_OFFSET) );
}

/*
 *	address_to_context() - converts an address to a context
 *
 *	This routine converts a memory address to a context segment/index
 *	as used in the PCXI/LCX/FCX registers.
 *	The address must be aligned on a 64-byte boundary, and must lie inside
 *	the lower 2 MB of the segment. An out-of-range value will result
 *	in a return value of 0.
 *
 *	uint32_t address_to_context(csa_t *csa);
*/
uint32_t address_to_context(csa_t *csa)
{
	uint32_t cx = 0;

    if ( (((uint32_t)csa) & CX_ADDR_ALIGN ) != 0 )
	{
		/* ERROR - the address is incorrectly aligned. */
	}
    else
    if ( (((uint32_t)csa) & CX_ADDR_ALIGN ) != 0 )
	{
		/* ERROR - the address is too high in the segment. */
	}
    else
	{
		cx = ((((uint32_t)csa) & CX_ADDR_SEG) >> CX_SEG_SHIFT) |
		     ((((uint32_t)csa) & CX_ADDR_OFFSET) >> CX_OFF_SHIFT);
	}

    return(cx);
}


/*
 *	next_csa - returns the address of the next CSA in the list.
 *
 *	csa_t *next_csa(csa_t *csa);
*/
csa_t *next_csa(csa_t *csa)
{
	return( csa == NULL ? csa : context_to_address(csa->pcxi));
}
