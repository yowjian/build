CC = gcc
PROG = ex1
INCLUDE_DIRS = -I../../src/capo/partitioner/src/
CFLAGS = -Wall -g $(INCLUDE_DIRS)
LIBPDG=../../src/capo/pdg/build/libpdg.so

include targets.make

aa:
	$(info target aa)

test: aa aa
	$(info orange=$(CC_ORANGE) purple=$(CC_PURPLE))

all: dot

dot: $(PROG).mod.bc
	opt -load $(LIBPDG) -dot-pdg $(PROG).mod.bc
	opt -load $(LIBPDG) -dot-ddg $(PROG).mod.bc
	opt -load $(LIBPDG) -dot-cdg $(PROG).mod.bc

$(PROG).mod.bc: $(PROG).mod.ll
	llvm-as $(PROG).mod.ll

$(PROG).mod.ll: $(PROG).mod.c
	clang -S -g $(INCLUDE_DIRS) -emit-llvm $(PROG).mod.c

$(PROG).mod.c: $(PROG).c
	../../src/mules/cle-preprocessor/src/qd_cle_preprocessor.py -f $(PROG).c

clang_$(PROG): $(PROG).mod.c
	clang -g $(PROG).mod.c -o $(PROG).mod.out -L. -l$(PROG)

$(PROG): lib$(PROG).a $(PROG).o
	gcc $(CFLAGS) $(PROG).o -o $(PROG) -L. -l$(PROG)

#Native versoin of lib$(PROG)
lib$(PROG).a: $(PROG)_libs.c
	gcc $(CFLAGS) -c $(PROG)_libs.c
	ar rcs lib$(PROG).a $(PROG)_libs.o

#Arm 64 version of lib$(PROG).a
libarm64$(PROG).a:
	aarch64-none-linux-gnu-gcc $(AARCH64_CFLAGS) $(CFLAGS) -o $(PROG)arm64_libs.o -c $(PROG)_libs.c
	aarch64-none-linux-gnu-ar rcs libarm64$(PROG).a $(PROG)arm64_libs.o

$(PROG)_orange: lib$(ORANGE_TARGET)$(PROG).a
	$(CC_ORANGE) $(ORANGE_FLAGS) $(CFLAGS) $@.mod.c -o $@ -L. -l$(ORANGE_TARGET)$(PROG) -L../../src/capo/partitioner/src -l$(ORANGE_LIBXDCOMMS)

$(PROG)_purple: lib$(PURPLE_TARGET)$(PROG).a
	$(CC_PURPLE) $(PURPLE_FLAGS) $(CFLAGS) $@.mod.c -o $@ -L. -l$(PURPLE_TARGET)$(PROG) -L../../src/capo/partitioner/src -l$(PURPLE_LIBXDCOMMS)

$(PROG)_parts: $(PROG)_orange $(PROG)_purple

packages:
	tar cf $(PROG)_orange-enclave-gw-P.tar $(PROG)_orange
	tar cf $(PROG)_purple-enclave-gw-O.tar $(PROG)_purple *.jpg

clean:
	rm -f *~ *.o $(PROG) lib$(PROG).a libarm64$(PROG).a clang_$(PROG) *.dot $(PROG).mod.bc $(PROG).mod.ll $(PROG).mod.c $(PROG).c.clemap.json  $(PROG)_orange $(PROG)_purple *.tar

