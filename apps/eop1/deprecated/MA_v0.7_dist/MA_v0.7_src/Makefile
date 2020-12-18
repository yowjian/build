
SUBDIRS := ISRM MPU MPX RDR EOIR
SUBDIRSCLEAN=$(addsuffix clean,$(SUBDIRS))

all: $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@

.PHONY: all $(SUBDIRS)

clean: $(SUBDIRSCLEAN)

$(SUBDIRSCLEAN):
	echo $@
	$(MAKE) -C $(subst clean,,$@)  clean	