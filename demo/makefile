CXX						:= g++
INCLUDES 			:= -I./../amnesia
CXXFLAGS			:= -Wall -g -pedantic --std=c++11 -stdlib=libc++ $(INCLUDES)
LFLAGS 				:= $(CXXFLAGS) -L./../_build/ -lamnesia -lSDL2
BUILDFOLDER 	:= _build
CPP_FILES 		:= $(shell find . -name '*.cpp')
SRCDIRS 			:= $(patsubst ./%,$(BUILDFOLDER)/%,$(shell find . -name '*.cpp' -exec dirname {} \; | uniq))
OBJECTS   		:= $(patsubst %,$(BUILDFOLDER)%,$(CPP_FILES:.%.cpp=%.o))
STATICLIBNAME := libamnesia.a

main: $(OBJECTS)
	$(CXX) $(LFLAGS) $(OBJECTS) -o demo

$(BUILDFOLDER)/%.o: %.cpp | $(BUILDFOLDER)
	$(CXX) $(CXXFLAGS) -o $@ -c $<

$(BUILDFOLDER):
	mkdir $(BUILDFOLDER)
	$(foreach var,$(SRCDIRS:./%=./$(BUILDFOLDER)/%),mkdir -p $(var);)

.PHONY: clean
clean:
	rm -rf $(BUILDFOLDER)
	rm demo
