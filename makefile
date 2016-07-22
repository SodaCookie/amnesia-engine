CXX						:= g++
CXXFLAGS			:= -Wall -g -O3 -pedantic --std=c++11 -stdlib=libc++
BUILDFOLDER 	:= _build
CPP_FILES 		:= $(shell find ./amnesia -name '*.cpp')
SRCDIRS 			:= $(patsubst ./%,$(BUILDFOLDER)/%,$(shell find ./amnesia -name '*.cpp' -exec dirname {} \; | uniq))
OBJECTS   		:= $(patsubst %,$(BUILDFOLDER)%,$(CPP_FILES:.%.cpp=%.o))
STATICLIBNAME := libamnesia.a

main: $(OBJECTS)
	ar rcs $(BUILDFOLDER)/$(STATICLIBNAME) $(OBJECTS)

$(BUILDFOLDER)/%.o: %.cpp %.h | $(BUILDFOLDER)
	$(CXX) $(CXXFLAGS) -o $@ -c $<

$(BUILDFOLDER):
	mkdir $(BUILDFOLDER)
	$(foreach var,$(SRCDIRS:./%=./$(BUILDFOLDER)/%),mkdir -p $(var);)

.PHONY: clean
clean:
	rm -rf $(BUILDFOLDER)
