/*	boot-sys.h - prototypes of functions in boot-***.c
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
 *	This file contains prototypes for the functions in boot-***.c
*/

#if !defined(__boot_sys_h)
#define __boot_sys_h

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(__ASSEMBLER__)

/* These functions are required (usually in boot-*.c) to start
 * the system.
*/
void usermain(void);
void init_cpu(void);
void clear_bss(void);
void copy_data(void);

/* These "variables" are created by the linker scripts. They
 * are only placemarkers, and should never be read or written.
 * Their addresses are used to find the start & end of the
 * program and data sections.
*/
extern int __text_start;
extern int __text_end;
extern int __data_start;
extern int __data_end;
extern int __bss_start;
extern int __bss_end;

#endif

#ifdef __cplusplus
}
#endif

#endif
