/*	asc-tty-drv.c - ASC tty driver for davros.
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
 *	This file contains definitions for the ASC tty driver
 *
*/

#include "davros/kernel.h"
#include "drv/asc-tty-drv.h"
#include "drv/asc-drv.h"
#define __STDIO_PRIVATE
#include "stdio.h"

/*
 *	asc_tty_create() - create a tty device for a tricore ASC
 *
 *	This function allocates the data structure for the device,
 *	then intialises it (calling th generic tty driver's initialisation
 *	function to intitialise the generic parts.
 *	Finally the interrupts service routines are connected, the ASC
 *	is initialised and the interrupts are enabled.
*/
__asc_tty_drv_t *asc_tty_create
(	char *name,
	tricore_asc_t *_asc,
	int _inum_base,
	int pisel
)
{
	uint32_t ps;

	__asc_tty_drv_t *dev = __davros_getmem(sizeof(__asc_tty_drv_t));
	if ( dev == NULL )
		return NULL;

	dev->asc = _asc;
	dev->inum_base = _inum_base;
	dev->txrun = 0;

	if ( __davros_tty_create(&dev->tty, name) == NULL )
	{
		__davros_freemem(dev, sizeof(__asc_tty_drv_t));
		return(NULL);
	}

	dev->tty.ospeed = 0;	/* ispeed & ospeed must be the same */
	dev->tty.hwctrl = asc_tty_control;	/* my control function */

	asc_init(dev->asc, pisel);
	asc_params(dev->asc, dev->tty.params);
	asc_baud(dev->asc, dev->tty.ispeed);

	__davros_attach_interrupt(dev->inum_base+ASCTTY_INUM_OFFSET_RXD,
				asc_tty_rx_interrupt, dev);
	__davros_attach_interrupt(dev->inum_base+ASCTTY_INUM_OFFSET_TXD,
				asc_tty_tx_interrupt, dev);
	__davros_attach_interrupt(dev->inum_base+ASCTTY_INUM_OFFSET_ERR,
				asc_tty_err_interrupt, dev);

	ps = disable_interrupts();

	dev->asc->asc_rsrc = ISR_CLRR | ISR_SRE | ISR_TOS_CPU |
						(dev->inum_base+ASCTTY_INUM_OFFSET_RXD);
	dev->asc->asc_tbsrc = ISR_CLRR | ISR_SRE | ISR_TOS_CPU |
						(dev->inum_base+ASCTTY_INUM_OFFSET_TXD);
	dev->asc->asc_esrc = ISR_CLRR | ISR_SRE | ISR_TOS_CPU |
						(dev->inum_base+ASCTTY_INUM_OFFSET_ERR);

	restore_interrupts(ps);

	return(dev);
}

/*
 *	asc_intr_enable() - enable interrupts
*/
void asc_intr_enable(tricore_asc_t *asc)
{
	asc->asc_rsrc |= ISR_SRE;
	asc->asc_esrc |= ISR_SRE;
	asc->asc_tbsrc |= ISR_SRE;
}

/*
 *	asc_tty_delete() - delete an ASC-tty device
 *
 *	This function shuts down the hardware and frees the data memory.
*/
void asc_tty_delete(__asc_tty_drv_t *dev)
{
	/* FIXME: to do */
}

/*
 *	asc_tty_rx_interrupt() - rx interrupt handler
 *
 *	Handles received-a-character interrupts 
*/
void asc_tty_rx_interrupt(void *_dev)
{
	__asc_tty_drv_t *dev = (__asc_tty_drv_t *)_dev;
	__davros_tty_cin(&dev->tty, dev->asc->asc_rbuf);
}

/*
 *	asc_tty_tx_interrupt() - tx interrupt handler
 *
 *	Handles transmitted-a-character interrupt
*/
void asc_tty_tx_interrupt(void *_dev)
{
	__asc_tty_drv_t *dev = (__asc_tty_drv_t *)_dev;
	int c = __davros_tty_cout(&dev->tty);
	if ( c == __DAVROS_TTY_EOF )
		dev->txrun = 0;
	else
	{
		dev->txrun = 1;
		dev->asc->asc_tbuf = c;
	}
}

/*
 *	asc_tty_err_interrupt() - error interrupt handler
 *
 *	Handles receiver-error interrupts. For the moment we just
 *	ignore them.
*/
void asc_tty_err_interrupt(void *_dev)
{
	__asc_tty_drv_t *dev = (__asc_tty_drv_t *)_dev;

	dev->asc->asc_con &= ~(ASC_CON_PE | ASC_CON_FE | ASC_CON_OE);
}

/*
 *	asc_tty_control() - hwctrl function for tty
 *
 *	This function updates the hardware with changes to the device
 *	settings.
*/
int asc_tty_control(__davros_tty_t *_dev, int func, int param)
{
	__asc_tty_drv_t *dev = (__asc_tty_drv_t *)_dev;
	uint32_t ps;

	switch ( func )
	{
	case __DAVROS_TTY_SPEED_CHANGE:
		asc_baud(dev->asc, dev->tty.ispeed);
		break;

	case __DAVROS_TTY_PARAM_CHANGE:
		asc_params(dev->asc, dev->tty.params);
		break;

	case __DAVROS_TTY_KICKOUT_CHAR:
		ps = disable_interrupts();
		if ( dev->txrun == 0 )
		{
			int c = __davros_tty_cout(&dev->tty);
			if ( c != __DAVROS_TTY_EOF )
			{
				dev->txrun = 1;
				dev->asc->asc_tbuf = c;
			}
		}
		restore_interrupts(ps);
		break;

	default:
		return(__DAVROS_SYSERR);
		break;
	}
	return(__DAVROS_OK);
}
