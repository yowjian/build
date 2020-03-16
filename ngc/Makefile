VERSION = 1.0.0
DATE = $(shell date +'%Y.%m.%d %H:%M:%S')
HOST = $(shell cat /etc/machine-id)
USER = $(shell whoami)
DIRS =

LDFLAGS += -lrpc -lpthread 
#CFLAGS += -Wall -g $(XMLFLAGS) -I/dist/include $(DIRS)
CPPFLAGS=-std=c++11

OBJ = \
	pnt_example.o \
	ownship.o \
	target.o \
	rpc.o

NDN_OBJ = \
	ndn_proxy.o

default: all

all: pnt

pnt: $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

.PHONY : force-rebuild $(MGRS) $(TEST_UDT) # $(UDT)

.c.o:  config.h
	$(CC) $(CFLAGS) $< -o $@ -c

clean:
	-rm -f *.o *~ pnt 

