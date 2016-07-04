FLAGS = -O2 -DSIXTYFOURBITS -pthread
SRC = mummer.cpp qsufsort.c sparseSA.cpp fasta.cpp
LDFLAGS = -L/opt/local/lib -lboost_serialization-mt
# LDFLAGS = /opt/local/lib/libboost_serialization-mt.a

all: create_mummer_index mummer

#create_mummer_index: create_mummer_index.o qsufsort.o sparseSA.o fasta.o /usr/lib/libboost_serialization.a

create_mummer_index: create_mummer_index.o qsufsort.o sparseSA.o fasta.o
	g++ -lpthread $(FLAGS) $^ -o $@ $(LDFLAGS)

#mummer: mummer.o qsufsort.o sparseSA.o fasta.o /usr/lib/libboost_serialization.a

mummer: mummer.o qsufsort.o sparseSA.o fasta.o
	g++ -lpthread $(FLAGS) $^ -o $@ $(LDFLAGS)

.cpp.o:
	g++ $(FLAGS) -Wall -c $<

.c.o:
	gcc $(FLAGS) -Wall -c $<

# .PHONY assures clean is exected even if there is a file "./clean" in
# the directory. The same for doc.
.PHONY: clean doc
doc: 
	doxygen

clean: 
	rm -f *.o *~ .depend mummer create_mummer_index

# Create all the dependencies between the source files. 
.depend:
	g++ -MM $(SRC) > .depend

# The - prevents make from complaining about a missing .depend
-include .depend
