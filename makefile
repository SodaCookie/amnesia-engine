CXX=g++
CFLAGS=-c -Wall --std=c++11
OBJECTS=main.o vector.o segment.o polygon.o component.o entity.o lightsource.o system.o input.o window.o time.o
SDLFLAGS=-I C:\Users\Eric\Documents\Programming\Libaries\SDL2-2.0.4\include -L C:\Users\Eric\Documents\Programming\Libaries\SDL2-2.0.4\lib\x86 -lSDL2main -lSDL2
DEMOOBJECTS=demo.o
BUILDFOLDER=build/

main: $(OBJECTS)
	$(CXX) -o $(BUILDFOLDER)main $(OBJECTS) $(SDLFLAGS)

main.o: main.cpp
	$(CXX) $(CFLAGS) $(SDLFLAGS) main.cpp

segment.o: amnesia/primitive/segment.cpp amnesia/primitive/segment.h
	$(CXX) $(CFLAGS) amnesia/primitive/segment.cpp

vector.o: amnesia/primitive/vector.cpp amnesia/primitive/vector.h
	$(CXX) $(CFLAGS) amnesia/primitive/vector.cpp

polygon.o: amnesia/primitive/polygon.cpp amnesia/primitive/polygon.h
	$(CXX) $(CFLAGS) amnesia/primitive/polygon.cpp

component.o: amnesia/classes/component.cpp amnesia/classes/component.h
	$(CXX) $(CFLAGS) amnesia/classes/component.cpp

entity.o: amnesia/classes/entity.cpp amnesia/classes/entity.h
	$(CXX) $(CFLAGS) amnesia/classes/entity.cpp

lightsource.o: amnesia/classes/lightsource.cpp amnesia/classes/lightsource.h
	$(CXX) $(CFLAGS) $(SDLFLAGS) amnesia/classes/lightsource.cpp

system.o: amnesia/core/system.cpp amnesia/core/system.h
	$(CXX) $(CFLAGS) amnesia/core/system.cpp

input.o: amnesia/core/input.cpp amnesia/core/input.h
	$(CXX) $(CFLAGS) $(SDLFLAGS) amnesia/core/input.cpp

window.o: amnesia/core/window.cpp amnesia/core/window.h
	$(CXX) $(CFLAGS) $(SDLFLAGS) amnesia/core/window.cpp

time.o: amnesia/core/time.cpp amnesia/core/time.h
	$(CXX) $(CFLAGS) $(SDLFLAGS) amnesia/core/time.cpp

.PHONY: clean
clean:
	rm *.o

.PHONY: demo
demo: $(OBJECTS) $(DEMOOBJECTS)
	$(CXX) $(DEMOOBJECTS) $(OBJECTS) $(CFLAGS) $(SDLFLAGS) -o $(BUILDFOLDER)demo

demo.o: demo/demo.cpp
	$(CXX) $(CFLAGS) $(SDLFLAGS) demo/demo.cpp