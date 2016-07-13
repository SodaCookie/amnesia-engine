CXX=g++
CFLAGS=-c -Wall -pedantic --std=c++11 -pg -g -stdlib=libc++
LFLAGS=-Wall --std=c++11 -pg -g -stdlib=libc++
EXE=main
MAIN_OBJ=$(patsubst %.o, $(BUILDFOLDER)/%.o, main.o)
OBJECTS=$(patsubst %.o, $(BUILDFOLDER)/%.o, vector.o segment.o polygon.o \
	component.o entity.o lightsource.o system.o input.o window.o time.o \
	engine.o rect.o)
SDLFLAGS=-lSDL2main -lSDL2
STATICLIBNAME=libamnesia.a
DEMOOBJECTS=demo.o
BUILDFOLDER=_build

main: $(BUILDFOLDER) $(OBJECTS) $(MAIN_OBJ)
	$(CXX) -o $(BUILDFOLDER)/$(EXE) $(OBJECTS) $(MAIN_OBJ) $(SDLFLAGS) $(LFLAGS)

$(BUILDFOLDER)/main.o: main.cpp
	$(CXX) $(CFLAGS) main.cpp -o $@

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
	$(CXX) $(CFLAGS) amnesia/classes/lightsource.cpp -o $@

$(BUILDFOLDER)/engine.o: amnesia/core/engine.cpp amnesia/core/engine.h
	$(CXX) $(CFLAGS) amnesia/core/engine.cpp -o $@

$(BUILDFOLDER)/system.o: amnesia/core/system.cpp amnesia/core/system.h
	$(CXX) $(CFLAGS) amnesia/core/system.cpp -o $@

$(BUILDFOLDER)/input.o: amnesia/core/input.cpp amnesia/core/input.h
	$(CXX) $(CFLAGS) amnesia/core/input.cpp -o $@

$(BUILDFOLDER)/window.o: amnesia/core/window.cpp amnesia/core/window.h
	$(CXX) $(CFLAGS) amnesia/core/window.cpp -o $@

$(BUILDFOLDER)/time.o: amnesia/core/time.cpp amnesia/core/time.h
	$(CXX) $(CFLAGS) amnesia/core/time.cpp -o $@

$(BUILDFOLDER)/rect.o: amnesia/primitive/rect.cpp amnesia/primitive/rect.h
	$(CXX) $(CFLAGS) amnesia/primitive/rect.cpp -o $@

$(BUILDFOLDER):
	mkdir $(BUILDFOLDER)

.PHONY: static
static: $(OBJECTS)
	ar rcs ./$(BUILDFOLDER)/$(STATICLIBNAME) $^

.PHONY: clean
clean:
	rm -rf $(BUILDFOLDER)

.PHONY: demo
demo: $(OBJECTS) $(DEMOOBJECTS)
	$(CXX) $(DEMOOBJECTS) $(OBJECTS) $(CFLAGS) $(SDLFLAGS) -o $(BUILDFOLDER)demo.exe

demo.o: demo/demo.cpp
	$(CXX) $(CFLAGS) $(SDLFLAGS) demo/demo.cpp
