all: test

test: test_graph.o graph.o
	g++ -o test $^

test_graph.o: test_graph.cpp graph.h
	g++ -c $<

graph.o: graph.cpp queue.cpp
	g++ -c $<

clean:
	rm -f *.o test