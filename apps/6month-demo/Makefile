VERSION = 1.0.0
DATE = $(shell date +'%Y.%m.%d %H:%M:%S')
HOST = $(shell cat /etc/machine-id)
USER = $(shell whoami)
DIRS =

HAL=../../src/hal
HAL_API_INCLUDE=-I${HAL}/api
HAL_APPGEN_INCLUDE=-I${HAL}/appgen/6month-demo
HAL_LIBS=-lxdcomms -lfloat -lgma
HAL_LIB_PATH=-L${HAL}/api -L${HAL}/appgen/6month-demo

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

#include the targets.make (native/arm64) configuration
include targets.make

NATIVE_TARGET=native
ARM64_TARGET=arm64

default: all

all: orange green

static: static-orange static-green

#naive object files, just symlink *.o into native/*.o
$(NATIVE_TARGET)/%.o:%.o
	mkdir -p $(NATIVE_TARGET)
	ln -sf ../$^ $@

#arm64 object files, build arm64 version of the c file
$(ARM64_TARGET)/%.o:%.cpp
	mkdir -p $(ARM64_TARGET)
	$(CXX_ARM64) -c -o $@ $^ $(ARM64_CPPFLAGS)

orange: $(addprefix $(ORANGE_TARGET)/,$(ORANGE_OBJ))
	$(CXX_ORANGE) -o $@ $^ $(ORANGE_LDFLAGS)

green: $(addprefix $(GREEN_TARGET)/,$(GREEN_OBJ))
	$(CXX_GREEN) -o $@ $^ $(GREEN_LDFLAGS)

static-orange: $(ORANGE_TARGET)/$(ORANGE_OBJ)
	$(CXX_ORANGE) -o orange $^ $(LIBS) $(COMPATLIBS)

static-green: $(GREEN_TARGET)/$(GREEN_OBJ)
	$(CXX_GREEN) -o green $^ $(LIBS) $(COMPATLIBS)

.PHONY : force-rebuild 

.c.o:  config.h
	$(CC) $(CFLAGS) $< -o $@ -c

clean:
	-rm -f *.o *~ orange green
	-rm -rf native arm64


#### LLVM Partitioner 

# make PROG=green will override this
PROG=orange
LIBPDG=../../src/capo/pdg/build/libpdg.so
CLE_PRE=../../src/mules/cle-preprocessor/src
PARTITIONER_DIR=../../src/capo/partitioner/src

orange_LLVMOBJ = orange_ownship.mod.ll\
          orange_rpc.mod.ll\
          orange_target.mod.ll\
          orange.mod.ll

green_LLVMOBJ = green_ownship.mod.ll\
          green_rpc.mod.ll\
          green_target.mod.ll\
          green.mod.ll


.SECONDARY:

$(PROG)_enclaves: $(PROG)_all.pdgragh.main.dot $(PROG)_all.mod.ll
	python3 $(PARTITIONER_DIR)/partitioner.py $(PROG)_all.cpp
	mv enclaves.dot $(PROG)_enclaves.dot

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

#%.mod.ll: %.mod.bc
#llvm-dis $^

%.ll: %.c
%.ll: %.cpp
	clang $(CPPFLAGS) -S -g -O0 $(INCLUDE_DIRS) -emit-llvm $^

%.mod.c: %.c
%.mod.cpp: %.cpp
	$(CLE_PRE)/qd_cle_preprocessor.py -f $^

capotags:
	llvm-dis orange_all.mod.bc
	llvm-dis green_all.mod.bc
	python3 $(PARTITIONER_DIR)/tag_processor.py green_all.pdgragh.main.dot orange_all.pdgragh.main.dot
	$(PARTITIONER_DIR)/cutzoom/cutzoom.py -f join_graph.dot -k1 -o abridged_1_colored.dot
	$(PARTITIONER_DIR)/cutzoom/cutzoom.py -f join_graph.dot -k2 -o abridged_2_colored.dot

packages:
	mkdir -p appgen
	cp ${GREEN_HAL}/api/libxdcomms.so ./appgen
	cp ${GREEN_HAL}/appgen/6month-demo/*.so ./appgen
	cp ${GREEN_HAL}/appgen/6month-demo/*.a ./appgen
	tar cf pnt_example-green-enclave-gw-O.tar green appgen
	cp ${ORANGE_HAL}/api/libxdcomms.so ./appgen
	cp ${ORANGE_HAL}/appgen/6month-demo/*.so ./appgen
	cp ${ORANGE_HAL}/appgen/6month-demo/*.a ./appgen
	tar cf pnt_example-orange-enclave-gw-G.tar orange appgen

capoclean:
	rm -f *~ *.ll *.bc *.dot *.clemap.json *.mod.c *.mod.cpp *.tar *.so
	rm -rf appgen
