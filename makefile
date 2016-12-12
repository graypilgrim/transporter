CXX = g++
CXXFLAGS = -c -Wall -pedantic -o2
LINKFLAGS = -lGL -lGLU -lX11 -lXxf86vm -lXrandr -lXi -lglfw -lGLEW -lSOIL
BINARY = main.bin

SOURCES = \
	main.cpp \

OBJECTS=$(SOURCES:.cpp=.o)

$(BINARY): $(OBJECTS)
	$(CXX) $^ -o $@ $(LINKFLAGS)

%.o : %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	@rm -f $(BINARY)
	@rm -f *.o *.gch

.PHONY:
	clean
