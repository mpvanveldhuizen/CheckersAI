FLAGS = -std=c++11 -O3 -Wall -pedantic -fopenmp -march=native -mtune=native

all: net.o node.o board.o gen.o main.cpp
	g++ $(FLAGS) node.o net.o gen.o board.o main.cpp -o gen

board.o: board.cpp board.h
	g++ $(FLAGS) board.cpp -c

net.o: net.cpp net.h 
	g++ $(FLAGS) net.cpp -c

node.o: node.cpp node.h
	g++ $(FLAGS) node.cpp -c

gen.o: gen.cpp gen.h
	g++ $(FLAGS) gen.cpp -c

clean:
	rm *.o gen 2> /dev/null
