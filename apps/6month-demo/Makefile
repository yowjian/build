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

LIBS 	    = ${HAL}/api/libxdcomms.a
COMPATLIBS  = ${HAL}/x86_64_prebuild/libzmq.a -static -Wl,--allow-multiple-definition -Wl,-Bstatic -lsodium -lunwind -llzma $(LDFLAGS) -ldl -lc -lstdc++ -lpthread

LDFLAGS += $(HAL_LIB_PATH) -lpthread $(HAL_LIBS) -lzmq 
#CFLAGS += -Wall -g $(XMLFLAGS) -I/dist/include $(DIRS)
CPPFLAGS=-std=c++11 ${HAL_API_INCLUDE} ${HAL_APPGEN_INCLUDE}

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

all: orange green

static: static-orange static-green

orange: $(ORANGE_OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

green: $(GREEN_OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

static-orange: $(ORANGE_OBJ)
	$(CXX) -o orange $^ $(LIBS) $(COMPATLIBS)

static-green: $(GREEN_OBJ)
	$(CXX) -o green $^ $(LIBS) $(COMPATLIBS)

.PHONY : force-rebuild 

.c.o:  config.h
	$(CC) $(CFLAGS) $< -o $@ -c

clean:
	-rm -f *.o *~ orange green


#### LLVM Partitioner 

# make PROG=green will override this
PROG=orange
LIBPDG=../../src/capo/pdg/build/libpdg.so
CLE_PRE=../../src/mules/cle-preprocessor/src
PARTITIONER=../../src/capo/partitioner/src/partitioner.py

orange_LLVMOBJ = orange_ownship.ll\
          orange_rpc.ll\
          orange_target.ll\
          orange.mod.ll
          
green_LLVMOBJ = green_ownship.ll\
          green_rpc.ll\
          green_target.ll\
          green.mod.ll


.SECONDARY:

enclaves: pdgragh.main.dot
	python3 $(PARTITIONER) $(PROG).cpp


dot: $(PROG)_all.mod.bc
	opt -load $(LIBPDG) -dot-pdg $^

remdot: dot
	gvpr -c "N[$.degree==0]{delete(root,$$)}" pdgragh.main.dot -o tmp.dot
	mv tmp.dot pdgragh.main.dot
	cp pdgragh.main.dot $(PROG)_all.pdgragh.main.dot
	
$(PROG)_all.mod.bc: $($(PROG)_LLVMOBJ)
	llvm-link -o $@ $^

%.mod.bc: %.mod.ll
	llvm-as $^

%.ll: %.c
%.ll: %.cpp
	clang $(CPPFLAGS) -S -g $(INCLUDE_DIRS) -emit-llvm $^

%.mod.c: %.c
%.mod.cpp: %.cpp
	$(CLE_PRE)/qd_cle_preprocessor.py -f $^

tags:
	llvm-dis orange_all.mod.bc
	llvm-dis green_all.mod.bc
	python3 ../../src/capo/partitioner/src/tag_processor.py green_all.pdgragh.main.dot orange_all.pdgragh.main.dot
	echo "INVOKE cutzoom HERE"

#packages:
#	tar cf $(PROG)_$(ENC1)-enclave-gw-P.tar $(PROG)_$(ENC1)
#	tar cf $(PROG)_$(ENC2)-enclave-gw-O.tar $(PROG)_$(ENC2)

capoclean:
	rm -f *~ *.ll *.bc *.dot *.clemap.json *.mod.c *.mod.cpp 

