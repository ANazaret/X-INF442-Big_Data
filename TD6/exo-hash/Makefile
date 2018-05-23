CC = g++

all: test-hash-q12-exch test-hash-q3-hash 

hash.o: hash.cpp hash.hpp
	$(CC) -std=c++11 -c hash.cpp
	
packet.o: packet.cpp packet.hpp
	$(CC) -std=c++11 -c packet.cpp

test-hash-q12-exch.o: test-hash-q12-exch.cpp 
	$(CC) -std=c++11 -c test-hash-q12-exch.cpp  

test-hash-q12-exch: test-hash-q12-exch.o packet.o
	$(CC) -std=c++11 -Wall test-hash-q12-exch.o packet.o -o test-hash-q12-exch

test-hash-q3-hash.o: test-hash-q3-hash.cpp
	$(CC) -std=c++11 -c test-hash-q3-hash.cpp

test-hash-q3-hash: test-hash-q3-hash.o hash.o 
	$(CC) -std=c++11 -Wall test-hash-q3-hash.o hash.o -o test-hash-q3-hash

clean: log-model.txt
	rm -f test-hash-q12-exch test-hash-q3-hash
	rm -f *.o
	cp log-model.txt logfile.txt
