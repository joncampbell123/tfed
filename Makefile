TARGET=test1
LIBS=tf_project.o

CXXFLAGS=-std=gnu++11 -Wall -Wextra -pedantic
LDFLAGS=

CXX=/usr/gcc-4.8/bin/g++

all: $(TARGET)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<

test1: test1.o $(LIBS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $<

clean:
	rm -f *.o

distclean: clean
	rm -f $(TARGET) $(LIBS)

