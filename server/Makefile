# -*- MakeFile -*-

all: server

server: main.o
	g++ main.o -o s

main.o: main.cpp protocol.h
	g++ -c main.cpp

clean:
	rm -f *.o s
