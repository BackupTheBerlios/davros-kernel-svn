/*	config.h - davros configuration - include user config, apply defaults
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

#ifndef __dv_config_h
#define __dv_config_h

#ifdef __DV_IDENT
__DV_IDENT("$Id$")
#endif

/* Include the user's config file
*/
#include <davros-config.h>

/* DV_CFG_CPUFAMILY --- choose the CPU family that we're building Davros for.
 *
 * The default value for this is just arbitrarily chosen. You should choose the
 * correct architecture for the microcontroller that you want to use. The list of supported
 * architectures can be found in processors.h
*/
#ifndef DV_CFG_CPUFAMILY
#error "DV_CFG_CPUFAMILY is not defined. Check your davros-config.h file"
#define DV_CFG_CPUFAMILY		__DV_CPUFAMILY_PPC
#endif

/* DV_CFG_CPU --- choose the CPU that we're building Davros for.
 *
 * The default value for this is just arbitrarily chosen. You should choose the
 * correct value for the microcontroller that you want to use. The list of supported
 * processors can be found in (arch)-processors.h
*/
#ifndef DV_CFG_CPU
#error "DV_CFG_CPU is not defined. Check your davros-config.h file"
#define DV_CFG_CPU				__DV_PPC_5554
#endif

/* DV_CFG_USE_MAGIC --- enable the "magic number" field in the object structure.
 *
 * The default is not to use magic numbers. Using magic numbers provides a little extra
 * confidence that the object you're looking at really is an object and not something else.
 * The only true test of course is if the object table contains the object, but to determine
 * that needs access to the kernel's variables.
*/
#ifndef DV_CFG_USE_MAGIC
#define DV_CFG_USE_MAGIC		0
#endif

/* DV_CFG_N_OBJECTS --- the number of objects in the object registration table
 *
 * This constant determines the number of objects in the kernel's internal object
 * registry. Every time an object is created it is registered in this table. Processes,
 * devices, semaphores etc. are all objects. You need to make sure that the table is
 * big enough, otherwise process creation or semaphore creation could fail.
 * The default value of 32 is sufficient for fairly small systems.
*/
#ifndef DV_CFG_N_OBJECTS
#define DV_CFG_N_OBJECTS		32
#endif

/* DV_CFG_NULLSTACK_LEN --- the length (number of stack elements, not bytes) of null's stack
 *
 * This constant determines exactly how many stackelements to reserve for the null process'
 * stack. The null process is what performs all the initialisation, both before and after
 * initialising the kernel. Afterwards, it is the process that runs whenever there is nothing
 * else to do. Note: DV_CFG_EXTRASTACK is not added onto this figure.
 * The default value of 128 is probably enough for most purposes.
*/
#ifndef DV_CFG_NULLSTACK_LEN
#define DV_CFG_NULLSTACK_LEN	128
#endif

/* DV_CFG_KERNSTACK_LEN --- the length ((number of stack elements, not bytes) of the kernel's stack
 *
 * This constant determines exactly how many stackelements to reserve for the kernel's stack.
 * The kernel switches to the kernel stack whenever an interrupt or trap occurs (including
 * the system call trap). All kernel functionality, including interrupts, runs on this stack.
*/
#ifndef DV_CFG_KERNSTACK_LEN
#define DV_CFG_KERNSTACK_LEN	256
#endif

/* DV_CFG_STACK_SPARE --- the amount of stack to reserve for C stack frames.
 *
 * This constant determines how many stack elements to leave unused when setting an initial stack
 * pointer. Some processors (e.g. PowerPC) expects the calling function to reserve some stack
 * frame into which the function can store data without having to build a stack frame. This
 * value represents such an area at the very beginning of the stack.
 * The default value of 0 is used for most processors.
*/
#ifndef DV_CFG_STACK_SPARE
#define DV_CFG_STACK_SPARE		0
#endif

/* DV_CFG_EXTRASTACK --- how much extra stack to allocate per process
 *
 * This constant determines how many extra bytes to add to the specified stack requirement
 * when creating a new process. The extra is for kernel-specific purposes like boundary marks
 * etc.
*/
#ifndef DV_CFG_EXTRASTACK
#define DV_CFG_EXTRASTACK		0
#endif

