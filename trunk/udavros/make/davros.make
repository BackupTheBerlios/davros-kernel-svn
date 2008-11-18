# davros.make
#
# Copyright 2008 David Haworth
#
# This file is part of davros.
#
# davros is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# davros is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with davros.  If not, see <http://www.gnu.org/licenses/>.
#
# $Id$

.PHONY: all lib exe dirs

all:	lib bin

clean:
	-rm $(DV_BINDIR)/davros.elf $(DV_LIBDIR)/*.$(A) $(DV_OBJDIR)/*.$(O) 

include $(UDAVROS_BASE)/family/$(DV_FAMILY)/make/davros-$(DV_FAMILY).make

# File suffixes
O = o
A = a
S = s

VPATH += $(UDAVROS_BASE)/src/davros

# Davros kernel object files: miscellaneous
DV_KERN_OBJS += $(DV_OBJDIR)/startup.$(O)

# Davros kernel object files: memory pool
DV_KERN_OBJS += $(DV_OBJDIR)/initmem.$(O)
DV_KERN_OBJS += $(DV_OBJDIR)/getmem.$(O)
DV_KERN_OBJS += $(DV_OBJDIR)/freemem.$(O)

# Davros kernel object files: object management
DV_KERN_OBJS += $(DV_OBJDIR)/initobj.$(O)
DV_KERN_OBJS += $(DV_OBJDIR)/registerobj.$(O)
DV_KERN_OBJS += $(DV_OBJDIR)/deregisterobj.$(O)

# Davros kernel object files: queue management
DV_KERN_OBJS += $(DV_OBJDIR)/dequeue.$(O)
DV_KERN_OBJS += $(DV_OBJDIR)/enqueue.$(O)
DV_KERN_OBJS += $(DV_OBJDIR)/insert.$(O)

DV_KERN_OBJS += $(DV_OBJDIR)/initproc.$(O)
DV_KERN_OBJS += $(DV_OBJDIR)/dispatch.$(O)
DV_KERN_OBJS += $(DV_OBJDIR)/ready.$(O)
DV_KERN_OBJS += $(DV_OBJDIR)/schedule.$(O)
DV_KERN_OBJS += $(DV_OBJDIR)/die.$(O)
DV_KERN_OBJS += $(DV_OBJDIR)/unknowncall.$(O)

DV_KERN_OBJS += $(DV_OBJDIR)/initint.$(O)
DV_KERN_OBJS += $(DV_OBJDIR)/unusedint.$(O)
DV_KERN_OBJS += $(DV_OBJDIR)/registerint.$(O)
DV_KERN_OBJS += $(DV_OBJDIR)/unregisterint.$(O)

DV_KERN_OBJS += $(DV_OBJDIR)/inittime.$(O)
DV_KERN_OBJS += $(DV_OBJDIR)/marktime.$(O)
DV_KERN_OBJS += $(DV_OBJDIR)/tick.$(O)

DV_KERN_OBJS += $(DV_OBJDIR)/resume.$(O)
DV_KERN_OBJS += $(DV_OBJDIR)/suspend.$(O)
DV_KERN_OBJS += $(DV_OBJDIR)/chprio.$(O)
DV_KERN_OBJS += $(DV_OBJDIR)/getpid.$(O)
DV_KERN_OBJS += $(DV_OBJDIR)/create.$(O)
DV_KERN_OBJS += $(DV_OBJDIR)/exit.$(O)
DV_KERN_OBJS += $(DV_OBJDIR)/kill.$(O)
DV_KERN_OBJS += $(DV_OBJDIR)/init.$(O)
DV_KERN_OBJS += $(DV_OBJDIR)/syscall.$(O)
DV_KERN_OBJS += $(DV_KERN_OBJS_ARCH)

# Davros userland objects
DV_USR_OBJS += $(DV_USR_OBJS_ARCH)

# Davros system objects
DV_OBJS += $(DV_OBJS_ARCH)

lib:	$(DV_LIBDIR)/libdavros.a $(DV_LIBDIR)/libdvusr.a

bin:	$(DV_BINDIR)/davros.elf

dirs:
	mkdir -p $(DV_OBJDIR)
	mkdir -p $(DV_LIBDIR)
	mkdir -p $(DV_BINDIR)

$(DV_LIBDIR)/libdavros.a:	$(DV_KERN_OBJS)
	$(AR) $(AR_OPT) $@ $(DV_KERN_OBJS)

$(DV_LIBDIR)/libdvusr.a:	$(DV_USR_OBJS)
	$(AR) $(AR_OPT) $@ $(DV_USR_OBJS)

$(DV_BINDIR)/davros.elf:	$(DV_OBJDIR) $(DV_OBJS) 
	$(LD) $(LD_OPT) -o $@ $(DV_OBJS) -L $(DV_LIBDIR) -ldavros -ldvusr -T $(DV_LDSCRIPT)

CC_INC = $(addprefix -I,$(DV_INCDIR))
CC_INC += -I$(UDAVROS_BASE)/family/$(DV_FAMILY)/include
CC_INC += -I$(UDAVROS_BASE)/include

AS_INC = $(CC_INC)
AS_DEF = $(CC_DEF)

$(DV_OBJDIR)/%.o:	%.c
	$(CC) $(CC_OPT) $(CC_DEF) $(CC_INC) -o $@ $<

$(DV_OBJDIR)/%.o:	%.s
	$(AS) $(AS_OPT) $(AS_DEF) $(AS_INC) -o $@ $<
