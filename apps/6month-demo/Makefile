VERSION = 1.0.0
DATE = $(shell date +'%Y.%m.%d %H:%M:%S')
HOST = $(shell cat /etc/machine-id)
USER = $(shell whoami)
DIRS =

HAL=../../src/hal
HAL_API_INCLUDE=-I${HAL}/api
HAL_APPGEN_INCLUDE=-I${HAL}/appgen
HAL_LIBS=-lpnt -lxdcomms
HAL_LIB_PATH=-L${HAL}/api -L${HAL}/appgen

LIBS 	    = ${HAL}/api/libxdcomms.a
COMPATLIBS  = ${HAL}/x86_64_prebuild/libzmq.a -static -Wl,--allow-multiple-definition -Wl,-Bstatic -lsodium -lunwind -llzma $(LDFLAGS) -ldl -lc -lstdc++ -lpthread

LDFLAGS += $(HAL_LIB_PATH) -lpthread $(HAL_LIBS) -lzmq 
#CFLAGS += -Wall -g $(XMLFLAGS) -I/dist/include $(DIRS)
CPPFLAGS=-std=c++11 ${HAL_API_INCLUDE} ${HAL_APPGEN_INCLUDE}

ORANGE_OBJ = \
	orange.o \
	orange_ownship.o \
	orange_target.o \
	orange_rpc.o

GREEN_OBJ = \
	green.o \
	green_ownship.o \
	green_target.o \
	green_rpc.o

default: all

all: orange green

static: static-orange static-green

orange: $(ORANGE_OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

green: $(GREEN_OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

static-orange: $(ORANGE_OBJ)
	$(CXX) -o orange $^ $(LIBS) $(COMPATLIBS)

static-green: $(GREEN_OBJ)
	$(CXX) -o green $^ $(LIBS) $(COMPATLIBS)

.PHONY : force-rebuild 

.c.o:  config.h
	$(CC) $(CFLAGS) $< -o $@ -c

clean:
	-rm -f *.o *~ orange green

