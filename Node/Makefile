#
# Makefile för NEO/Node, GNU GCC (g++)
#
# Filkataloger där andra delar av programet finns.
EDGE = ../Edge
NETWORK = ../Network
SET = ../Set
NODE = ../Node

# Kompilator
#CCC = g++
CC = g++

# Kompilatorflaggor, lägg till '-g' om kompilering för avlusning ska göras.
CCFLAGS += -std=c++11 -pedantic -Wall -Wextra

# Preprocessorflaggor, -I lägger till en filkatalog i inkluderingssökvägen.
CPPFLAGS += -I. -I.. -I$(NODE) -I$(SET) -I$(EDGE)

# Länkflaggor - Fix för att lösa lokala (IDA) problem med C++ länkbibliotek.
LDFLAGS += -L/sw/gcc-$(GCC4_V)/lib -static-libstdc++

Node.o: Node.h Node.cc Position.h $(EDGE)/Edge.h $(SET)/Set.h
	$(CC) $(CPPFLAGS) $(CCFLAGS) -c Node.cc

Position.o: Position.h
	$(CC) $(CPPFLAGS) $(CCFLAGS) -c Position.cc

# 'make clean' tar bort objektkodsfiler och 'core' (minnesdump).
clean:
	@ \rm -rf *.o core

# 'make zap' tar även bort det körbara programmet och reservkopior (filer
# som slutar med tecknet '~').
#zap: clean
#	@ \rm -rf <programnamn> *~

# Se upp vid eventuell ändring, '*' får absolut inte finnas för sig!!!
#
# '@' medför att kommandot inte skrivs ut på skärmen då det utförs av make.
# 'rm' är ett alias för 'rm -i' på IDA:s system, '\rm' innebär att "original-
# versionen", utan flaggan '-i', används. 
