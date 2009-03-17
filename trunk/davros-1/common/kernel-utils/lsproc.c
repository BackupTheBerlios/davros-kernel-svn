/*	lsproc.c - __davros_lsproc
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
*/

#include "davros/kernel-utils.h"
#include <stdio.h>

__DAVROS_IDENT("$Id$")

const char *pstates[] =
{	"Unknown",
	"Current",
	"Free",
	"Ready",
	"Receive",
	"Sleep",
	"Suspend",
	"Wait",
	"Break"
};

const char dvnone[] = "None";

/*==============================================================================
 *	lsproc - print process table
 *==============================================================================
*/

void __davros_lsproc
(	__davros_device_t *out
)
{
	__davros_process_t *p;
	__davros_qent_t *pe;

	if ( out == NULL )
		out = __davros_getstdout();

	if ( out == NULL )
		return;

	pe = __davros.proctab.head.next;
	while ( pe != &__davros.proctab.tail )
	{
		p = (__davros_process_t *)pe->kd.data;

		fprintf(out, "%-*.*s %-7.7s %3d  %-*.*s %-*.*s %-*.*s\n",
			__DAVROS_PNMLEN, __DAVROS_PNMLEN, p->name,
			p->state > 8 ? pstates[0] : pstates[p->state], p->priority,
			__DAVROS_DVNMLEN, __DAVROS_DVNMLEN,
			p->dvstdin == NULL ? dvnone : p->dvstdin->name,
			__DAVROS_DVNMLEN, __DAVROS_DVNMLEN,
			p->dvstdout == NULL ? dvnone : p->dvstdout->name,
			__DAVROS_DVNMLEN, __DAVROS_DVNMLEN,
			p->dvstderr == NULL ? dvnone : p->dvstderr->name);

		pe = pe->next;
	}
}
