IDIR=./annotated
EDIR=./annotated-working
CLANG_FLAGS += -I ../xdcc_echo -I ../../../amqlib
CONSTRAINTS=$(CLOSURE_PYTHON)/conflict_analyzer/constraints

assignments: topology 

topology: topology.json

topology.json: $(EDIR)
	conflict_analyzer \
	--pdg-lib $(CLOSURE_LIBS)/libpdg.so \
	--output topology.json \
	--artifact artifact.json \
	--source-path $(realpath .)/refactored \
	annotated/example1.c 

$(EDIR):
	mkdir -p $(EDIR)