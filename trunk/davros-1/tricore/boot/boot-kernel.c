/*	boot-kernel.c - boot a system running the Davros kernel
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
 *	This file contains the code that initialises the processor and the
 *	rest of the basic hardware before jumping to the main davros
 *	function.
 *
*/

#include "kernel-config.h"
#include "tricore.h"
#include "boot-sys.h"
#include "davros/kernel.h"
#include "modules/tricore-csfr.h"
#include "modules/tricore-mod.h"
#include "modules/tricore-cps.h"
#include "modules/tricore-pwr.h"
#include "modules/tricore-pmu.h"
#include "modules/tricore-dmu.h"
#include "modules/tricore-bcu.h"
#include "modules/tricore-ebu.h"
#include "modules/tricore-gptu.h"
#include "drv/asc-drv.h"
#include "drv/gpio-drv.h"
#include "drv/gptu-drv.h"
#include "drv/pwr-drv.h"
#include "drv/asc-tty-drv.h"
#include "tricore-core.h"
#include <ctype.h>
#define __STDIO_PRIVATE
#include <stdio.h>

/*
 *	usrmain() - start the kernel
 *
 *  This function is called from from rom_entry. It initialises the
 *	serial port (ASC0) for kernel debug messages and then starts the
 *	kernel program.
 *
*/
void usrmain(void)
{
#if (ASC0_PORT==0)
	gpio_port_config(0, 4, GPIO_MODE_OUT|GPIO_MODE_ALT2);
	gpio_port_config(0, 5, GPIO_MODE_IN);
	asc_init(ASC0, 1);
#elif (ASC0_PORT==2)
	gpio_port_config(2, 4, GPIO_MODE_OUT|GPIO_MODE_ALT1);
	gpio_port_config(2, 5, GPIO_MODE_IN);
	asc_init(ASC0, 0);
#endif
	ASC0->asc_tbuf = '\r';	/* kick out a character to start things rolling */

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
	set_biv((uint32_t)interrupt_table);
	set_btv((uint32_t)exception_table);

	CPS->cps_src3 = ISR_CLRR;
	CPS->cps_src2 = ISR_CLRR;
	CPS->cps_src1 = ISR_CLRR;
	CPS->cps_src0 = ISR_CLRR;

	gptu_timer_stop(GPTU0, 0);
	gptu_timer_stop(GPTU0, 1);
	gptu_timer_stop(GPTU1, 0);
	gptu_timer_stop(GPTU1, 1);

	GPTU0->gptu_gtsrc7 = ISR_CLRR;
	GPTU0->gptu_gtsrc6 = ISR_CLRR;
	GPTU0->gptu_gtsrc5 = ISR_CLRR;
	GPTU0->gptu_gtsrc4 = ISR_CLRR;
	GPTU0->gptu_gtsrc3 = ISR_CLRR;
	GPTU0->gptu_gtsrc2 = ISR_CLRR;
	GPTU0->gptu_gtsrc1 = ISR_CLRR;
	GPTU0->gptu_gtsrc0 = ISR_CLRR;
	GPTU1->gptu_gtsrc7 = ISR_CLRR;
	GPTU1->gptu_gtsrc6 = ISR_CLRR;
	GPTU1->gptu_gtsrc5 = ISR_CLRR;
	GPTU1->gptu_gtsrc4 = ISR_CLRR;
	GPTU1->gptu_gtsrc3 = ISR_CLRR;
	GPTU1->gptu_gtsrc2 = ISR_CLRR;
	GPTU1->gptu_gtsrc1 = ISR_CLRR;
	GPTU1->gptu_gtsrc0 = ISR_CLRR;

	asc_polled_init(ASC0);
	asc_polled_init(ASC1);

	enable_interrupts();

	if ( gptu_timer_start(GPTU0, 0, __DAVROS_INUM_TIMER, __DAVROS_HZ) != 0 )
	{
		kprintf("gptu_timer_start() returned error.\n");
		return;
	}
	if ( __davros_attach_interrupt(__DAVROS_INUM_TIMER,
				(__davros_intfunc_t)__davros_tick, NULL) != 0 )
	{
		kprintf("__davros_attach_interrupt() returned error.\n");
		return;
	}
	if ( gptu_timer_enable_int(GPTU0, 0) != 0 )
	{
		kprintf("gptu_timer_enable_int() returned error.\n");
		return;
	}

#if (ASC1_PORT==0)
	gpio_port_config(0, 6, GPIO_MODE_OUT|GPIO_MODE_ALT2);
	gpio_port_config(0, 7, GPIO_MODE_IN);
#elif (ASC1_PORT==2)
	gpio_port_config(2, 6, GPIO_MODE_OUT|GPIO_MODE_ALT1);
	gpio_port_config(2, 7, GPIO_MODE_IN);
#endif

	asc_tty_create("tty/0", ASC0, __DAVROS_INUM_ASC0, (ASC0_PORT==0));
	asc_tty_create("tty/1", ASC1, __DAVROS_INUM_ASC1, (ASC1_PORT==0));
}

