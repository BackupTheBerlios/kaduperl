/********************************************************************************

    Kadu::Perl Initialization header file.

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
// $Id: perlinit.h,v 1.1 2005/08/05 19:44:40 lysek Exp $

#ifndef PERL_INIT_H
#define PERL_INIT_H
#include"perlinterpreter.h"
#include"perlconsole.h"
#include"qmenubar.h"
namespace Perl
{

   // Interpreter *PERL;
   // Console *CONSOLE;
   // int MenuId;
   // QPopupMenu* Menu;

    int Init();
    int Close();


} // namespace Perl
#endif // PERL_INIT_H
