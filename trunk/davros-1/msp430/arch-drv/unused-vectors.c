/*	unused-vectors.c - Interrupt routines for unused vectors
 *
 *	$Id$
 *	Copyright 2004 David Haworth
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
 *	This file contains a dummy handlers for all the unused interrupts.
 *	To avoid having a dummy handler for a particular interrupt, simply
 *	define the macro __DAVROS_HAVE_ISR_x (x = 0 .. 28, even).
 *
 *	$Log: unused-vectors.c,v $
 *	Revision 1.1  2004/05/11 20:39:27  dave
 *	Files for the MSP430 port.
 *	
*/

#include "kernel-config.h"
#include "arch-cpudef.h"
#include "davros/kernel.h"
#include "drv/timer-a-drv.h"
#include "msp430.h"

#ifndef __DAVROS_HAVE_ISR_0
void __attribute__((interrupt (0))) unused_0(void)
{
	while (1) ;
}
#endif

#ifndef __DAVROS_HAVE_ISR_2
void __attribute__((interrupt (2))) unused_2(void)
{
	while (1) ;
}
#endif

#ifndef __DAVROS_HAVE_ISR_4
void __attribute__((interrupt (4))) unused_4(void)
{
	while (1) ;
}
#endif

#ifndef __DAVROS_HAVE_ISR_6
void __attribute__((interrupt (6))) unused_6(void)
{
	while (1) ;
}
#endif

#ifndef __DAVROS_HAVE_ISR_8
void __attribute__((interrupt (8))) unused_8(void)
{
	while (1) ;
}
#endif

#ifndef __DAVROS_HAVE_ISR_10
void __attribute__((interrupt (10))) unused_10(void)
{
	while (1) ;
}
#endif

#ifndef __DAVROS_HAVE_ISR_12
void __attribute__((interrupt (12))) unused_12(void)
{
	while (1) ;
}
#endif

#ifndef __DAVROS_HAVE_ISR_14
void __attribute__((interrupt (14))) unused_14(void)
{
	while (1) ;
}
#endif

#ifndef __DAVROS_HAVE_ISR_16
void __attribute__((interrupt (16))) unused_16(void)
{
	while (1) ;
}
#endif

#ifndef __DAVROS_HAVE_ISR_18
void __attribute__((interrupt (18))) unused_18(void)
{
	while (1) ;
}
#endif

#ifndef __DAVROS_HAVE_ISR_20
void __attribute__((interrupt (20))) unused_20(void)
{
	while (1) ;
}
#endif

#ifndef __DAVROS_HAVE_ISR_22
void __attribute__((interrupt (22))) unused_22(void)
{
	while (1) ;
}
#endif

#ifndef __DAVROS_HAVE_ISR_24
void __attribute__((interrupt (24))) unused_24(void)
{
	while (1) ;
}
#endif

#ifndef __DAVROS_HAVE_ISR_26
void __attribute__((interrupt (26))) unused_26(void)
{
	while (1) ;
}
#endif

#ifndef __DAVROS_HAVE_ISR_28
void __attribute__((interrupt (28))) unused_28(void)
{
	while (1) ;
}
#endif

/* Interrupt 30 is reset.
*/
