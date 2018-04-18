CC = g++

testComplex0.o: testComplex0.cpp Complex.hpp
	$(CC) -c testComplex0.cpp

testComplex2.o: testComplex2.cpp Complex.hpp
	$(CC) -c testComplex2.cpp

testComplex1.o: testComplex1.cpp Complex.hpp
	$(CC) -c testComplex1.cpp

testComplex3.o: testComplex3.cpp Complex.hpp
	$(CC) -c testComplex3.cpp

Complex.o: Complex.cpp Complex.hpp
	$(CC) -c Complex.cpp
	
testComplex0: testComplex0.o Complex.o
	$(CC) Complex.o testComplex0.o -o testComplex0

testComplex1: testComplex1.o Complex.o
	$(CC) Complex.o testComplex1.o -o testComplex1

testComplex2: testComplex2.o Complex.o
	$(CC) Complex.o testComplex2.o -o testComplex2

testComplex3: testComplex3.o Complex.o
	$(CC) Complex.o testComplex3.o -o testComplex3

Atom.o: Atom.cpp Atom.hpp
	$(CC) -c Atom.cpp
	
Rectangle.o: Rectangle.cpp Rectangle.hpp Atom.hpp
	$(CC) -c Rectangle.cpp
	
QuadTree.o: QuadTree.cpp QuadTree.hpp Rectangle.hpp Atom.hpp
	$(CC) -c QuadTree.cpp
	
testQuadTree1.o: testQuadTree1.cpp QuadTree.hpp Rectangle.hpp Atom.hpp
	$(CC) -c testQuadTree1.cpp
	
testQuadTree2.o: testQuadTree2.cpp QuadTree.hpp Rectangle.hpp Atom.hpp
	$(CC) -c testQuadTree2.cpp
	
testQuadTree1: testQuadTree1.o QuadTree.o Rectangle.o Atom.o
	$(CC) testQuadTree1.o QuadTree.o Rectangle.o Atom.o -o testQuadTree1

testQuadTree2: testQuadTree2.o QuadTree.o Rectangle.o Atom.o
	$(CC) testQuadTree2.o QuadTree.o Rectangle.o Atom.o -o testQuadTree2

clean: 
	rm -f testComplex0 testComplex1 testComplex2 testComplex3 
	rm -f *.o
	
