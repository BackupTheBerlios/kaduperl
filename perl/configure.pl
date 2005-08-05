#!/usr/bin/env perl
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
# $Id: configure.pl,v 1.3 2005/08/05 20:39:16 lysek Exp $
use Config;
use strict;
my $NL="\033[0m";
my $ERR="\033[31m*$NL";
my $OK="\033[32m*$NL";
my $WARN="\033[36m*$NL";
my $config="perl_config.h";

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
      exit 1 if $what->{fatal};
  }

}

print "$OK" for (1 .. 10);
print "\n";

my %files = (
  perlso => { file => 'libperl.so', path => "$Config{archlib}/CORE/libperl.so", fatal => 1 },
  dynaa => { file => 'DynaLoader.a', path => "$Config{archlib}/auto/DynaLoader/DynaLoader.a", fatal => 0 },
  externh => { file => 'EXTERN.h', path => "$Config{archlib}/CORE/EXTERN.h", fatal => 1 },
  perlh=> { file => 'perl.h', path => "$Config{archlib}/CORE/perl.h", fatal => 1 }
);

check($files{$_}) for (keys %files);

my $DIR = `find -name perlinterpreter.cpp -print`;
$DIR =~ s/perlinterpreter\.cpp//;
chomp $DIR;

if( -d $DIR )
{
    open CONF,">$DIR/$config" or die "$ERR Can't open $config";
    print CONF "#ifndef _PERL_MOD_CONFIG_H\n";
    print CONF "#define _PERL_MOD_CONFIG_H\n";
    
    if( -e $files{dynaa}{path} )
    {
        print CONF "#define HAVE_DYNALOADER 1\n";
        print "$OK Unpacking $files{dynaa}{path} to $DIR\n";
        ` ar x $files{dynaa}{path}`;
        ` mv DynaLoader.o $DIR`;
    }

    else
    {
        print "$WARN Dynaloader.a not found.. This mean you wont be able to use shared modules in scripts.\n";
    }

    print CONF "#endif // _PERL_MOD_CONFIG_H\n";
    close CONF;
}

else
{
    print "$ERR Can't find module directory!!!\n";    
    exit 1;
}


print "$OK" for (1 .. 10);
print "\n";
