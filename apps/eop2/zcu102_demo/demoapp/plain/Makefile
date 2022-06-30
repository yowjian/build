CC      = gcc
PROG   ?= websrv
OSDK    = ../../orion-sdk
SRCS    = $(wildcard *.c)
INCS    = -I $(OSDK)/Communications -I $(OSDK)/Utils 
CFLAGS  = -Wno-unused-result -Wno-deprecated-declarations \
          -D_GNU_SOURCE -D MG_ENABLE_MBEDTLS=1 -DMG_ENABLE_LINES=1 
LDFLAGS = -L $(OSDK)/Communications/x86 -lOrionComm -L $(OSDK)/Utils/x86 -lOrionUtils \
          -lavformat -lavcodec -lavutil -lswscale -lswresample \
          -lmbedtls -lmbedcrypto -lmbedx509 \
          -lz -llzma -lbz2 -lpthread -lm 

all: $(PROG)
 
$(PROG): $(SRCS)
	$(CC) $(INCS) $(CFLAGS) -o $(PROG) $^ $(LDFLAGS) 

clean:
	rm -rf $(PROG) *.o 

