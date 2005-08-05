/********************************************************************************

    Kadu::Perl Qt console.

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
// $Id: perlconsole.cpp,v 1.1 2005/08/05 19:44:40 lysek Exp $

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
#include<qpopupmenu.h>
#include<qmenubar.h>
#include<qmainwindow.h>
#include<qfiledialog.h>
#include<iostream>
#include"perlconsole.h"
#include"perlinterpreter.h"
#include"qerrormessage.h"
#include<qmessagebox.h>


/////////////////////////////////////////////
// Perl::Syntax 
/////////////////////////////////////////////

/////////////////////////////////////////////
// Callback klasy QTextEdit --> podswietlanie skladni perla.
// Poki co to dziala liniowo i ogolnie lipnie, ale lepszy rydz niz nic;]
int Perl::Syntax::highlightParagraph( const QString & text, int state )
{

  state = state;

  //if( tokens.empty() ) return 0; 
  
  // Ustawiamy defaultowy kolor paragrafu...
  setFormat(0, text.length(), color );
 
  
  int found(0), Index(0);

// normal hajlajt.
#define NHLIGHT(regxp,color) \
  while( ( found = text.find( regxp, Index ) ) >= 0 ) \
    { \
        int len( regxp.matchedLength() ); \
        setFormat( found, len, QColor(color) ); \
        Index = found +len; \
    } \
  found = 0; Index = 0;
  
  // Slowa kluczowe
  static QRegExp keywords(
   "("
   "\\bfor\\b|\\bif\\b|\\belse\\b|\\belsif\\b|\\bunless\\b|\\bwhile\\b|\\bforeach\\b|\\beach\\b|\\bcontinue\\b|\\blast\\b|\\bmy\\b|"
   "\\blocal\\b|\\bour\\b|\\bgoto\\b|\\breturn\\b|\\blast\\b|\\bnext\\b|\\bredo\\b|\\bchomp\\b|\\bchop\\b|\\bchr\\b|"
   "\\bcrypt\\b|\\bindex\\b|\\blc\\b|\\blcfirst\\b|\\bpos\\b|\\bquotemeta\\b|\\bsplit\\b|\\bstudy\\b|\\babs\\b|" 
   "\\batan2\\b|\\bcos\\b|\\bexp\\b|\\bhex\\b|\\bint\\b|\\blog\\b|\\boct\\b|\\brand\\b|\\bsin\\b|\\bsqrt\\b|\\bsrand\\b|"
   "\\bsplice\\b|\\bunshift\\b|\\bshift\\b|\\bpush\\b|\\bpop\\b|\\bsplit\\b|\\bjoin\\b|\\breverse\\b|\\bgrep\\b|\\bmap\\b|" 
   "\\bsort\\b|\\bunpack\\b|\\blength\\b|\\bord\\b|\\bpack\\b|\\breverse\\b|\\brindex\\b|\\bsprintf\\b|\\bsubstr\\b|"
   "\\buc\\b|\\bucfirst\\b|\\bcarp\\b|\\bconfess\\b|\\bcroak\\b|\\bdbmclose\\b|\\bdbmopen\\b|\\bdie\\b|\\bsyscall\\b|"
   "\\binmode\\b|\\bclose\\b|\\bclosedir\\b|\\beof\\b|\\bfileno\\b|\\bgetc\\b|\\blstat\\b|\\bprint\\b|\\bprintf\\b|" 
   "\\breaddir\\b|\\breadline\\b|\\breadpipe\\b|\\brewinddir\\b|\\bselect\\b|\\bstat\\b|\\btell\\b|\\btelldir\\b|\\bwrite\\b|"
   "\\bfcntl\\b|\\bflock\\b|\\bioctl\\b|\\bopen\\b|\\bopendir\\b|\\bread\\b|\\bseek\\b|\\bseekdir\\b|\\bsysopen\\b|"
   "\\bsysread\\b|\\bsysseek\\b|\\bsyswrite\\b|\\btruncate\\b|\\bchdir\\b|\\bchmod\\b|\\bchown\\b|\\bchroot\\b|\\bglob\\b|"
   "\\blink\\b|\\bmkdir\\b|\\breadlink\\b|\\brename\\b|\\bcaller\\b|\\bdie\\b|\\bdump\\b|\\beval\\b|\\bexit\\b|"
   "\\bwantarray\\b|\\buse\\b|\\brequire\\b|\\balarm\\b|\\bexec\\b|\\bfork\\b|\\bgetpgrp\\b|\\bgetppid\\b|"
   "\\bgetpriority\\b|\\bkill\\b|\\bpipe\\b|\\bsetpgrp\\b|\\bsetpriority\\b|\\bsleep\\b|\\bsystem\\b|\\btimes\\b|"
   "\\bwait\\b|\\bwaitpid\\b|\\brmdir\\b|\\bsymlink\\b|\\bumask\\b|\\bunlink\\b|\\butime\\b|\\baccept\\b|\\bbind\\b|"
   "\\bconnect\\b|\\bgetpeername\\b|\\bgetsockname\\b|\\bgetsockopt\\b|\\blisten\\b|\\brecv\\b|\\bsend\\b|\\bsetsockopt\\b|"
   "\\bshutdown\\b|\\bsocket\\b|\\bsocketpair\\b|\\bmsgctl\\b|\\bmsgget\\b|\\bmsgrcv\\b|\\bmsgsnd\\b|\\bsemctl\\b|"
   "\\bsemget\\b|\\bsemop\\b|\\bshmctl\\b|\\bshmget\\b|\\bshmread\\b|\\bendhostent\\b|\\bendnetent\\b|\\bendprotoent\\b|"
   "\\bendservent\\b|\\bgethostbyaddr\\b|\\bgethostbyname\\b|\\bgethostent\\b|\\bgetnetbyaddr\\b|\\bgetnetbyname\\b|"
   "\\bgetnetent\\b|\\bgetprotobyname\\b|\\bgetprotobynumber\\b|\\bgetprotoent\\b|\\bgetservbyname\\b|\\bgetservbyport\\b|" 
   "\\bgetservent\\b|\\bsethostent\\b|\\bsetnetent\\b|\\bsetprotoent\\b|\\bsetservent\\b|\\bshmwrite\\b|"
   "\\bgetpwuid\\b|\\bgetpwnam\\b|\\bgetpwent\\b|\\bsetpwent\\b|\\bendpwent\\b|\\bgetgrent\\b|\\bgetgrgid\\b|"
   "\\bgetlogin\\b|\\bgetgrnam\\b|\\bsetgrent\\b|\\bendgrent\\b|\\bgmtime\\b|\\blocaltime\\b|\\btime\\b|\\btimes\\b|"
   "\\bwarn\\b|\\bformline\\b|\\breset\\b|\\bscalar\\b|\\bdelete\\b|\\bprototype\\b|\\block\\b|\\bnew\\b"
   ")");
  NHLIGHT(keywords,"#aa8406")
  
  // begin i end
  static QRegExp BE("(\\bBEGIN\\b|\\bEND\\b)");
  NHLIGHT(BE,"#7a0578")
  
  // liczby
  static QRegExp digits("\\b\\d+\\b"); 
  NHLIGHT(digits,"#ab0003")

  // <*>
  static QRegExp streams("<([A-Z_a-z])+>");
  NHLIGHT(streams,"#08b0c3")
  

  // s///
  static QRegExp s("s([^A-Z_a-z $]).*\\1.*\\1[a-z]*");
  NHLIGHT(s,"#aa8406")

  // m//
  static QRegExp m("m([^A-Z_a-z $]).*\\1[a-z]*");
  NHLIGHT(m,"#aa8406")
  
  // //
  static QRegExp slashes("/.*/[a-z]*");
  NHLIGHT(slashes,"#aa8406")
  
   // qq//
  static QRegExp qq("q{1,2}([^A-Z_a-z$]).*\\1");
  NHLIGHT(qq,"#8a0d0f")

  // Cudzyslow
  static QRegExp squote("'[^']*'");
  NHLIGHT(squote,"#8a0d0f")
  
  // Podwojny 
  static QRegExp dquote("\"[^\"]*\"");
  NHLIGHT(dquote,"#8a0d0f")

  // Zmienne
  static QRegExp vars("([\\$@%]|\\$#)(\\$*)((\"|\'|/|\\||=|-|~|\\^|[1-9]|&|`|\\+|\\.|\\\\|,|\\?|\\*|\\[|\\]|;|!)|"
                      "([A-Z_a-z])+([A-Z_a-z1-9])*)");
  NHLIGHT(vars,"#00adb9")
  
  // Komentarz
  static QRegExp comment("#.*");
  NHLIGHT(comment,"#001684");
  return 0;
}


