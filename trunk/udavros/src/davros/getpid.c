/*	getpid.c - __dv_getpid
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
#include <davros/config.h>
#include <davros/process.h>

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

/*====================================================================
 *	__dv_getpid - change the priority of a process
 *====================================================================
*/
__dv_processstate_t *__dv_getpid(void)
{
	return __dv_currproc;
}
