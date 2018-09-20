CC=g++

CFLAGS=-std=gnu++11 -Wall 


all: main

main: bin/main.o 
	$(CC) $(CFLAGS) bin/main.o -o main

bin/main.o: main.cpp
	mkdir -p bin
	$(CC) $(CFLAGS) -c main.cpp -o bin/main.o

clean:
	rm -f *.o ./bin/*.o main *~
	rmdir bin

.PHONY: all clean