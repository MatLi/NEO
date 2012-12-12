#
# Makefile för NEO, GNU GCC (g++)
#
# Filkataloger där andra delar av programet finns.
NODE = ../Node
EDGE = ../Edge
NETWORK = ../Network
SET = ../Set


# Kompilator
#CCC = g++
CC = g++

# Kompilatorflaggor, lägg till '-g' om kompilering för avlusning ska göras.
CCFLAGS += -std=c++11 -pedantic -Wall -Wextra

# Preprocessorflaggor, -I lägger till en filkatalog i inkluderingssökvägen.
CPPFLAGS += -I$(NODE) -I$(SET) -I$(EDGE) -I$(NETWORK)

# Länkflaggor - Fix för att lösa lokala problem med C++ länkbibliotek.
LDFLAGS += -L/sw/gcc-$(GCC4_V)/lib -static-libstdc++

# Objektkodsmoduler som ingår i den kompletta kalkylatorn.
OBJECTS = $(EDGE)/Edge.o $(NODE)/Node.o $(NODE)/Position.o $(NETWORK)/Network.o ne_test.o

# Huvudmål - skapas med kommandot 'make' eller 'make kalkylator'.
ne_test: $(OBJECTS) node edge network Makefile
	$(CC) $(CPPFLAGS) $(CCFLAGS) $(LDFLAGS) -o ne_test $(OBJECTS)

# Delmål (flaggan -c avbryter innan länkning, objektkodsfil erhålls)
ne_test.o: ne_test.cc $(NODE)/Node.h $(EDGE)/Edge.h $(SET)/Set.h  $(NETWORK)/Network.h
	$(CC) $(CPPFLAGS) $(CCFLAGS) -c ne_test.cc

node:
	cd ../Node; make

edge:
	cd ../Edge; make

network:
	cd ../Network; make

# 'make clean' tar bort objektkodsfiler och 'core' (minnesdump).
clean:
	@ \rm -rf *.o core

# 'make zap' tar även bort det körbara programmet och reservkopior (filer
# som slutar med tecknet '~').
zap: clean
	@ \rm -rf kalkylator *~

# Se upp vid eventuell ändring, '*' får absolut inte finnas för sig!!!
#
# '@' medför att kommandot inte skrivs ut på skärmen då det utförs av make.
# 'rm' är ett alias för 'rm -i' på IDA:s system, '\rm' innebär att "original-
# versionen", utan flaggan '-i', används. 
