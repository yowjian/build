include ../common

CXX=g++

LDFLAGS += -lactivemq-cpp -lpthread
CXXFLAGS += -g $(LLVMFLAGS) $(INCLUDE) $(LDFLAGS)

MPU_OBJ = \
	MPU.o

EXEC = mpu

default: all

all: $(EXEC)

$(EXEC): $(MPU_OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS)

.PHONY : force-rebuild

.cpp.o:
	$(CXX) $(CXXFLAGS) $< -o $@ -c

clean:
	-rm -f *.o *~ $(EXEC)

