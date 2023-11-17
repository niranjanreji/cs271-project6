all: test

test: test_graph.o graph.o
	g++ -std=c++11 -o test $^

test_graph.o: test_graph.cpp graph.h
	g++ -std=c++11 -c $<

graph.o: graph.cpp queue.cpp
	g++ -std=c++11 -c $<

clean:
	rm -f *.o test