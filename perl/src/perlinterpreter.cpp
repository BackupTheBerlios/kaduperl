/********************************************************************************

    Kadu::Perl Perl interpreter.

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
// $Id: perlinterpreter.cpp,v 1.2 2005/08/05 20:39:16 lysek Exp $

extern "C" {
#include"EXTERN.h"
#include"perl.h"
}
#include"perl_config.h"
#include"perlinterpreter.h"
#include<qstring.h>
#include<qfile.h>
#include<qstringlist.h>
#include<iostream>
#include<qregexp.h>


/////////////////////////////////////////////
// Perl::Script 
/////////////////////////////////////////////

/////////////////////////////////////////////
// Statyczne skladowe
QValueList<Perl::Script*> Perl::Script::scripts = QValueList<Perl::Script*>();



/////////////////////////////////////////////
// Skrypt konstruowany jest na dwa sposoby, bedzie uruchamiany z kodu lub
// bezposrednio z pliku.
void Perl::Script::assign(const QString& n, int Ready )
{
    scripts.push_back( this );  
    _script_id = scripts.size() -1;
   
    if( Ready )
     {
        _script_id_string = "Kadu::Console::Text";
        setName("__NoFile__");
        return;
     }

    else
     {
        // dzieki temu mozna wyczyscic symbole po idzie (Symbol.pm)
        _script_id_string = "Kadu::Script::" + n;
        _script_id_string.replace(QRegExp("([^A-Z_a-z/1-9:])"),"_");
        _script_id_string.replace("/","::");
     }

    if( Ready ) return;

    QString file;

    if( !isOpen() && name() != n ) setName( n );
    
    if( n.contains("/") ) {
        QStringList all = QStringList::split( "/", n );
        file = all.back();
        all.erase(--(all.end()));
        _script_path = all.join("/");
    }

    else { file = n; _script_path = "."; }


    if( file.right( 3 ) == ".pl" )
     {
        _script_name = file.left( file.length() -3 );
     }
    
    else _script_name = file;
  
}

/////////////////////////////////////////////
// Destruktor
Perl::Script::~Script()
{
    scripts.erase(scripts.at(_script_id));
}


/////////////////////////////////////////////
// Zwraca skrypt po nazwie (bez sciezki .pl)
Perl::Script* Perl::Script::byName(const QString& name)
{
    QValueList<Script*>::iterator it = scripts.begin();
    for(; it != scripts.end() && (*it)->scrname() != name; ++it )
    return ( it == scripts.end() ? 0 : *it );
    return reinterpret_cast<Perl::Script*>(0);
}


/////////////////////////////////////////////
// Perl::Interpreter 
/////////////////////////////////////////////


/////////////////////////////////////////////
// Statyczne skladowe
const int Perl::Interpreter::EVAL_ERROR = 1;
const int Perl::Interpreter::INTERPRETER_ALLOC_ERROR = 2;
const int Perl::Interpreter::INTERPRETER_PARSE_ERROR = 4;


/////////////////////////////////////////////
// Instaluje perla
Perl::Interpreter::Interpreter(QObject* parent, const char* name): QObject( parent, name )
{
    _ERROR = 0;
    char* core_args[] = { "", "-e", "0" };
    
    my_perl = perl_alloc();
    
    if(!my_perl) { 
        
        _ERROR |= INTERPRETER_ALLOC_ERROR; 
        
        // Mozna w konstruktorze??
        // emit _error_( "Can't install perl!" );
        
        
        return; 
    }

    perl_construct(my_perl);
    
#ifdef HAVE_DYNALOADER
    if( perl_parse(my_perl, xs_init, 3, core_args, 0) ) { 
#else
    if( perl_parse(my_perl, 0, 3, core_args, 0) ) {
#endif
        _ERROR |= INTERPRETER_PARSE_ERROR;
        
        // emit _error_( "Can't initialize perl!" );
         
        return;
    }
    
    require_pv("./Kadu.pm");
    // U kolegi na slacku10(perl5.8.4) to segfaultuje:
    // load_module( 0, newSVpv("Kadu", 4), 0 );
}


/////////////////////////////////////////////
// Czysci pamiec
Perl::Interpreter::~Interpreter()
{
   if(my_perl) perl_destruct(my_perl);
   if(my_perl) perl_free(my_perl);
}


/////////////////////////////////////////////
// Dzieki temu mozna uzywac dynamicznych modulow (.so)
#ifdef HAVE_DYNALOADER
extern "C" void Perl::Interpreter::xs_init(pTHX)
{
   
    char *file = __FILE__;
    
    dXSUB_SYS
      newXS("DynaLoader::boot_DynaLoader", boot_DynaLoader, file); 
}
#endif

/////////////////////////////////////////////
// Odpala skrypt z pliku, lub kod perla jestli script->isReady()
void Perl::Interpreter::run_script(Perl::Script* script)
{
    // Tu jest doc -> http://search.cpan.org/dist/perl/pod/perlembed.pod#Fiddling_with_the_Perl_stack_from_your_C_program

    dSP;
    
    _ERROR ^= (~EVAL_ERROR);
    
    // Przy bezposrednim zapodawaniu do makr perla
    // zdarzaly sie jakies dziwne segfauly... ch.. wie czemu.
    const char*  _sid = script->stringid().ascii();
    int _sid_len = script->stringid().length(); 
    const char* _scode = script->perl_code.ascii();
    int _scode_len = script->perl_code.length();
    const char* _sname = script->name().ascii();
    int _sname_len = script->name().length();

    if( !_sid_len || !_scode_len || !_sname_len ) 
      {
          _EVAL_ERROR = "Script structure is broken!";
          _ERROR |= EVAL_ERROR;
          emit _error_(_EVAL_ERROR);
          return;
      }

    ENTER;
    SAVETMPS;

    PUSHMARK(SP);

    // Sciezka .pl / kod na stos
    if( script->isReady() )
      XPUSHs( sv_2mortal( newSVpv( _scode, _scode_len ) ) );
    else XPUSHs( sv_2mortal( newSVpv( _sname, _sname_len ) ) );
    
    // `package' na stos
    XPUSHs(sv_2mortal(newSVpv(_sid, _sid_len)));

    PUTBACK;

    call_pv( (script->isReady()?"Kadu::eval_data":"Kadu::eval_file"), G_EVAL|G_DISCARD ); 

    SPAGAIN;
    
    if( SvTRUE(ERRSV) )
     {   
        _ERROR |= EVAL_ERROR;
        _EVAL_ERROR = SvPV(ERRSV, PL_na);
        emit _error_(_EVAL_ERROR);
     }

    PUTBACK;
    FREETMPS;
    LEAVE;
}

