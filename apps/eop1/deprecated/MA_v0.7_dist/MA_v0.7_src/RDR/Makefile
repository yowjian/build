include ../common

CXX=g++

LDFLAGS += -lactivemq-cpp -lpthread
CXXFLAGS += -g $(LLVMFLAGS) $(INCLUDE) $(LDFLAGS)

RDR_OBJ = \
	RDR.o

EXEC = rdr

default: all

all: $(EXEC)

$(EXEC): $(RDR_OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS)

.PHONY : force-rebuild

.cpp.o:
	$(CXX) $(CXXFLAGS) $< -o $@ -c

clean:
	-rm -f *.o *~ $(EXEC)

