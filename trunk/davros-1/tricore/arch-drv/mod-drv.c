/*	mod-drv.c - Driver for Tricore module
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
 *	This file contains a driver for all Tricore modules
*/

#include "drv/mod-drv.h"
#include "drv/pwr-drv.h"
#include "tricore-core.h"

/*
 *	tricore_module_init - initialize a Tricore on-chip module
 *
 *	This routine initialises and enables a TriCore on-chip module.
*/

int tricore_module_init(tricore_mod_t *m, int sleep, uint32_t rmc)
{
	int res = 0;
	int ps;

	ps = disable_interrupts();
	endinit(0);
	m->clc = (sleep ? CLC_EDIS : 0) | CLC_RMCval(rmc);
    
	if ( m->clc & CLC_DISS )	/* flush pipeline by reading */
	{
		res = -1;			/* module is still disabled */
	}
	endinit(1);
	restore_interrupts(ps);
	return(res);
}

/*
 * tricore_module_disable - disable a Tricore on-chip module
 *
 * This routine disables a Tricore on-chip module.
*/

int tricore_module_disable(tricore_mod_t *m)
{
	int res = 0;
	int ps;

	ps = disable_interrupts();
	endinit(0);
	m->clc |= CLC_DISR;
	if ( (m->clc & CLC_DISS) == 0 )		/* flush pipeline by reading */
	{
		res = -1;					/* module is still enabled */
	}
	endinit(1);
	restore_interrupts(ps);
	return(res);
}
