CC = gcc
PROG = ex1
INCLUDE_DIRS = -I../../src/capo/partitioner/src/
CFLAGS = -Wall -g $(INCLUDE_DIRS)
LIBPDG=../../src/capo/pdg/build/libpdg.so
NATIVE_TARGET=native
ARM64_TARGET=arm64

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
	clang -g $(PROG).mod.c -o $(PROG).mod.out -L./$(NATIVE_TARGET)/ -l$(PROG)

$(PROG): $(NATIVE_TARGET)/lib$(PROG).a $(PROG).o
	gcc $(CFLAGS) $(PROG).o -o $(PROG) -L./$(NATIVE_TARGET)/ -l$(PROG)

#Native versoin of lib$(PROG)
$(NATIVE_TARGET)/lib$(PROG).a: $(PROG)_libs.c
	mkdir -p $(NATIVE_TARGET)
	gcc $(CFLAGS) -c $(PROG)_libs.c -o $(NATIVE_TARGET)/$(PROG)_libs.o
	ar rcs $@ $(NATIVE_TARGET)/$(PROG)_libs.o

#ARM64 versoin of lib$(PROG)
$(ARM64_TARGET)/lib$(PROG).a: $(PROG)_libs.c
	mkdir -p $(ARM64_TARGET)
	aarch64-none-linux-gnu-gcc $(AARCH64_CFLAGS) $(CFLAGS) -c $(PROG)_libs.c -o $(ARM64_TARGET)/$(PROG)_libs.o
	aarch64-none-linux-gnu-ar rcs $@ $(ARM64_TARGET)/$(PROG)_libs.o

$(PROG)_orange: $(ORANGE_TARGET)/lib$(PROG).a
	$(CC_ORANGE) $(ORANGE_FLAGS) $(CFLAGS) $(INCLUDE_DIRS) $@.mod.c -o $@ -L./$(ORANGE_TARGET)/ -l$(PROG) -lxdcomms

$(PROG)_purple: $(PURPLE_TARGET)/lib$(PROG).a
	$(CC_PURPLE) $(PURPLE_FLAGS) $(CFLAGS) $(INCLUDE_DIRS) $@.mod.c -o $@ -L./$(PURPLE_TARGET)/ -l$(PROG) -lxdcomms

$(PROG)_parts: $(PROG)_orange $(PROG)_purple

packages:
	tar cf $(PROG)_orange-enclave-gw-P.tar $(PROG)_orange
	tar cf $(PROG)_purple-enclave-gw-O.tar $(PROG)_purple *.jpg

clean:
	rm -f *~ *.o $(PROG) clang_$(PROG) *.dot $(PROG).mod.bc $(PROG).mod.ll $(PROG).mod.c $(PROG).c.clemap.json  $(PROG)_orange $(PROG)_purple *.tar
	rm -rf $(NATIVE_TARGET) $(ARM64_TARGET)

