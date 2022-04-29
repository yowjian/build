IDIR=./divvied
ODIR=$(realpath ./partitioned/$(IPCMODE))

ENCLAVES=
enclaves_set := $(foreach enclave,$(sort $(dir $(wildcard $(IDIR)//*/))), $(eval ENCLAVES+=$(notdir $(enclave:%/=%))))

EDIR=./verifier
RDIR=./refactored
REFACTORED=./refactored-working
PARTITIONED=

CONSTRAINTS=$(CLOSURE_PYTHON)/conflict_analyzer/constraints
partitioned_set := $(foreach enclave,$(ENCLAVES), $(eval PARTITIONED += $(ODIR)/$(enclave)))

SRC=
src_set := $(foreach enclave,$(ENCLAVES), $(eval SRC += $(shell find $(ODIR)/$(enclave) -name *.c;)))
REF_SRC=$(shell find $(REFACTORED) -name *.c)

HDR=
hdr_set := $(foreach enclave,$(ENCLAVES), $(eval SRC += $(shell find $(ODIR)/$(enclave) -name *.h;)))

CLANG_INCLUDES= -I $(CLOSURE_INCLUDES) -I $(ODIR)/autogen

CLANG_FLAGS += -D__LEGACY_XDCOMMS__=1 -I../../../amqlib -I../xdcc_echo

MODLL=$(patsubst %.c, %.ll, $(SRC))
MODCJC=$(patsubst %.c, %.c.clemap.json,$(SRC))
MODCJH=$(patsubst %.h,%.h.clemap.json,$(HDR))

all: 
	echo "Nothing to do for all"

assignments: analyze
	$(foreach enclave, $(ENCLAVES), \
		minizinc --solver Gecode $(CONSTRAINTS)/*.mzn $(EDIR)/$(enclave)/*.mzn > $(EDIR)/$(enclave)/label_assignments.txt; )

analyze: $(EDIR)
	$(foreach enclave, $(ENCLAVES), \
		conflict_analyzer \
			--clang-args="-I$(ODIR)/$(enclave),-I$(ODIR)/autogen,-I/opt/closure/include,-D__LEGACY_XDCOMMS__=1" \
			--pdg-lib=$(CLOSURE_LIBS)/libpdg.so \
			--output=$(EDIR)/$(enclave)/topology.json \
			--temp-dir=$(realpath $(EDIR)/$(enclave)) \
			--source-path=$(ODIR)/$(enclave) \
			$(ODIR)/$(enclave)/*.c $(ODIR)/$(enclave)/*.h; )

$(EDIR):
	mkdir -p $(EDIR)
	$(foreach enclave, $(ENCLAVES), mkdir -p $(EDIR)/$(enclave))	

verify: $(REFACTORED)/preproc.done prep
	$(VERIFIER) $(REFACTORED) $(PARTITIONED)

prep: $(MODCJC) $(MODCJH)
	$(foreach p,$(REF_SRC), $(CLANG) $(CLANG_FLAGS) $(CLANG_INCLUDES) $p -o $(basename $p).ll;)
	$(foreach enclave,$(ENCLAVES), $(foreach p,$(shell find $(ODIR)/$(enclave) -name *.c;), $(CLANG) $(CLANG_FLAGS) $(CLANG_INCLUDES) $p -o $(basename $p).ll;))
	echo "Done prep"

# preprocess each C and H file, rename them back
$(REFACTORED)/preproc.done: $(REFACTORED)/cleancopy.done
	$(eval PREPROCC += $(shell ls $(REFACTORED)/*.c;))
	$(eval PREPROCH += $(shell ls $(REFACTORED)/*.h;))
	$(foreach p,$(PREPROCC), $(PREPROCESSOR) -s ${CLOSURE_SCHEMAS}/cle-schema.json -f $p -o $(dir $(p));)
	$(foreach p,$(PREPROCH), $(PREPROCESSOR) -s ${CLOSURE_SCHEMAS}/cle-schema.json -f $p -o $(dir $(p));)
	$(foreach p,$(PREPROCC), mv $(basename $p).mod.c $p;)
	$(foreach p,$(PREPROCH), mv $(basename $p).mod.h $p;)
	$(JOINCLEMAPS) $(REFACTORED)/$(PROG).all.clemap.json $(PREPROCC) $(PREPROCH)
	mkdir -p jsons/refactored
	mv $(REFACTORED)/$(PROG).all.clemap.json jsons/refactored
	touch $(REFACTORED)/preproc.done

$(REFACTORED)/cleancopy.done:
	rm -rf $(REFACTORED) && \
        cp -r $(RDIR) $(REFACTORED) && \
	touch $(REFACTORED)/cleancopy.done
