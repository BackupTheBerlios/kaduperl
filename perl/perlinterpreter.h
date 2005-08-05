/********************************************************************************

    Kadu::Perl Perl interpreter header.

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
// $Id: perlinterpreter.h,v 1.1 2005/08/05 19:26:41 lysek Exp $

#ifndef PERLINTERPRETER_H
#define PERLINTERPRETER_H
extern "C" {
#include"EXTERN.h"
#include"perl.h"
}
#include<qobject.h>
#include<qfile.h>
#include<qstring.h>
#include<qobjectlist.h>

extern "C" void boot_DynaLoader (pTHX_ CV* cv);

namespace Perl 
{

class Script: public QFile
{
    public:
      Script( const QString& name ): QFile( name ), _script_ready( 0 ) { assign( name ); }
      Script( int Ready, const QString& code ): _script_ready( 1 ), perl_code( code ) { assign( "", Ready=1 ); }
      virtual ~Script();
      void assign( const QString& name, int ready = 0 );
      
    protected:
      // Wskazniki do wszystkich zaladowanych skryptow. 
      static QValueList<Script*> scripts; 
      
      // Identyfikacja
      QString _script_name;
      QString _script_path;
      int _script_id;
      QString _script_id_string;

      int _script_ready;

    public:
      QString perl_code;

      // Metody statyczne
      static Script* byName(const QString&);
      static Script* atIndex(int i) { return scripts[i]; }
       
      // Reszta
      const QString& scrname() const { return _script_name; }
      const QString& scrpath() const { return _script_path; }
      const int scrid() const { return _script_id; }
      const QString& stringid() const { return _script_id_string; }
      const int& isReady() const { return _script_ready; }
      void setReady(int f) { _script_ready = f; }
      
};


class Interpreter: public QObject
{
  Q_OBJECT
    
    public:
      Interpreter(QObject* parent = 0, const char* name = 0);
      virtual ~Interpreter();

    public:
      PerlInterpreter* my_perl;
      static void xs_init(pTHX);
   
    protected:
      static const int EVAL_ERROR;
      static const int INTERPRETER_ALLOC_ERROR;
      static const int INTERPRETER_PARSE_ERROR;
      QString _EVAL_ERROR;

    public slots:
      void run_script(Script*);
    
    signals:
      void _error_( const QString& );

    public:
      bool isBroken() const { 
        return ((INTERPRETER_ALLOC_ERROR==(_ERROR&INTERPRETER_ALLOC_ERROR))||
                 INTERPRETER_PARSE_ERROR==(_ERROR&INTERPRETER_PARSE_ERROR)); }
      bool isOk() const { return !isBroken(); }
      bool wasEvalOk() const { return !(EVAL_ERROR==(_ERROR&EVAL_ERROR)); }
      bool wasEvalBroken() const { return !wasEvalOk(); }
      const QString& evalError() const { return _EVAL_ERROR; }

   
    protected:
      int _ERROR;

};
} // namespace Perl
#endif // PERLINTERPRETER_H
