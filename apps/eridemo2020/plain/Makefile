MYLIB=-lsqlite3 -lpthread -lssl -lm

APPSRC=$(wildcard *.c)
APPOBJ=$(patsubst %.c, %.o, $(APPSRC)) 
APPEXE=eridemo2020

FACILSRC=$(wildcard facilio/src/*.c)
FACILOBJ=$(patsubst %.c, %.o, $(FACILSRC)) 
FACILINCL=-I facilio/include
FACILLIB=facilio/facilio.a

MPARTSRC=$(wildcard multipart-parser/*.c)
MPARTOBJ=$(patsubst %.c, %.o, $(MPARTSRC)) 
MPARTINCL=-I multipart-parser

$(APPEXE): $(APPOBJ) $(MPARTOBJ) $(FACILLIB)
	clang -o $@ $^ $(MYLIB)

$(FACILLIB): $(FACILOBJ)
	ar -crs $@ $^

clean:
	rm -f $(APPEXE) $(APPOBJ)

realclean:
	rm -f $(APPEXE) $(APPOBJ) $(MPARTOBJ) $(FACILOBJ) $(FACILLIB) 

.SECONDARY:

%.o: %.c
	clang -c $(FACILINCL) $(MPARTINCL) $< -o $@

