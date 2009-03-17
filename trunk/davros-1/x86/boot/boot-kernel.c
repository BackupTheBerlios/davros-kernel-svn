/*	boot-kernel.c - boot a system running the Davros kernel
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
 *	This file contains the code that initialises the processor and the
 *	rest of the basic hardware before jumping to the main davros
 *	function.
 *
*/

#include "kernel-config.h"
#include "x86.h"
#include "boot-sys.h"
#include "davros/kernel.h"
#include "x86-core.h"
#include "drv/i8250-drv.h"
#include "drv/i8250-tty-drv.h"
#include "drv/i8253-drv.h"
#include "drv/i8259-drv.h"
#include <ctype.h>
#define __STDIO_PRIVATE
#include <stdio.h>

#if 1 /* FIXME */
#include "davros/kernel-utils.h"
#endif

/*
 *	usrmain() - start the kernel
 *
 *  This function is called from from entry. It initialises the
 *	serial port (COM1) for kernel debug messages and then starts the
 *	kernel program.
 *
*/
void usrmain(void)
{
	kprintf("davros version 0.1, copyright 2001 David Haworth\n");
	kprintf("davros comes with ABSOLUTELY NO WARRANTY. It is free software,\n");
	kprintf("and you are welcome to redistribute it under certain conditions.\n");
	kprintf("Please read the file COPYING for details.\n");

	__davros_init((memaddr_t)&__bss_end, (RAM_START+RAM_SIZE));
	/* Never returns */
}

/*
 *	__arch_init() - start the drivers, etc.
 *
*/
void __arch_init(void)
{
	uint16_t count;

	/*	PC has 2 8259s. M is master, S is slave connected to input
	 *	2 on master.
	 *	We choose auto-eoi mode for now, because nested interrupts 
	 *	are not supported.
	*/
	i8259_init(I8259_M, I8259_ICW1_IC4,
			__DAVROS_BASE_IRQ, I8259_ICW3_M_S2,
			I8259_ICW4_BUF | I8259_ICW4_MS | I8259_ICW4_AEOI | I8259_ICW4_UPM);
	i8259_init(I8259_S,	I8259_ICW1_IC4,
			__DAVROS_BASE_IRQ+8, 2,
			I8259_ICW4_BUF | I8259_ICW4_AEOI | I8259_ICW4_UPM);

	/*	The counter value is calculated to be the timer input
	 *	frequency over the required interrupt frequency, rounded to
	 *	the nearest multiple of 2, because the counter counts down in
	 *	2s.
	 *	We don't touch timer 1 - it might be controlling the RAM
	 *	refresh. We assume the BIOS has set it correctly.
	 *	Timer 2 is the speaker, so we just ignore that for now.
	*/
	count = (((TIMER_FREQ + __DAVROS_HZ/2) / __DAVROS_HZ) + 1) & ~1;

	i8253_init(I8253, 0, I8253_CTRL_RWL_LM | I8253_CTRL_MODE_SQW, count);

	if ( __davros_attach_interrupt(__DAVROS_INUM_TIMER,
				(__davros_intfunc_t)__davros_tick, NULL) != 0 )
	{
		kprintf("__davros_attach_interrupt() returned error.\n");
		return;
	}

	pic_enable_interrupts(__DAVROS_IMASK_TIMER);

	i8250_tty_create("tty/0", I8250_0, __DAVROS_INUM_TTY0, __DAVROS_IMASK_TTY0);
	i8250_tty_create("tty/1", I8250_1, __DAVROS_INUM_TTY1, __DAVROS_IMASK_TTY1);

	enable_interrupts();
}

/* kputc function for kprintf */
int kputc(int c, void *stream)
{
	if ( c == '\n' )
		i8250_polled_putc(I8250_0, '\r');
	i8250_polled_putc(I8250_0, c);
	return(c);
}

/* kmode function for kprintf
*/
int kmode(int m)
{
	if ( m == KPOLLED )
		return(disable_interrupts());
	else
		return(restore_interrupts(m));
}

