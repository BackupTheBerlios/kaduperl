################################################################################
#
#    Kadu::Perl Core functions.
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
# $Id: Kadu.pm,v 1.1 2005/08/05 19:26:41 lysek Exp $
package Kadu;
use warnings;
use strict;
use Symbol qw(delete_package);

#XXX Nastepny razem wrzucajac jakies dane dla perla 10 razy sprawdzaj \0!!!
#XXX \0 to Z³o!!!
sub eval_data {
  
  die "Give me 2 arguments dude" if(scalar@_ < 2);
  
  my ($data, $id) = @_;
  my $eval = "package $id;\nsub handler { \n\t$data\n }\n";
 
  #open TTT, ">__data";
  #print TTT $eval, $/;
  #close TTT;
  
  {
      my($data,$id);
      eval $eval;
  }
 
  die $@ if $@; 
  
  my $ret;
  eval { $ret = $id->handler; };
  die $@ if $@;
  delete_package($id);
  return $ret;
}

sub eval_file {
  my ($filename, $id) = @_;
  
  local *FH;
  open FH, $filename or die "File not found: $filename";

  local($/) = undef;
  my $data = <FH>;
  close FH;
  local($/) = "\n";

  return eval_data($data, $id);
}

1;
__END__
