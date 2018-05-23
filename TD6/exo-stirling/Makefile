CC = g++

all: test-stirling

stirling.o: stirling.cpp
	$(CC) -c stirling.cpp

test-stirling: test-stirling.o stirling.o
	$(CC) -Wall stirling.o test-stirling.o -o test-stirling

clean: 
	rm -f test-stirling
	rm -f *.o
