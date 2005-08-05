#!/bin/bash
# Plik wylacznie do szybkiego prztestowania kodu!
# Uzyj ./configure i make z kadu!
mv src/DynaLoader.o .
rm -f src/*.o src/*_moc* src/*.d perl.so
mv DynaLoader.o src/

