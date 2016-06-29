CXX=g++
CFLAGS=-c -Wall --std=c++11
OBJECTS=main.o vector.o segment.o polygon.o component.o entity.o lightsource.o
DEMOOBJECTS=demo.o
DEMOFLAGS=-c -Wall --std=c++11 -I C:\Users\Eric\Documents\Programming\Libaries\SDL2-2.0.4\include
BUILDFOLDER=build/

main: $(OBJECTS)
	$(CXX) -o $(BUILDFOLDER)main $(OBJECTS)

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

.PHONY: demo
demo: $(OBJECTS) $(DEMOOBJECTS)
	$(CXX) demo.o vector.o segment.o polygon.o component.o entity.o lightsource.o -L C:\Users\Eric\Documents\Programming\Libaries\SDL2-2.0.4\lib\x86 -lSDL2main -lSDL2 -o $(BUILDFOLDER)demo

demo.o: demo/demo.cpp
	$(CXX) $(DEMOFLAGS) demo/demo.cpp