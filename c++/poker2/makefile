all: omahacomp;
CPPFLAGS=-static-libstdc++ -static-libgcc
omahacomp: omahacomp.o
	g++ $(CPPFLAGS) -o omahacomp omahacomp.o

omahacomp.o: omahacomp.cpp
	g++ $(CPPFLAGS) -c omahacomp.cpp

clean:
	rm -f *.o omahacomp
