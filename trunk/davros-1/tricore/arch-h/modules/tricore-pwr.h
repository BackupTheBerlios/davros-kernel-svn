/*	tricore-pwr.h - Tricore PWR module description
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
 *	This file contains a description of Tricore's PWR module which
 *	contains the PLL control registers, watchdog, etc.
 *
*/

#if !defined(__tricore_pwr_h)
#define __tricore_pwr_h

#include "modules/tricore-mod.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(__ASSEMBLER__)

typedef struct tricore_pwr
{
	tricore_mod_t		pwr_hdr;
    volatile uint32_t	reserved1[1];
    volatile uint32_t	pwr_rstreq;		/* Reset Request Register */
    volatile uint32_t	pwr_rstsr;		/* Reset Status Register */
    volatile uint32_t	reserved2[2];
    volatile uint32_t	pwr_wdtcon0;	/* Watchdog Timer Control Register 0 */
    volatile uint32_t	pwr_wdtcon1;	/* Watchdog Timer Control Register 1 */
    volatile uint32_t	pwr_wdtsr;		/* Watchdog Timer Status Register */
    volatile uint32_t	pwr_nmisr;		/* NMI Status Register */
    volatile uint32_t	pwr_pmcon;		/* Power Management Control Register */
    volatile uint32_t	pwr_pmcsr;		/* Power Management Control & Status Register */
    volatile uint32_t	reserved3[2];	/* Reserved */
    volatile uint32_t	pwr_pllclc;		/* PLL Clock Control Register */
    volatile uint32_t	pwr_eckclc;		/* External Clock Control Register FIXME: gone? */
    volatile uint32_t	pwr_icuclc;		/* ICU Clock Control Register FIXME: gone? */
} tricore_pwr_t;

#endif

/*	The PWR registers sometimes need to be accessed from assembler modules. */
#define PWRREG(x)	(PWR_BASE+(x))
#define PWRCLC		PWRREG(0x00)	/* FIXME - name? */
#define	PWRID		PWRREG(0x08)
#define RSTREQ		PWRREG(0x10)
#define RSTSR		PWRREG(0x14)
#define WDTCON0		PWRREG(0x20)
#define WDTCON1		PWRREG(0x24)
#define WDTSR		PWRREG(0x28)
#define NMISR		PWRREG(0x2c)
#define PMCON		PWRREG(0x30)
#define PMCSR		PWRREG(0x34)
#define PLLCLC		PWRREG(0x40)
#define ECKCLC		PWRREG(0x44)
#define ICUCLC		PWRREG(0x48)

/* PLL Clock Control Register */
#define PLL_LOCK		0x00000100      /* State of PLL Lock Signal */
#define PLL_N_FAC		0x00007000      /* State of PLL N-Factor Signals */
#define PLL_BYPASS		0x00008000      /* State of PLL Bypass Signal */
#define PLL_K_DIV		0x00070000      /* PLL K-Divider */
#define PLL_K_DIVval(c)	((c) << 16)

/*	These macros calculate the n-factor and k-factor for given
 *	N_FAC and K_DIV values (0..7 in both cases)
*/
#define PLL_KFAC(i)		(((i) == 1) ? 16 : (((i) > 4) ? ((i) + 3) : ((i) + 2)))
#define PLL_NFAC(i)		((i) + 8)

/* External / ICU Clock Control Register */
#define DISR            0x00000001      /* Disable Request Bit */
#define DISS            0x00000002      /* Disable Status Bit */
#define SUSPEN          0x00000004      /* Suspend Enable Bit */
#define EXRDIS          0x00000008      /* External Request Disable Bit */
#define SBWE            0x00000010      /* Suspend Write Enable Bit */
#define DIVCLK_MSK      0x00FF0000      /* Clock Divider */

