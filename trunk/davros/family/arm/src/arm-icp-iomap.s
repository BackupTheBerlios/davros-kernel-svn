
/*	arm-icp-iomap.s - I/O port map for ARM926EJ Integrator/CP board.
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

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

/*==============================================================================
 *	Interrupt controllers
 *==============================================================================
*/
	.global		__dv_arm_pic_pri_irq
	.global		__dv_arm_pic_pri_fiq
	.global		__dv_arm_pic_sec

	.equ		__dv_arm_pic_pri_irq,	0x14000000
	.equ		__dv_arm_pic_pri_fiq,	0x14000020
	.equ		__dv_arm_pic_sec,		0xca000000

/*==============================================================================
 *	Timers
 *==============================================================================
*/
	.global		__dv_arm_timer_0
	.global		__dv_arm_timer_1
	.global		__dv_arm_timer_2

	.equ		__dv_arm_timer_0,		0x13000000
	.equ		__dv_arm_timer_1,		0x13000100
	.equ		__dv_arm_timer_2,		0x13000200
