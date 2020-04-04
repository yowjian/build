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

EXEC=simple

OBJ = \
	main.o \
	utils.o

default: all

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

.PHONY : force-rebuild 

.c.o:  config.h
	$(CC) $(CFLAGS) $< -o $@ -c

clean:
	-rm -f *.o *~ $(EXEC)