/////////////////////////////////////////////
// Perl::Console 
/////////////////////////////////////////////


/////////////////////////////////////////////
// Tworzy nowa konsole
Perl::Console::Console( QWidget * parent, const char * name, 
                        const char* caption, WFlags f): 
  QMainWindow( parent, name, f )
{
    setCaption( caption );

    interpreter = new Interpreter( this, "__Perl__" ); 
    tA = new QTextEdit(this, "editor_screen");
    syn = new Syntax( tA );
    QPopupMenu* edit = new QPopupMenu( this );
    
    menuBar()->insertItem( "&Edit", edit );
    
    tA->setFocus();
    setCentralWidget( tA );
    
    edit->insertItem( "&Run", this, SLOT(Run()), CTRL + Key_R );
    edit->insertItem( "C&lear", tA, SLOT(clear()), CTRL + Key_L );
    edit->insertItem( "L&oad", this, SLOT(load()), CTRL + Key_O ); 
    edit->insertItem( "&Save", this, SLOT(save()), CTRL + Key_S );
    edit->insertItem( "Save &as", this, SLOT(saveAs()), CTRL + Key_A );
    
    if( interpreter->isOk() )
     {
        connect( interpreter, SIGNAL(_error_(const QString&)), this, SLOT(error_in_script(const QString&)) );
     }

    tA->setWordWrap( QTextEdit::WidgetWidth );
    tA->setTextFormat( Qt::PlainText );
    tA->setPaper( QBrush( "#4b4b4b" ) );
    tA->setColor( QColor( syn->getDefaultColor() ) );
    tA->setCurrentFont( QFont( "Courier", 10 ) );
    tA->setAutoFormatting( QTextEdit::AutoAll );
    tA->setTabStopWidth( 4 );
}


