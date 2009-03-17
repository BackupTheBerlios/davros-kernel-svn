/*	davros-ld - Davros template linker script
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
 *
 *	$Id$
*/
MEMORY
{
	ram (rwx)		: ORIGIN = 0x00000000, LENGTH = 0x08000000
}

SECTIONS
{
	.dv_vector			: { *(Vectors)   } > ram
	.text     			: { *(.text*)    } > ram
	.rodata   			: { *(.rodata*)  } > ram
	.data     			: { *(.data*)    } > ram
	.bss      			: { *(.bss*)     } > ram
}
