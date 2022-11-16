CXX=g++
CXXFLAGS=-g -Wall -std=c++11 
# Uncomment for parser DEBUG
#DEFS=-DDEBUG


all: bst-test internal-range-test

bst-test: bst-test.cpp bst.h avlbst.h
	$(CXX) $(CXXFLAGS) $(DEFS) $< -o $@

# Brute force recompile all files each time
internal-range-test: internal-range-test.cpp internal-range.cpp internal-range.h
	$(CXX) $(CXXFLAGS) $(DEFS) internal-range-test.cpp internal-range.cpp -o $@

clean:
	rm -f *~ *.o bst-test internal-range-test
