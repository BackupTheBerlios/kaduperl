/********************************************************************************

    Kadu::Perl Module functions.

    Copyright (c) 2005 Piotr £ysek.

    This file is part of Kadu::Perl (Perl module for Kadu im).

    Kadu::Perl is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    Kadu::Perl is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Kadu::Perl; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

********************************************************************************/
// $Id: perl.cpp,v 1.1 2005/08/05 19:26:41 lysek Exp $

#include"perlinit.h"
extern "C" int perl_init()
{
    return Perl::Init();
}

extern "C" int perl_close()
{
    return Perl::Close();
}
