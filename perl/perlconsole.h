/********************************************************************************

    Kadu::Perl Qt console header file.

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
// $Id: perlconsole.h,v 1.1 2005/08/05 19:26:41 lysek Exp $

#ifndef PERLCONSOLE_H
#define PERLCONSOLE_H
#include<qtextedit.h>
#include<qapplication.h>
#include<qbrush.h>
#include<qcolor.h>
#include<qfont.h>
#include<qregexp.h>
#include<qsyntaxhighlighter.h>
#include<qhbox.h>
#include<qvbox.h>
#include<qpushbutton.h>
#include<qmainwindow.h>
#include<qfile.h>
#include<iostream>
#include"perlinterpreter.h"
namespace Perl
{

class Syntax: public QSyntaxHighlighter
{
    public:
      Syntax( QTextEdit* te ): QSyntaxHighlighter( te ), color( "#ffffff" ), font( "Helvetica", 10 ) {};

      QFont setDefaultFont( const QFont& _font )
       {
          QFont last( font );
          font = _font;
          return last;
       }

      QColor setDefaultColor( const QColor& _color )
       {
          QColor last( color );
          color = _color;
          return last;
       }

      const QColor& 
       getDefaultColor() const
        {
          return color;
        }

      const QFont&
       getDefaultFont() const
        {
          return font;
        }
    
    protected:
      int highlightParagraph( const QString&, int );
      QColor color;
      QFont font;
};

class Console: public QMainWindow
{
  Q_OBJECT

  public:
    Interpreter* interpreter;
    Console( QWidget * parent = 0, const char * name = 0, const char* caption = "Console", WFlags f = WType_TopLevel );
    QTextEdit* textarea() { return tA; }
    const QTextEdit*const textarea() const { return tA; }
    virtual ~Console();
  
  protected:
    QTextEdit* tA;
    Syntax* syn;
    QFile handler;
  
  public slots:
    void save();
    void saveAs();
    void load();
    void error_in_script(const QString&);  
  protected slots:
    void Run();
    
};
} //namespace Perl
#endif // PERLCONSOLE_H
