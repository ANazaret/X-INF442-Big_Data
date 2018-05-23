CC = g++

all: test-spiral-q1-print test-spiral-q2-next test-spiral-q3-shp test-spiral-q4-dis test-spiral-q5-adj

spiral.o: spiral.cpp spiral.hpp
	$(CC) -c -Wall spiral.cpp

Cell.o: Cell.cpp Cell.hpp
	$(CC) -c -Wall Cell.cpp

Memory.o: Memory.cpp Memory.hpp
	$(CC) -c -Wall Memory.cpp

test-spiral-q1-print: test-spiral-q1-print.o spiral.o Cell.o Memory.o
	$(CC) -Wall test-spiral-q1-print.o spiral.o Cell.o Memory.o -o test-spiral-q1-print

test-spiral-q2-next: test-spiral-q2-next.o spiral.o Cell.o Memory.o
	$(CC) -Wall test-spiral-q2-next.o spiral.o Cell.o Memory.o -o test-spiral-q2-next

test-spiral-q3-shp: test-spiral-q3-shp.o spiral.o Cell.o Memory.o
	$(CC) -Wall test-spiral-q3-shp.o spiral.o Cell.o Memory.o -o test-spiral-q3-shp

test-spiral-q4-dis: test-spiral-q4-dis.o spiral.o Cell.o Memory.o
	$(CC) -Wall test-spiral-q4-dis.o spiral.o Cell.o Memory.o -o test-spiral-q4-dis
	
test-spiral-q5-adj: test-spiral-q5-adj.o spiral.o Cell.o Memory.o
	$(CC) -Wall test-spiral-q5-adj.o spiral.o Cell.o Memory.o -o test-spiral-q5-adj
	
clean: 
	rm -f test-spiral-q1-print test-spiral-q2-next test-spiral-q3-shp test-spiral-q4-dis test-spiral-q5-adj
	rm -f *.o
