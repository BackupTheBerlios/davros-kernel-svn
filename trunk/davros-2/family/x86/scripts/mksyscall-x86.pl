#!/usr/bin/perl -w
#
#	mksyscall-x86.pl
#
#	This little perl script writes a small assembler stub to stdout.
#	The stub uses a system call instruction to enter the kernel with the
#	appropriate system-call index that matches the stub-function's name.
#	On the x86 architecture at least 4 parameters can be passed in registers
#	so the stub function leaves them there.
#
#	Important note: while this script is copyright and released under the GPL,
#	the output is not copyright. The author expressly disclaims all copyright
#	in output producd by this script. It is left as an exercise for the reader
#	(or his lawyer) to discover if and how this fact can be used to create
#	davros-based systems without having to release the whole system under
#	the GPL.  >-)
#
#	Copyright 2008 David Haworth
#
#	This file is part of davros.
#
#	davros is free software: you can redistribute it and/or modify
#	it under the terms of the GNU General Public License as published by
#	the Free Software Foundation, either version 3 of the License, or
#	(at your option) any later version.
#
#	davros is distributed in the hope that it will be useful,
#	but WITHOUT ANY WARRANTY; without even the implied warranty of
#	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#	GNU General Public License for more details.
#
#	You should have received a copy of the GNU General Public License
#	along with davros.  If not, see <http://www.gnu.org/licenses/>.

$name = $ARGV[0];

if ( !defined $name )
{
	print STDERR "Usage: mksyscall-x86.pl SYSCALL-NAME\n";
	exit 1;
}

$lcname = lc($name);
$ucname = uc($name);

print STDOUT "/*  x86-usr-$lcname.s - __dv_usr_$lcname\n";
print STDOUT " *\n";
print STDOUT " *  PUBLIC DOMAIN\n";
print STDOUT " *  The authors of davros expressly disclaim any\n";
print STDOUT " *  copyright in this generated file\n";
print STDOUT "*/\n";
print STDOUT "#include <davros/config.h>\n";
print STDOUT "#include <x86-asm.h>\n";
print STDOUT "#include <davros/syscall.h>\n";
print STDOUT "\n";
print STDOUT "/*==============================================================================\n";
print STDOUT " *  __dv_usr_$lcname - assembler stub for \"$lcname\" system call\n";
print STDOUT " *==============================================================================\n";
print STDOUT "*/\n";
print STDOUT "    .text\n";
print STDOUT "    .balign 4\n";
print STDOUT "\n";
print STDOUT "    .global Dv$name\n";
print STDOUT "    .global __dv_usr_$lcname\n";
print STDOUT "\n";
print STDOUT "Dv$name:\n";
print STDOUT "__dv_usr_$lcname:\n";
print STDOUT "    mov     __DV_SC_$ucname,%esi\n";
print STDOUT "    mov     %esp,%ebp\n";
print STDOUT "    sysenter\n";

exit 0;
