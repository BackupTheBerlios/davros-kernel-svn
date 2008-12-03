# davros-config.make - make configuration for ppc build of udavros
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

# Where are the davros sources?
UDAVROS_BASE = /where/is/udavros

# Which CPU family are we building for, and (optional) which member of the family?
DV_FAMILY ?= arm

# Where are the project source files?
VPATH += src

# Where to put the object files and library files?
DV_GENDIR = gen
DV_OBJDIR = obj
DV_LIBDIR = lib
DV_BINDIR = bin

# Space-separated list of include directories
DV_INCDIR = config/$(DV_FAMILY) config

# Which files are needed as part of this project?
DV_OBJS = $(DV_OBJDIR)/template-prj.$(O)

include config/$(DV_FAMILY)/davros-config-$(DV_FAMILY).make
