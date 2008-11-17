/*	basic-types.h - basic data types for davros
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

#ifndef __dv_basic_types_h
#define __dv_basic_types_h

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

/* This file defines the basic data types for davros
 *
 * The types are defined using macros to permit the processor families to define their own
 * types if necessary. The default macros in this file will be suitable for most 32-bit and
 * many 16-bit CPUs.
 *
 * The macros will be used in dv-typedefs.h to define C data types.
*/
#include <davros/cpu-characteristics.h>
#define __DV_BASEFILE	types
#include <davros/family-select.h>

/* Natural data types (useful for some purposes)
*/
#ifndef __DV_CHAR_T
#define __DV_CHAR_T		char
#endif

#ifndef __DV_SHORT_T
#define __DV_SHORT_T	short
#endif

#ifndef __DV_INT_T
#define __DV_INT_T		int
#endif

#ifndef __DV_LONG_T
#define __DV_LONG_T		long
#endif

#ifndef __DV_LLONG_T
#define __DV_LLONG_T	long long
#endif

#ifndef __DV_UCHAR_T
#define __DV_UCHAR_T	unsigned char
#endif

#ifndef __DV_USHORT_T
#define __DV_USHORT_T	unsigned short
#endif

#ifndef __DV_UNSIGNED_T
#define __DV_UNSIGNED_T	unsigned
#endif

#ifndef __DV_ULONG_T
#define __DV_ULONG_T	unsigned long
#endif

#ifndef __DV_ULLONG_T
#define __DV_ULLONG_T	unsigned long long
#endif


/* Signed scalar types of fixed size.
*/
#ifndef __DV_INT8_T
#define __DV_INT8_T		char
#endif

#ifndef __DV_INT16_T
#define __DV_INT16_T	short
#endif

#ifndef __DV_INT32_T
#define __DV_INT32_T	long
#endif

#ifndef __DV_INT64_T
#define __DV_INT64_T	long long
#endif


/* Unsigned scalar types of fixed size.
*/
#ifndef __DV_UINT8_T
#define __DV_UINT8_T	unsigned char
#endif

#ifndef __DV_UINT16_T
#define __DV_UINT16_T	unsigned short
#endif

#ifndef __DV_UINT32_T
#define __DV_UINT32_T	unsigned long
#endif

#ifndef __DV_UINT64_T
#define __DV_UINT64_T	unsigned long long
#endif


/* Fastest signed scalar types of at least given size.
*/
#ifndef __DV_FINT8_T
#define __DV_FINT8_T	int
#endif

#ifndef __DV_FINT16_T
#define __DV_FINT16_T	int
#endif

#ifndef __DV_FINT32_T
#define __DV_FINT32_T	long
#endif

#ifndef __DV_FINT64_T
#define __DV_FINT64_T	long long
#endif


/* Fastest unsigned scalar types of at least given size.
*/
#ifndef __DV_FUINT8_T
#define __DV_FUINT8_T	unsigned
#endif

#ifndef __DV_FUINT16_T
#define __DV_FUINT16_T	unsigned
#endif

#ifndef __DV_FUINT32_T
#define __DV_FUINT32_T	unsigned long
#endif

#ifndef __DV_FUINT64_T
#define __DV_FUINT64_T	unsigned long long
#endif


/* Memory-mapped hardware registers.
*/
#ifndef __DV_REG8_T
#define __DV_REG8_T		volatile __dv_uint8_t
#endif

#ifndef __DV_REG16_T
#define __DV_REG16_T	volatile __dv_uint16_t
#endif

#ifndef __DV_REG32_T
#define __DV_REG32_T	volatile __dv_uint32_t
#endif


/* Memory sizes and addresses
*/
#ifndef __DV_SIZE_T
#define __DV_SIZE_T		__dv_uint32_t
#endif

#ifndef __DV_ADDRESS_T
#define __DV_ADDRESS_T	__dv_uint32_t
#endif


/* Stack elements
*/
#ifndef __DV_STACKELEMENT_T

#ifndef __DV_SIZEOF_STACKELEMENT
#error "CPU characteristics file doesn't define __DV_SIZEOF_STACKELEMENT"

#elif	__DV_SIZEOF_STACKELEMENT == 1
#define __DV_STACKELEMENT_T		__dv_uint8_t
#elif	__DV_SIZEOF_STACKELEMENT == 2
#define __DV_STACKELEMENT_T		__dv_uint16_t
#elif	__DV_SIZEOF_STACKELEMENT == 4
#define __DV_STACKELEMENT_T		__dv_uint32_t
#else
#error "Unsupported value of __DV_SIZEOF_STACKELEMENT. Define your own __DV_STACKELEMENT_T"
#endif

#endif


/* Status
*/
#ifndef __DV_STATUS_T
#define	__DV_STATUS_T	__dv_int_t
#endif


/* Below here we define the C data types
 *
 * The types are defined using the macros defined above and/or in the CPU files
*/
#ifndef __DV_ASM

typedef __DV_CHAR_T		__dv_char_t;
typedef __DV_SHORT_T	__dv_short_t;
typedef __DV_INT_T		__dv_int_t;
typedef __DV_LONG_T		__dv_long_t;
typedef __DV_LLONG_T	__dv_llong_t;

typedef __DV_UCHAR_T	__dv_uchar_t;
typedef __DV_USHORT_T	__dv_ushort_t;
typedef __DV_UNSIGNED_T	__dv_unsigned_t;
typedef __DV_ULONG_T	__dv_ulong_t;
typedef __DV_ULLONG_T	__dv_ullong_t;

typedef __DV_INT8_T		__dv_int8_t;
typedef __DV_INT16_T	__dv_int16_t;
typedef __DV_INT32_T	__dv_int32_t;
typedef __DV_INT64_T	__dv_int64_t;

typedef __DV_UINT8_T	__dv_uint8_t;
typedef __DV_UINT16_T	__dv_uint16_t;
typedef __DV_UINT32_T	__dv_uint32_t;
typedef __DV_UINT64_T	__dv_uint64_t;

typedef __DV_FINT8_T	__dv_fint8_t;
typedef __DV_FINT16_T	__dv_fint16_t;
typedef __DV_FINT32_T	__dv_fint32_t;
typedef __DV_FINT64_T	__dv_fint64_t;

typedef __DV_FUINT8_T	__dv_fuint8_t;
typedef __DV_FUINT16_T	__dv_fuint16_t;
typedef __DV_FUINT32_T	__dv_fuint32_t;
typedef __DV_FUINT64_T	__dv_fuint64_t;

typedef __DV_REG8_T		__dv_reg8_t;
typedef __DV_REG16_T	__dv_reg16_t;
typedef __DV_REG32_T	__dv_reg32_t;

typedef __DV_SIZE_T			__dv_size_t;
typedef __DV_ADDRESS_T		__dv_address_t;
typedef __DV_STACKELEMENT_T	__dv_stackelement_t;
typedef __DV_STATUS_T		__dv_status_t;

#endif

#endif