/* FIXME: temp */
int fputc(int c, void *stream)
{
	if ( c == '\n' )
		__davros_putc((__davros_device_t *)stream, '\r');
	__davros_putc((__davros_device_t *)stream, c);
	return(c);
}

uint32_t i8250_read(memaddr_t base, int reg)
{
	return(in8(base+reg));
}

void i8250_write(memaddr_t base, int reg, uint32_t val)
{
	out8(base+reg, val);
}

uint32_t i8253_read(memaddr_t base, int reg)
{
	return(in8(base+reg));
}

void i8253_write(memaddr_t base, int reg, uint32_t val)
{
	out8(base+reg, val);
}

uint32_t i8259_read(memaddr_t base, int reg)
{
	return(in8(base+reg));
}

void i8259_write(memaddr_t base, int reg, uint32_t val)
{
	out8(base+reg, val);
}

/*
 *	pic_enable_interrupts() - enable interrupts at PIC
*/
void pic_enable_interrupts(uint16_t mask)
{
	i8259_enable(I8259_M, mask & __DAVROS_IMASK_MASTER);
	i8259_enable(I8259_S, mask >> 8);
}

/*
 *	pic_disable_interrupts() - disable interrupts at PIC
*/
void pic_disable_interrupts(uint16_t mask)
{
	i8259_disable(I8259_M, mask & __DAVROS_IMASK_MASTER);
	i8259_disable(I8259_S, mask >> 8);
}

/*
 *	init_cpu() - intialise the CPU
 *
 *	Assumptions: interrupts are disabled globally.
*/
void init_cpu(void)
{
	/*	Now we're running at full speed, we can zero the bss section and
	 *	copy the ROM image of the data section out to RAM
	*/
#if 0	/* FIXME: 	we hope the bootloader does this! */
	clear_bss();
	copy_data();
#endif

	init_interrupt();

	/* Fixme: we really ought to intialise the kbd, etc., but
	 * it's easy to be lazy & assume the bootloader has already
	 * done it.
	 * In any case we've killed all unwanted interrupts by reprogramming
	 * the PIC.
	*/
}

/*
 *	clear_bss() - sets the whole bss section to zero, as expected by C programs
 *
 *	This function is called from the assembler-code startup function. It cannot
 *	assume that any global variables contain the expected values. In addition,
 *	it cannot make use of any uninitialised (bss) global variables.
 *
 *	In practice, it only uses local (automatic) variables, and on Tricore, we
 *	can fairly safely assume that these will be in registers.
 *
 *	Assumptions: the bss section is word aligned and is a whole number of
 *	words long.
*/

#if 0	/* FIXME: running in RAM at the moment */
void clear_bss(void)
{
	uint32_t *p = (uint32_t *)bss_start;

	while ( p < bss_end )
		*p++ = 0;
}
#endif

/*
 *	copy_data() - copies the ROM image of the data section to the proper place
 *
 *	This function is called from the assembler-code startup function. It can
 *	assume that bss is zeroed (if BOOT_CLEAR_BSS is defined). It cannot make
 *	use of any initialised (data) global variables.
 *	
 *	In practice, it only uses local (automatic) variables, and on Tricore,
 *	we can fairly safely assume that these will be in registers.
 *
 *	Assumptions: the data section is word aligned and is a whole number of
 *	words long.
*/

#if 0	/* FIXME: running in RAM at the moment */
void copy_data(void)
{
	uint32_t *p, *q;

	p = (uint32_t *)data_start;
	q = (uint32_t *)data_image;

	while ( p < data_end )
		*p++ = *q++;
}
#endif

/*	FIXME: this needs expansion ... */
int x86_exception(int trapno, esf_t *esf)
{
	kprintf("Exception no. %d at PC = 0x%08x\n", trapno, esf->pc);

	kprintf("Registers:\n");
	kprintf("eax  0x%08x    ebx  0x%08x    ecx  0x%08x    edx  0x%08x\n",
			esf->eax, esf->ebx, esf->ecx, esf->edx);
	kprintf("ebp  0x%08x    esi  0x%08x    edi  0x%08x    flag 0x%08x\n",
			esf->ebp, esf->esi, esf->edi, esf->flags);

	for (;;)
		;
}
