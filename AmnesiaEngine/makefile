CXX=g++
CFLAGS=-c -Wall --std=c++11 -pg -g
OBJECTS=$(patsubst %.o, $(BUILDFOLDER)/%.o, main.o vector.o segment.o polygon.o component.o entity.o lightsource.o system.o input.o window.o time.o engine.o)
SDLFLAGS=-lSDL2main -lSDL2
DEMOOBJECTS=demo.o
BUILDFOLDER=build

main: $(BUILDFOLDER) $(OBJECTS)
	$(CXX) -o main $(OBJECTS) $(SDLFLAGS) -pg -g

$(BUILDFOLDER)/main.o: main.cpp
	$(CXX) $(CFLAGS) $(SDLFLAGS) main.cpp -o $@

$(BUILDFOLDER)/segment.o: amnesia/primitive/segment.cpp amnesia/primitive/segment.h
	$(CXX) $(CFLAGS) amnesia/primitive/segment.cpp -o $@

$(BUILDFOLDER)/vector.o: amnesia/primitive/vector.cpp amnesia/primitive/vector.h
	$(CXX) $(CFLAGS) amnesia/primitive/vector.cpp  -o $@

$(BUILDFOLDER)/polygon.o: amnesia/primitive/polygon.cpp amnesia/primitive/polygon.h
	$(CXX) $(CFLAGS) amnesia/primitive/polygon.cpp -o $@

$(BUILDFOLDER)/component.o: amnesia/classes/component.cpp amnesia/classes/component.h
	$(CXX) $(CFLAGS) amnesia/classes/component.cpp -o $@

$(BUILDFOLDER)/entity.o: amnesia/classes/entity.cpp amnesia/classes/entity.h
	$(CXX) $(CFLAGS) amnesia/classes/entity.cpp -o $@

$(BUILDFOLDER)/lightsource.o: amnesia/classes/lightsource.cpp amnesia/classes/lightsource.h
	$(CXX) $(CFLAGS) $(SDLFLAGS) amnesia/classes/lightsource.cpp -o $@

$(BUILDFOLDER)/engine.o: amnesia/core/engine.cpp amnesia/core/engine.h
	$(CXX) $(CFLAGS) $(SDLFLAGS) amnesia/core/engine.cpp -o $@

$(BUILDFOLDER)/system.o: amnesia/core/system.cpp amnesia/core/system.h
	$(CXX) $(CFLAGS) amnesia/core/system.cpp -o $@

$(BUILDFOLDER)/input.o: amnesia/core/input.cpp amnesia/core/input.h
	$(CXX) $(CFLAGS) $(SDLFLAGS) amnesia/core/input.cpp -o $@

$(BUILDFOLDER)/window.o: amnesia/core/window.cpp amnesia/core/window.h
	$(CXX) $(CFLAGS) $(SDLFLAGS) amnesia/core/window.cpp -o $@

$(BUILDFOLDER)/time.o: amnesia/core/time.cpp amnesia/core/time.h
	$(CXX) $(CFLAGS) $(SDLFLAGS) amnesia/core/time.cpp -o $@

$(BUILDFOLDER):
	mkdir $(BUILDFOLDER)

.PHONY: clean
clean:
	rm -rf $(BUILDFOLDER)

.PHONY: clean
cleanall:
	rm -rf $(BUILDFOLDER)
	rm main

.PHONY: demo
demo: $(OBJECTS) $(DEMOOBJECTS)
	$(CXX) $(DEMOOBJECTS) $(OBJECTS) $(CFLAGS) $(SDLFLAGS) -o $(BUILDFOLDER)demo.exe

demo.o: demo/demo.cpp
	$(CXX) $(CFLAGS) $(SDLFLAGS) demo/demo.cpp
