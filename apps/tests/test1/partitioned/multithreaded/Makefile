BUILD=../../../../..
INCLUDES=-I${BUILD}/src/hal/api -I./autogen
LDLIBS=-L${BUILD}/src/hal/api
LIBS=./autogen/libcodecs.a


all: test1_purple test1_orange

clean:
	make -C ./autogen clean
	rm -f *.o *~ test1_purple test1_orange

test1_purple: test1_purple.c test1_purple_rpc.c
	make -C ./autogen autogen
	make -C ./autogen libraries
	gcc -c test1_purple.c test1_purple_rpc.c ${INCLUDES}
	gcc -o test1_purple test1_purple.o test1_purple_rpc.o ${LDLIBS} ${LIBS} -lxdcomms

test1_orange: test1_orange.c test1_orange_rpc.c
	make -C ./autogen autogen
	make -C ./autogen libraries
	gcc -c test1_orange.c test1_orange_rpc.c ${INCLUDES}
	gcc -o test1_orange test1_orange.o test1_orange_rpc.o ${LDLIBS} ${LIBS} -lxdcomms -lpthread