/* DV_CFG_HEAPBASE, DV_CFG_HEAPSIZE --- where and how big the heap is
 *
 * These two constants determine the initial amount of memory for the heap.
 * There are no default values; these two macros *must* be defined in davros-config.h.
*/
#ifndef DV_CFG_HEAPBASE
#error "DV_CFG_HEAPBASE is not defined"
#endif
#ifndef DV_CFG_HEAPSIZE
#error "DV_CFG_HEAPSIZE is not defined"
#endif

/* DV_CFG_USERINIT --- user-defined initialisation code
 *
 * If this macro is defined it is called from __dv_startup just after the kernel has
 * been initialised. The macro should be defined like this:
 * #define DV_CFG_USERINIT()	<some code here>
 * The default is not to perform any user-defined initialisation
*/
#ifndef DV_CFG_USERINIT
#define DV_CFG_USERINIT()
#endif

/* DV_CFG_USERPROCESS --- user-defined process to start at startup
 *
 * If this macro is defined, it is used as the value of a dv_process_t structure
 * to create a new process at startup. The process is started with priority 1
 * and is made runnable (which means in practice that it runs immediately.)
 * The value of the macro is simply the initialiser of the structure, without the { and },
 * like in the example below.
 * See process-config.h for definition of the fields.
 *
 * There is no default value; if this macro is not defined, no process is started.
 * If this macro and DV_CFG_USERINIT are both defined, DV_CFG_USERINIT() is called before
 * the process is started.
*/
#if 0
#define DV_CFG_USERPROCESS	"myProcess", myFunction, 0, __DV_NULL, 512, 0
#endif

/* DV_CFG_USERNULL --- user-defined null process
 *
 * If this macro is defined, it is called in the null process. The code placed in this
 * macro must never return and must never make a system-call that results in the process
 * being non-runnable.
 *
 * The default value is simply a dynamic stop.
*/
#ifndef DV_CFG_USERNULL
#define DV_CFG_USERNULL()	for (;;)
#endif

/* DV_CFG_MINSLEEP --- minimum number of ticks for a process to sleep
 *
 * The minimum number of ticks for which DvSleep will actually put a process to sleep
 * and set the timer. If the parameter to DvSleep() is less than this value, DvSleep()
 * returns immediately without doing anything. This is not an error case.
 *
 * The default value of 1 is always safe. Setting 0 is not recommended. Raising the
 * value can bring performance benefits, depending on how fast the timer ticks
 * relative to the CPU.
*/
#ifndef DV_CFG_MINSLEEP
#define DV_CFG_MINSLEEP		1
#endif

/* DV_CFG_MAXSLEEP --- maximum number of ticks for a process to sleep
 *
 * The maximum number of ticks for which a process can sleep. Attempting to sleep for
 * longer than this in one step is an error, and DvSleep() return __DV_ERR.
 * The value should be chosen to avoid the situation where there is a process that has
 * been asleep for a long time and is about to wake up, and another process decides to
 * sleep for a long time. The sum of the two times, needed to insert the 2nd process into
 * the delta list, is bigger than a 32-bit unsigned can hold. Interrupt locking times
 * need to be taken int account too, because the wakeup of the first process might be
 * overdue.
 *
 * The default value of 2000000000 should be fine in nearly all cases. Even with a
 * 100 MHz clock this represents 20 seconds.
*/
#ifndef DV_CFG_MAXSLEEP
#define DV_CFG_MAXSLEEP		2000000000
#endif

/* =================================================================================================
 * Below this point there are no more configuration macros.
 * Most of the rest are (temporary) translations from DV_CFG_ macros to internal __DV_ macros
*/
#define __DV_FAMILY			DV_CFG_CPUFAMILY
#define __DV_CPU			DV_CFG_CPU
#define __DV_EXTRASTACK		DV_CFG_EXTRASTACK
#define __DV_USE_MAGIC		DV_CFG_USE_MAGIC

#endif
