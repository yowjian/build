MYLIB=-lsqlite3 -lpthread -lssl -lm

APPSRC=$(wildcard *.c)
APPOBJ=$(patsubst %.c, %.o, $(APPSRC)) 
APPEXE=secdesk

FACILSRC=$(wildcard facilio/src/*.c)
FACILOBJ=$(patsubst %.c, %.o, $(FACILSRC)) 
FACILINCL=-I facilio/include
FACILLIB=facilio/facilio.a

CFLAGS += -g -I/usr/include/python3.8
PYFLAGS = `python3-config --ldflags --libs` -lpython3.8

ifdef FACE
CFLAGS += -DINC_FACE_RECOGNITION=1
endif

$(APPEXE): $(APPOBJ) $(FACILLIB)
	clang -o $@ $^ $(MYLIB) $(PYFLAGS)

$(FACILLIB): $(FACILOBJ)
	ar -crs $@ $^

clean:
	rm -f $(APPEXE) $(APPOBJ)

realclean:
	rm -f $(APPEXE) $(APPOBJ) $(FACILOBJ) $(FACILLIB) 

.SECONDARY:

%.o: %.c
	clang -c $(CFLAGS) $(FACILINCL) $< -o $@

