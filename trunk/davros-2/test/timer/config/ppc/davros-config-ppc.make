# davros-config-ppc.make - make configuration for davros synchronous test
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
ifneq ($(DV_FAMILY), ppc)
  $(error DV_FAMILY is not set correctly for this makefile)
endif

# Which compiler/assembler/linker are we using, and where is it?
DV_TOOL = gnu
DV_TOOLPATH = /gnu/4.3.2-powerpc-eabi

# Linker scripts
DV_LDSCRIPT = config/davros.ld