/* kputc function for kprintf */
int kputc(int c, void *stream)
{
	if ( c == '\n' )
		asc_polled_putc(ASC0, '\r');
	asc_polled_putc(ASC0, c);
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

/*
 *	init_cpu() - intialise the CPU
 *
 *	This function initialises those parts of the CPU that have not already been
 *	initialised by the assembler code in rom-entry. This function is called before
 *	the bss and data sections are initialised, because the RAM may not be visible
 *	until the initialisation done here.
 *
 *	On Tricore we can intialise almost everything - except the SDRAM controller
 *	and the context management systems.
 *
 *	Assumptions: interrupts are disabled globally. ENDINIT is clear.
*/
void init_cpu(void)
{
	/*	Initialise the BCU and EBU
	*/
	BCU->bcu_bcucon = INIT_BCUCON;
	EBU->ebu_ebucon = INIT_EBUCON;

	/*	We only initialise the chip selects that have address ranges defined.
	*/
#if defined(INIT_ADDSEL0) && defined(INIT_BUSCON0)
	EBU->ebu_addsel0 = INIT_ADDSEL0;
	EBU->ebu_buscon0 = INIT_BUSCON0;
#endif
#if defined(INIT_ADDSEL1) && defined(INIT_BUSCON1)
	EBU->ebu_addsel1 = INIT_ADDSEL1;
	EBU->ebu_buscon1 = INIT_BUSCON1;
#endif
#if defined(INIT_ADDSEL2) && defined(INIT_BUSCON2)
	EBU->ebu_addsel2 = INIT_ADDSEL2;
	EBU->ebu_buscon2 = INIT_BUSCON2;
#endif
#if defined(INIT_ADDSEL3) && defined(INIT_BUSCON3)
	EBU->ebu_addsel3 = INIT_ADDSEL3;
	EBU->ebu_buscon3 = INIT_BUSCON3;
#endif

	/*	From here we can assume that all external memory and I/O is visible
	 *	on the bus.
	 *	We set the CPU clock frequency here. This function should be called with
	 *	ENDINIT set, since it manipulates ENDINIT as required.
	*/
	cpu_clock_rate(CLOCK_RATE);

	/*	Now we're running at full speed, we can zero the bss section and
	 *	copy the ROM image of the data section out to RAM
	*/
#if 0	/* FIXME: running in RAM at the moment */
	clear_bss();
	copy_data();
#endif
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
int tricore_exception(int tclass, int tin, uint32_t pcxi)
{
	csa_t *lower, *upper;

	if ( pcxi == 0 )
	{
		kprintf("Exception class %d, TIN %d in startup code\n");
		for (;;)
			;
	}

	lower = context_to_address(pcxi);
	upper = next_csa(lower);

	kprintf("Exception class %d, TIN %d at PC = 0x%08x, called from 0x%08x\n",
			tclass, tin, lower->context.lower.a11, upper->context.upper.a11);

	kprintf("Registers:\n");
	kprintf("a0  0x%08x    a1  0x%08x    a2  0x%08x    a3  0x%08x\n",
			0, 0, lower->context.lower.a2, lower->context.lower.a3);
	kprintf("a4  0x%08x    a5  0x%08x    a6  0x%08x    a7  0x%08x\n",
			lower->context.lower.a4, lower->context.lower.a5,
			lower->context.lower.a6, lower->context.lower.a7);
	kprintf("a8  0x%08x    a9  0x%08x    a10 0x%08x    a11 0x%08x\n",
			0, 0, upper->context.upper.a10, upper->context.upper.a11);
	kprintf("a12 0x%08x    a13 0x%08x    a14 0x%08x    a15 0x%08x\n",
			upper->context.upper.a12, upper->context.upper.a13,
			upper->context.upper.a14, upper->context.upper.a15);
	kprintf("d0  0x%08x    d1  0x%08x    d2  0x%08x    d3  0x%08x\n",
			lower->context.lower.d0, lower->context.lower.d1,
			lower->context.lower.d2, lower->context.lower.d3);
	kprintf("d4  0x%08x    d5  0x%08x    d6  0x%08x    d7  0x%08x\n",
			lower->context.lower.d4, lower->context.lower.d5,
			lower->context.lower.d6, lower->context.lower.d7);
	kprintf("d8  0x%08x    d9  0x%08x    d10 0x%08x    d11 0x%08x\n",
			upper->context.upper.d8, upper->context.upper.d9,
			upper->context.upper.d10, upper->context.upper.d11);
	kprintf("d12 0x%08x    d13 0x%08x    d14 0x%08x    d15 0x%08x\n",
			upper->context.upper.d12, upper->context.upper.d13,
			upper->context.upper.d14, upper->context.upper.d15);

	for (;;)
		;
}

