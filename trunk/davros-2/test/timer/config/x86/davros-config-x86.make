# davros-config-x86.make - make configuration for davros synchronous test
#
# (c) 2008 David Haworth
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

# Which CPU family and CPU are we compiling for?
ifneq ($(DV_FAMILY), x86)
  $(error DV_FAMILY is not set correctly for this makefile)
endif

# Which compiler/assembler/linker are we using, and where is it?
DV_TOOL = gnu

ifeq ($(wildcard /home/dave/gnu/x86-4.4.1/bin/i386-linux-elf-gcc),)
  DV_TOOLPATH = /usr
  DV_TOOLPREFIX = 
else
  DV_TOOLPATH = /home/dave/gnu/x86-4.4.1
  DV_TOOLPREFIX = i386-linux-elf-
endif

# Linker scripts
DV_LDSCRIPT = config/x86/davros.ld
