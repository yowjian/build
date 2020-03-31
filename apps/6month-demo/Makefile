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

LDFLAGS += $(HAL_LIB_PATH) -lpthread $(HAL_LIBS) -lzmq 
#CFLAGS += -Wall -g $(XMLFLAGS) -I/dist/include $(DIRS)
CPPFLAGS=-std=c++11 ${HAL_API_INCLUDE} ${HAL_APPGEN_INCLUDE}

OBJ = \
	pnt_example.o \
	ownship.o \
	target.o \
	rpc.o

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

pnt: $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

orange: $(ORANGE_OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

green: $(GREEN_OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

.PHONY : force-rebuild 

.c.o:  config.h
	$(CC) $(CFLAGS) $< -o $@ -c

clean:
	-rm -f *.o *~ pnt orange green

