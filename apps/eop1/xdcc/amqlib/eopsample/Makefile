INCLUDE = -I ./include
INCLUDE += -I/usr/local/include/activemq-cpp-3.9.5
INCLUDE += -I/usr/local/apr/include/apr-1
CXXFLAGS += -g $(INCLUDE) $(LDFLAGS) -Wno-deprecated-declarations
LDFLAGS += -lactivemq-cpp -lpthread
CXX=g++

FOO_OBJ = FOO.o
EXEC = foo

default: all

all: $(EXEC)

$(EXEC): $(FOO_OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS)

.PHONY : force-rebuild

.cpp.o:
	$(CXX) $(CXXFLAGS) $< -o $@ -c

clean:
	-rm -f *.o *~ $(EXEC)

