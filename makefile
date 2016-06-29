CXX=g++
CFLAGS=-c -Wall --std=c++11
OBJECTS=main.o vector.o segment.o polygon.o component.o entity.o lightsource.o

main: $(OBJECTS)
	$(CXX) -o main $(OBJECTS)

main.o: main.cpp
	$(CXX) $(CFLAGS) main.cpp

vector.o: amnesia/primitive/vector.cpp amnesia/primitive/vector.h
	$(CXX) $(CFLAGS) amnesia/primitive/vector.cpp

segment.o: amnesia/primitive/segment.cpp amnesia/primitive/segment.h
	$(CXX) $(CFLAGS) amnesia/primitive/segment.cpp

polygon.o: amnesia/primitive/polygon.cpp amnesia/primitive/polygon.h
	$(CXX) $(CFLAGS) amnesia/primitive/polygon.cpp

component.o: amnesia/classes/component.cpp amnesia/classes/component.h
	$(CXX) $(CFLAGS) amnesia/classes/component.cpp

entity.o: amnesia/classes/entity.cpp amnesia/classes/entity.h
	$(CXX) $(CFLAGS) amnesia/classes/entity.cpp

lightsource.o: amnesia/classes/lightsource.cpp amnesia/classes/lightsource.h
	$(CXX) $(CFLAGS) amnesia/classes/lightsource.cpp

.PHONY: clean
clean:
	rm *.o