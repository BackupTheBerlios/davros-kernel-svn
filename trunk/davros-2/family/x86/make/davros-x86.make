# davros-x86.make
#
# Copyright 2009 David Haworth
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

VPATH += $(DAVROS_BASE)/family/x86/src

DV_OBJS_ARCH += $(DV_OBJDIR)/x86-startup.$(O)
DV_OBJS_ARCH += $(DV_OBJDIR)/x86-cstartup.$(O)
#DV_OBJS_ARCH += $(DV_OBJDIR)/x86-vectors.$(O)

#DV_KERN_OBJS_ARCH += $(DV_OBJDIR)/x86-syscall.$(O)
#DV_KERN_OBJS_ARCH += $(DV_OBJDIR)/x86-initialregisters.$(O)
#DV_KERN_OBJS_ARCH += $(DV_OBJDIR)/x86-ctxtsw.$(O)
#DV_KERN_OBJS_ARCH += $(DV_OBJDIR)/x86-irq.$(O)
#DV_KERN_OBJS_ARCH += $(DV_OBJDIR)/x86-dispatch-irq.$(O)
#DV_KERN_OBJS_ARCH += $(DV_OBJDIR)/x86-dispatch-sec.$(O)

#DV_KERN_OBJS_ARCH += $(DV_OBJDIR)/x86-icp-iomap.$(O)
#DV_KERN_OBJS_ARCH += $(DV_OBJDIR)/x86-icp-inittimer.$(O)
#DV_KERN_OBJS_ARCH += $(DV_OBJDIR)/x86-icp-settimer.$(O)
#DV_KERN_OBJS_ARCH += $(DV_OBJDIR)/x86-icp-stoptimer.$(O)
#DV_KERN_OBJS_ARCH += $(DV_OBJDIR)/x86-icp-enableint.$(O)
#DV_KERN_OBJS_ARCH += $(DV_OBJDIR)/x86-icp-disableint.$(O)

DV_TOOLPREFIX = 

CC = $(DV_TOOLPATH)/bin/$(DV_TOOLPREFIX)gcc
CC_OPT = -g -std=iso9899:1999 -Wall -c

AS = $(DV_TOOLPATH)/bin/$(DV_TOOLPREFIX)gcc
AS_OPT = -xassembler-with-cpp -g -Wall -c

LD = $(DV_TOOLPATH)/bin/$(DV_TOOLPREFIX)ld
LD_OPT = -g

AR = $(DV_TOOLPATH)/bin/$(DV_TOOLPREFIX)ar
AR_OPT = crus
