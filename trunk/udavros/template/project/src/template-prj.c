/*	template-prj.c - Davros template project
 *
 *	Copyright 2008 David Haworth
 *
 *	This file is part of davros.
 *
 *	davros is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	davros is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with davros.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <davros.h>
#include <davros-config.h>

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

#ifdef DV_CFG_USERPROCESS
int template_proc(int nargs, int *args);
#endif

unsigned char DV_CFG_HEAPBASE[DV_CFG_HEAPSIZE];

/*==============================================================================
 *	template_init - called at startup
 *==============================================================================
*/
#ifdef DV_CFG_USERINIT
void template_init(void)
{
	/* Put your startup code here. You can do anything you like that is non-blocking.
	 * If you need to block (for example, printf!) it's better to use a startup process
	*/
}
#endif

/*==============================================================================
 *	template_null - called instead of dynamic stop in null process
 *==============================================================================
*/
void template_null(void)
{
	/* Put your idle-loop code here. You can do anything you like that is non-blocking.
	 * Using the CPU's HALT (or similar) instruction might save power.
	*/
	for (;;) ;
}

/*==============================================================================
 *	template_proc - entry function for startup process
 *==============================================================================
*/
#ifdef DV_CFG_USERPROCESS
int template_proc(int nargs, int *args)
{
	/* Put your startup code here. You can do anything - even make blocking calls.
	*/
	return 0;
}
#endif