/* Watchdog Timer Control Register 0 */
#define ENDINIT         0x00000001      /* End of Initialisation Control Bit*/
#define WDTLCK          0x00000002      /* Lock Bit */
#define WDTHPW0_MSK     0x0000000C      /* Hardware Password 0 */
#define WDTHPW1_MSK     0x000000F0      /* Hardware Password 1 */
#define WDTPW_MSK       0x0000FF00      /* User Definable Password */
#define WDTREL_MSK      0xFFFF0000      /* Reload Value for the Watchdog Timer */

/* Watchdog Timer Control Register 1 */
#define WDTIR           0x00000004      /* Input Frequency Request Control Bit */
#define WDTDR           0x00000008      /* Disable Request Control Bit */
#define SCKCLR_MSK      0x00000700      /* Self Check Clear Request Bits */

/* Watchdog Timer Status Register */
#define WDTAE           0x00000001      /* Access Error Status Flag */
#define WDTOE           0x00000002      /* Overflow Error Status Flag */
#define WDTIS           0x00000004      /* Input Clock Status Bit */
#define WDTDS           0x00000008      /* Enable / Disable Bit */
#define WDTTO           0x00000010      /* Time Out Period Indicating Flag */
#define WDTPR           0x00000020      /* Reset Prewarning Flag */
#define SCKERR_MSK      0x0000FF00      /* Self Check Error Bits */
#define WDTTIM_MSK      0xFFFF0000      /* Contents of Watchdog Timer */

/* Power Management Control & Status Register */
#define REQSLP_MSK      0x00000003      /* Request Sleep Mode */
#define REQSLP_RUN      0x00000000      /* Run Mode */
#define REQSLP_IDLE     0x00000001      /* Request Idle Mode */
#define REQSLP_SLEEP    0x00000002      /* Request Sleep Mode */
#define PMST_MSK        0x00000700      /* Power Management State */
#define PMST_WAIT       0x00000000      /* Wait for PLL Clock */
#define PMST_RUN        0x00000100      /* Normal Run Mode */
#define PMST_IDLER      0x00000200      /* Idle Request */
#define PMST_IDLEA      0x00000300      /* Idle Acknowledged */
#define PMST_SLEEP      0x00000400      /* Sleep Mode */
#define PMST_DSLEEP     0x00000500      /* Deep Sleep Mode */

/* Power Management Control Register */
#define DSRW            0x00000001      /* Reset on Wake Up from Deep Sleep */
#define DSREQ           0x00000002      /* Deep Sleep Request */

/* Reset Status Register */
#define RSSTM           0x00000001      /* Reset Status System Timer */
#define RSDBG           0x00000002      /* Reset Status Debug Unit */
#define RSEXT           0x00000004      /* Reset Status for External Devices */
#define HWCFG_MSK       0x00070000      /* Status of CFG[2..0] */
#define HW_OCDS_E       0x00080000      /* Status of the OCDS_E Pin */
#define HW_BRK_IN       0x00100000      /* Status of the BRK_IN Pin */
#define PWORST          0x08000000      /* Power On Reset Indicator */
#define HDRST           0x10000000      /* Hardware Reset Indicator */
#define SFTRST          0x20000000      /* Software Reset Indicator */
#define WDTRST          0x40000000      /* Watchdog Reset Indicator */
#define PWDRST          0x80000000      /* Power Down / Wake Up Indicator */

/* Reset Request Register */
#define RRSTM           0x00000001      /* System Timer Reset Request */
#define RRDBG           0x00000002      /* Debug Unit Reset Request */
#define RREXT           0x00000004      /* External Devices Reset Request */
#define SWCFG_MSK       0x00070000      /* Software Boot Configuration */
#define SW_OCDS_E       0x00080000      /* Software OCDS_E Signal Boot Value */
#define SW_BRK_IN       0x00100000      /* Software BRK_IN Signal Boot Value */
#define SWBOOT          0x01000000      /* Software Boot Configuration Selection */

#ifdef __cplusplus
}
#endif

#endif
