
WORKING_DIR=ect-working
DIRS=$(ENCLAVES) refactored

CC=clang-9
LLFLAGS=-S -emit-llvm
IPC_MODE=multithreaded
PARTITIONED_IPCMODE=partitioned/$(IPC_MODE)
INCLUDES=-I$(PARTITIONED_IPCMODE)/autogen -I$(CLOSURE_INCLUDES)
REFACTORED=refactored
ect: lls
	$(ECT) \
		$(foreach e,$(DIRS), $(WORKING_DIR)/llvm/$(e)) \
		$(foreach e,$(DIRS), $(WORKING_DIR)/clemaps/$(e).json)

lls: $(WORKING_DIR)
	$(foreach e,$(ENCLAVES), \
		$(PREPROCESSOR) -f $(PARTITIONED_IPCMODE)/$(e)/$(PROG).c -o $(WORKING_DIR)/c/$(e)/ -s $(CLOSURE_SCHEMAS)/cle-schema.json; \
		$(CC) $(LLFLAGS) $(WORKING_DIR)/c/$(e)/$(PROG).mod.c $(INCLUDES) -I$(PARTITIONED_IPCMODE)/$(e) -o $(WORKING_DIR)/llvm/$(e)/$(PROG).ll; \
		mv $(WORKING_DIR)/c/$(e)/$(PROG).c.clemap.json $(WORKING_DIR)/clemaps/$(e).json; \
	)
	$(PREPROCESSOR) -f $(REFACTORED)/$(PROG).c -o $(WORKING_DIR)/c/refactored/ -s $(CLOSURE_SCHEMAS)/cle-schema.json
	$(CC) $(LLFLAGS) $(WORKING_DIR)/c/refactored/$(PROG).mod.c -o $(WORKING_DIR)/llvm/refactored/$(PROG).ll; 
	mv $(WORKING_DIR)/c/refactored/$(PROG).c.clemap.json $(WORKING_DIR)/clemaps/refactored.json; 

$(WORKING_DIR): 
	$(foreach e,$(DIRS),\
		mkdir -p $(WORKING_DIR)/llvm/$(e); \
		mkdir -p $(WORKING_DIR)/c/$(e); \
	)
	mkdir -p $(WORKING_DIR)/clemaps 