/////////////////////////////////////////////
// Destruktor
Perl::Console::~Console()
{
    delete syn; 
    delete tA; 
    delete interpreter;
}


/////////////////////////////////////////////
// Slot uruchamiajacy kod perla aktualnie znajdujacy sie w buforze QTextEdit
void Perl::Console::Run()
{
    Perl::Script* screen = new Perl::Script( 1, tA->text());
    interpreter->run_script( screen );
    delete screen;
}


/////////////////////////////////////////////
// Slot wczytuje zawartosc pliku do buforu QTextEdit
void Perl::Console::load()
{
    QString name = QFileDialog::getOpenFileName( ".", "Perl scripts (*.pl)", this, 
                                                 "open file dialog", "Choose script" );
    if( name.isEmpty() ) return;
    QErrorMessage error( this, "Error");
    
    QFile file(name);
    if( file.exists() )
     {
        if( !file.open( IO_ReadOnly ) )
         {
            error.message("Can't open specified file :(");
            return;
         }
        tA->setText( file.readAll() );
        file.close();
     }

    else { error.message("File doesnt exists!"); return; }
    handler.setName(file.name());
}

/////////////////////////////////////////////
// Zapisuje pliku w wybranej sciezce
void Perl::Console::saveAs()
{
    QString name = QFileDialog::getSaveFileName( ".", "Perl scripts (*.pl)", this,
                                                 "save file dialog", "Save script" );
    if( name.isEmpty() ) return;
    QErrorMessage error( this, "Error");
    QFile file(name);

    if( file.exists() )
     {
        if( QMessageBox::question( this, "File exists", "File already exists, overwrite?", 
              QMessageBox::Ok, QMessageBox::Cancel ) == QMessageBox::Cancel ) return;
     }

    if( !file.open( IO_WriteOnly ) )
     {
        error.message("Can't write that file :(");
        return;
     }

    file.writeBlock( tA->text(), tA->text().length() );
    file.close();
    handler.setName(file.name());
}


/////////////////////////////////////////////
// Zapisuje aktualnie wczytany plik
void Perl::Console::save()
{
    QErrorMessage error( this, "Error");

    if( !handler.exists() ) { saveAs(); return; }
    if( !handler.open( IO_WriteOnly ) )
     {
        error.message("Can't write that file :(");
        return;
     }
    handler.writeBlock( tA->text(), tA->text().length() );
    handler.close();
}


/////////////////////////////////////////////
// Slot do polaczenia sie z Perl::Interpreter::_error_(const QString&)
void Perl::Console::error_in_script(const QString& error_string)
{
    QMessageBox::warning( this, "Error in script", error_string, QMessageBox::Ok, QMessageBox::NoButton);
}


/////////////////////////////////////////////
// Test .1 
/////////////////////////////////////////////

int main ( int argc, char* argv[] )
{
    QApplication qt( argc, argv );
    Perl::Console PC(0, "testowa konsola");
    //PerlScript scr("script.pl");
    //SV* ret = i.run_script(scr);
    //STRLEN n_a;
    //std::cout << "perl ret: " << SvPV(ret,n_a) << std::endl;
    qt.setMainWidget( &PC );
    
    PC.resize(800, 600);
    PC.show();
    
    if( PC.interpreter->isBroken() ) {
      std::cerr << "I will die now. " << std::endl;
      PC.close();
      return 1;
    }
    return qt.exec();
}

