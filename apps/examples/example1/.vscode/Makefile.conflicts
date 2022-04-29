IDIR=./annotated
EDIR=./annotated-working
CLANG_FLAGS += -I ../xdcc_echo -I ../../../amqlib
CONSTRAINTS=$(CLOSURE_PYTHON)/conflict_analyzer/constraints

assignments: topology 
	minizinc --solver Gecode $(CONSTRAINTS)/*.mzn $(EDIR)/*.mzn > $(EDIR)/label_assignments.txt

topology: topology.json

topology.json: $(EDIR)
	conflict_analyzer \
	--pdg-lib $(CLOSURE_LIBS)/libpdg.so \
	--constraint-files \
		$(CONSTRAINTS)/conflict_variable_declarations.mzn \
		$(CONSTRAINTS)/conflict_analyzer_constraints.mzn \
	--output topology.json \
	--temp $(realpath $(EDIR)) \
	--source-path $(realpath .)/refactored \
	annotated/example1.c 

$(EDIR):
	mkdir -p $(EDIR)