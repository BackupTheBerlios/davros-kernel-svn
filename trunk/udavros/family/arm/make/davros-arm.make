# davros-arm.make
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

VPATH += $(UDAVROS_BASE)/family/arm/src

DV_OBJS_ARCH += $(DV_OBJDIR)/arm-startup.$(O)
DV_OBJS_ARCH += $(DV_OBJDIR)/arm-cstartup.$(O)
DV_OBJS_ARCH += $(DV_OBJDIR)/arm-vectors.$(O)

DV_KERN_OBJS_ARCH += $(DV_OBJDIR)/arm-syscall.$(O)
DV_KERN_OBJS_ARCH += $(DV_OBJDIR)/arm-initialregisters.$(O)
DV_KERN_OBJS_ARCH += $(DV_OBJDIR)/arm-ctxtsw.$(O)
DV_KERN_OBJS_ARCH += $(DV_OBJDIR)/arm-irq.$(O)
DV_KERN_OBJS_ARCH += $(DV_OBJDIR)/arm-dispatch-irq.$(O)
DV_KERN_OBJS_ARCH += $(DV_OBJDIR)/arm-dispatch-sec.$(O)

DV_KERN_OBJS_ARCH += $(DV_OBJDIR)/arm-icp-iomap.$(O)
DV_KERN_OBJS_ARCH += $(DV_OBJDIR)/arm-icp-inittimer.$(O)
DV_KERN_OBJS_ARCH += $(DV_OBJDIR)/arm-icp-settimer.$(O)
DV_KERN_OBJS_ARCH += $(DV_OBJDIR)/arm-icp-enableint.$(O)
DV_KERN_OBJS_ARCH += $(DV_OBJDIR)/arm-icp-disableint.$(O)

DV_TOOLPREFIX = arm-elf-

CC = $(DV_TOOLPATH)/bin/$(DV_TOOLPREFIX)gcc
CC_OPT = -g -std=iso9899:1999 -mabi=aapcs -mcpu=arm926ej-s -Wall -c

AS = $(DV_TOOLPATH)/bin/$(DV_TOOLPREFIX)gcc
AS_OPT = -xassembler-with-cpp -g -mabi=aapcs -mcpu=arm926ej-s -Wall -c

LD = $(DV_TOOLPATH)/bin/$(DV_TOOLPREFIX)ld
LD_OPT = -g

AR = $(DV_TOOLPATH)/bin/$(DV_TOOLPREFIX)ar
AR_OPT = crus
