################################################################################
#
#    Kadu::Perl Configure file.
#
#    Copyright (c) 2005 Piotr £ysek.
#
#    This file is part of Kadu::Perl (Perl module for Kadu im).
#
#    Kadu::Perl is free software; you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation; either version 2 of the License, or
#    (at your option) any later version.
#
#    Kadu::Perl is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with Kadu::Perl; if not, write to the Free Software
#    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
#
################################################################################

use Config;
use strict;
my $NL="\033[0m";
my $ERR="\033[31m*$NL";
my $OK="\033[32m*$NL";

sub check(%)
{
  my $what = shift;
  print "$OK Checking for $what->{file} ... ";

  if( -e $what->{path} )
  {
      print "found in $what->{path}\n";
  }

  else
  {
      print "not found\n";
      exit 1;
  }

}

print "$OK" for (1 .. 10);
print "\n";

my %files = (
  perlso => { file => 'libperl.so', path => "$Config{archlib}/CORE/libperl.so" },
  dynaa => { file => 'DynaLoader.a', path => "$Config{archlib}/auto/DynaLoader/DynaLoader.a" },
  externh => { file => 'EXTERN.h', path => "$Config{archlib}/CORE/EXTERN.h" },
  perlh=> { file => 'perl.h', path => "$Config{archlib}/CORE/perl.h" }
);

check($files{$_}) for (keys %files);

my $DIR = `find -name perlinterpreter.cpp -print`;
$DIR =~ s/perlinterpreter\.cpp//;
chomp $DIR;
if( -d $DIR )
{
    print "$OK Unpacking $files{dynaa}{path} to $DIR\n";
    ` ar x $files{dynaa}{path}`;
    ` mv DynaLoader.o $DIR`;
}

else
{
    print "$ERR Can't find module directory!!!\n";
    
    exit 1;
}


print "$OK" for (1 .. 10);
print "\n";
