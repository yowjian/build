include ../common

CXX=g++

LDFLAGS += -lactivemq-cpp -lpthread `pkg-config --libs opencv`
CXXFLAGS += -g $(LLVMFLAGS) $(INCLUDE) $(LDFLAGS)

EOIR_OBJ = \
	Blob.o \
	GAPS_opencv_Manager.o \
	EOIR.o

EXEC = eoir

default: all

all: $(EXEC)

$(EXEC): $(EOIR_OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS)

.PHONY : force-rebuild

.cpp.o:
	$(CXX) $(CXXFLAGS) $< -o $@ -c

clean:
	-rm -f *.o *~ $(EXEC)

