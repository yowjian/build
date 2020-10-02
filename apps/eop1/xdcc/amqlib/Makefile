INCLUDE = -I ./include
INCLUDE += -I/usr/local/include/activemq-cpp-3.9.5
INCLUDE += -I/usr/local/apr/include/apr-1
CXXFLAGS += -g $(INCLUDE) $(LDFLAGS) -Wno-deprecated-declarations
LDFLAGS += -lactivemq-cpp -lpthread
CXX=g++

LIB_OBJ = amqlib.o
LIB_LIB = amqlib.a
EXE_OBJ = test.o
EXEC    = test

default: all

all: $(EXEC)

lib: $(LIB_LIB)

$(EXEC): $(EXE_OBJ) $(LIB_LIB) 
	$(CXX) -o $@ $^ $(CXXFLAGS)

$(LIB_LIB): $(LIB_OBJ)
	ar -cvq $@ $^

.PHONY : force-rebuild

.c.o:
	gcc $< -o $@ -c

.cpp.o:
	$(CXX) $(CXXFLAGS) $< -o $@ -c

clean:
	-rm -f *.o *~ $(EXEC)

libclean: clean
	-rm -f $(LIB_LIB) 
