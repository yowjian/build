VERSION = 1.0.0
DATE = $(shell date +'%Y.%m.%d %H:%M:%S')
HOST = $(shell cat /etc/machine-id)
USER = $(shell whoami)
DIRS =

LDFLAGS += -L. -lrpc -lpthread -lpnt -lxdcomms -lzmq
#CFLAGS += -Wall -g $(XMLFLAGS) -I/dist/include $(DIRS)
CPPFLAGS=-std=c++11

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

all: pnt orange green

pnt: $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

orange: $(ORANGE_OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

green: $(GREEN_OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

.PHONY : force-rebuild $(MGRS) $(TEST_UDT) # $(UDT)

.c.o:  config.h
	$(CC) $(CFLAGS) $< -o $@ -c

clean:
	-rm -f *.o *~ pnt orange green

