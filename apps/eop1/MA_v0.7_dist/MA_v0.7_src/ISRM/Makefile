include ../common

CXX=g++

LDFLAGS += -lactivemq-cpp -lpthread
CXXFLAGS += -g $(LLVMFLAGS) $(INCLUDE) $(LDFLAGS)

ISRM_OBJ = \
	ISRM.o

EXEC = isrm

default: all

all: $(EXEC)

$(EXEC): $(ISRM_OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS)

.PHONY : force-rebuild

.cpp.o:
	$(CXX) $(CXXFLAGS) $< -o $@ -c

clean:
	-rm -f *.o *~ $(EXEC)

