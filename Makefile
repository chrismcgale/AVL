CXX=g++
CXXFLAGS=-std=c++14 -Wall -O -g -MMD -Werror=vla# use -MMD to generate dependencies
SOURCES=$(wildcard *.cpp)   # list of all .cpp files in the current directory
OBJECTS=${SOURCES:.cpp=.o}  # .o files depend upon .cpp files with same names
DEPENDS=${OBJECTS:.o=.d}   # .d file is list of dependencies for corresponding .cc file
EXEC=range

# First target in the makefile is the default target.
# Note that the LIBFLAGS must come last in the command
$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXEC) -lX11

%.o: %.cc
	$(CXX) -c -o $@ $< $(CXXFLAGS) 

-include ${DEPENDS}

.PHONY: clean
clean:
	rm  -f $(OBJECTS) $(DEPENDS) $(EXEC)
