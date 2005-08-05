#!/bin/bash
# Plik wylacznie do szybkiego prztestowania kodu!
# Uzyj ./configure i make z kadu!
mv DynaLoader.o ../
rm -f *.o *_moc* *.d ../perl.so
mv ../DynaLoader.o .

