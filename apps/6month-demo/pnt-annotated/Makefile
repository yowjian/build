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

LDFLAGS += $(HAL_LIB_PATH) -lpthread
#CFLAGS += -Wall -g $(XMLFLAGS) -I/dist/include $(DIRS)
CPPFLAGS=-std=c++11 ${HAL_API_INCLUDE} ${HAL_APPGEN_INCLUDE}

OBJ = \
	pnt_example.o \
	ownship.o \
	target.o

default: all

all: pnt

pnt: $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

.PHONY : force-rebuild 

.c.o:  config.h
	$(CC) $(CFLAGS) $< -o $@ -c

clean:
	-rm -f *.o *~ pnt

