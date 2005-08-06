use 5.008006;
use ExtUtils::MakeMaker;
$CC = 'g++';
WriteMakefile(
    NAME              => 'Kadu',
    VERSION_FROM      => 'lib/Kadu.pm',
    PREREQ_PM         => {}, # e.g., Module::Name => 1.1
    ($] >= 5.005 ?     
      (ABSTRACT_FROM  => 'lib/Kadu.pm', 
       AUTHOR         => 'P. £ysek <lysek@mail.berlios.de>') : ()),
    LIBS              => [''], 
    DEFINE            => '', 
    INC               => '-I. -I../../../kadu/', 
    'CC'              => $CC,
    'LD'              => '$(CC)',
    'XSOPT'           => '-C++',
    'TYPEMAPS'        => ['perlobject.map' ],
);
