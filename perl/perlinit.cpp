/********************************************************************************

    Kadu::Perl Initialization.

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
// $Id: perlinit.cpp,v 1.1 2005/08/05 19:26:41 lysek Exp $

#include"kadu.h"
#include"qpopupmenu.h"
#include"perlinterpreter.h"
#include"perlconsole.h"
#include"perlinit.h"

//Perl::Interpreter* Perl::PERL = 0;
//Perl::Console* Perl::CONSOLE = 0;
//int Perl::MenuId = 0;
//QPopupMenu* Perl::Menu = 0;
Perl::Interpreter *PERL;
Perl::Console *CONSOLE;
int MenuId;
QPopupMenu* Menu;

int Perl::Init()
{

#ifdef WAIT_A_MOMENT
    PERL = new Interpreter(0, "Standalone perl interpreter");
    
    if( PERL->isBroken() )
     {
        delete PERL;
        return 1;
     }
#endif // WAIT_A_MOMENT

    CONSOLE = new Console(0, "Perl console", "Perl console" );
    if( CONSOLE->interpreter->isBroken() )
     {
        delete CONSOLE;
        return 1;
     }

    Menu = new QPopupMenu(0, "Perl module menu");
    Menu->insertItem("&Open console", CONSOLE, SLOT(show()));
    MenuId = kadu->menuBar()->insertItem( "&Perl", Menu );
    return 0;
}

int Perl::Close()
{
    kadu->menuBar()->removeItem( MenuId );
    delete CONSOLE;
    //delete PERL;
}

