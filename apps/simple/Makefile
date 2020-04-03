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
CFLAGS += -Wall -g ${HAL_API_INCLUDE} ${HAL_APPGEN_INCLUDE}

ORANGE_OBJ = \
	orange.o \
	common.o \
	utils.o

GREEN_OBJ = \
	green.o \
	common.o \
	utils.o

default: all

all: orange green

orange: $(ORANGE_OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

green: $(GREEN_OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

.PHONY : force-rebuild 

.c.o:  config.h
	$(CC) $(CFLAGS) $< -o $@ -c

clean:
	-rm -f *.o *~ orange green

