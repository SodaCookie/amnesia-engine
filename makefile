CXX=g++
CFLAGS=-c -Wall --std=c++11
OBJECTS=main.o vector.o segment.o

main: $(OBJECTS)
	$(CXX) -o main $(OBJECTS)

main.o: main.cpp
	$(CXX) $(CFLAGS) main.cpp

vector.o: amnesia/classes/vector.cpp amnesia/classes/vector.h
	$(CXX) $(CFLAGS) amnesia/classes/vector.cpp

segment.o: amnesia/classes/segment.cpp amnesia/classes/segment.h
	$(CXX) $(CFLAGS) amnesia/classes/segment.cpp

.PHONY: clean
clean:
	rm *.o