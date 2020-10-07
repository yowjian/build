include ../common

CXX=g++

LDFLAGS += -lactivemq-cpp -lpthread
CXXFLAGS += -g $(LLVMFLAGS) $(INCLUDE) $(LDFLAGS)

MPU_OBJ = \
	MPX.o

EXEC = mpx

default: all

all: $(EXEC)

$(EXEC): $(MPU_OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS)

.PHONY : force-rebuild

.cpp.o:
	$(CXX) $(CXXFLAGS) $< -o $@ -c

clean:
	-rm -f *.o *~ $(EXEC)

