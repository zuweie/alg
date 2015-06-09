programs    := test_alg
sources     := 
extra_clean := *~


objects       = $(subst .c,.o,$(sources))
dependencies  = $(subst .c,.d,$(sources))


project_dir   := /home/zuweie/WorkShop/code/Algorithms
include_dirs  := $(project_dir)/algorithms
sources_dirs  := $(project_dir)/algorithms
testcase_dirs := $(project_dir)test_case

bin          := out

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
	$(CC) $(objects) $(CFLAGS) -o $(bin)/$@

.PHONY: clean
clean:
	$(RM) $(objects) $(bin)/$(programs) $(dependencies) $(extra_clean)

ifneq "$(MAKECMDGOALS)" "clean"
   include $(dependencies)
endif

%.d: %.c
	$(CC) $(CFLAGS) $(TARGET_ACH) -MM $< | \
	$(SED) 's, \($notdi $*)\.o\) *:,$(dir $@)\1 $@: ,' > $@.tmp
	$(MV) $@.tmp $@

 
