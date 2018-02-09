programs    := test_alg
libs        := libalg.a
sources     := 
extra_clean := *~


objects       = $(subst .c,.o,$(sources))
dependencies  = $(subst .c,.d,$(sources))


project_dir   := $(shell pwd)
include_dirs  := $(project_dir)/algorithms/
sources_dirs  := $(project_dir)/algorithms/ 
testcase_dirs := $(project_dir)/test_case/

exportheader_dir := $(project_dir)/out/export_header/

bin_dir       := out

CFLAGS     += $(addprefix -I, $(include_dirs)) -lm -lcunit -g
vpath %.h $(include_dirs)

MV  :=  mv -f
RM  :=  rm -f
SED := sed

include algorithms/alg.mk
include test_case/test_case.mk

.PHONY: all
all: $(programs)

$(programs): $(objects)
	$(CC) $(objects) $(CFLAGS) -o $(bin_dir)/$@

.PHONY: libs
libs: $(libs)

$(libs): $(objects)
	$(AR) -r $(bin_dir)/$@ $(objects) 
	cp $(include_dirs)/*.h $(exportheader_dir)

.PHONY: clean
clean:
	$(RM) $(objects) $(bin_dir)/$(programs) $(bin_dir)/$(libs) $(exportheader_dir)/*.h $(dependencies) $(extra_clean)

ifneq "$(MAKECMDGOALS)" "clean"
   include $(dependencies)
endif

%.d: %.c
	$(CC) $(CFLAGS) $(TARGET_ACH) -MM $< | \
	$(SED) 's, \($notdi $*)\.o\) *:,$(dir $@)\1 $@: ,' > $@.tmp
	$(MV) $@.tmp $@

 
