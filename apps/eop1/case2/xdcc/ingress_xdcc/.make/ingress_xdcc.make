MYLIB=-lpthread ../autogen/libcodecs.a -lzmq -L../../../../../../amqlib -lamqlib -L../../../../xdcc_echo -lxdcc_echo -L$(CLOSURE_LIBS) -lxdcomms -L$(PINSTALL)/lib -lactivemq-cpp

APPSRC=$(wildcard *.c)
APPOBJ=$(patsubst %.c, %.o, $(APPSRC)) 
APPEXE=ingress_xdcc
APPLL=$(patsubst %.c, %.ll, $(APPSRC))

CFLAGS += -g -I/usr/include/python3.8
PYFLAGS = `python3-config --ldflags --libs`

CFLAGS += -D__LEGACY_XDCOMMS__=1 -D__ONEWAY_RPC__=1 -I../../../../../../amqlib -I../../../../xdcc_echo -I$(CLOSURE_INCLUDES) -I../autogen

$(APPEXE): $(APPOBJ)
	gcc $(CFLAGS) -o $@ $^ $(MYLIB) $(PYFLAGS)

clean:
	rm -f $(APPEXE) $(APPOBJ) $(APPLL)

realclean:
	rm -f $(APPEXE) $(APPOBJ) $(APPLL)

.SECONDARY:

%.o: %.c
	gcc -c $(CFLAGS) $< -o $@

