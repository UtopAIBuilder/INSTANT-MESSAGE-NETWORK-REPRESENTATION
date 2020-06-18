a.out: client.o impl.o randGraphGen.o
	g++ -g client.o impl.o randGraphGen.o

client.o: client.c header.h
	gcc -g -c client.c

impl.o: impl.c header.h
	gcc -g -c impl.c
randGraphGen.o: randGraphGen.cpp
	g++ -g -c randGraphGen.cpp
