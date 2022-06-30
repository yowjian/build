CC      = gcc
PROG   ?= websrv
OSDK    = ../../orion-sdk
SRCS    = $(wildcard *.c)
INCS    = -I $(OSDK)/Communications \
          -I $(OSDK)/Utils \
          -I /usr/include/x86_64-linux-gnu

CFLAGS  = -Wno-unused-result -Wno-deprecated-declarations \
          -D_GNU_SOURCE -D MG_ENABLE_MBEDTLS=1 -DMG_ENABLE_LINES=1 
LDFLAGS = -lz -llzma -lbz2 -lpthread -lm -lmbedtls -lmbedcrypto -lmbedx509 \
          -L /usr/lib/x86_64-linux-gnu -lavformat -lavcodec -lavutil -lswscale -lswresample \
          -L $(OSDK)/Communications/x86 -lOrionComm -L $(OSDK)/Utils/x86 -lOrionUtils

all: $(PROG)
 
$(PROG): $(SRCS)
	$(CC) $(INCS) $(CFLAGS) -o $(PROG) $^ $(LDFLAGS) 

clean:
	rm -rf $(PROG) *.o 

