programs    := test_alg
libs        := libalg.a
alg_sources  := 
test_sources :=
extra_clean := *~


alg_objects   = $(subst .c,.o,$(alg_sources))
test_objects  = $(subst .c,.o,$(test_sources))


project_dir   := $(shell pwd)
include_dirs  := $(project_dir)/algorithms/
sources_dirs  := $(project_dir)/algorithms/ 
testcase_dirs := $(project_dir)/test_case/

exportheader_dir := $(project_dir)/out/export_header/

bin_dir       := out

INCLUDE_FLAGS   := $(addprefix -I, $(include_dirs))
PROGRAM_CFLAGS  += $(INCLUDE_FLAGS) -lm -lcunit -g
LIBS_CFLAGS     += $(INCLUDE_FLAGS) -lm -g

MV  :=  mv -f
RM  :=  rm -f
SED := sed

include algorithms/alg.mk
include test_case/test_case.mk

.PHONY: all
all: $(programs)

$(programs): $(alg_sources) $(test_sources)
	$(CC) $(PROGRAM_CFLAGS) $^ -o $(bin_dir)/$@

.PHONY: libs
libs: $(libs)

$(libs): $(alg_objects)
	$(AR) -r $(bin_dir)/$@ $(alg_objects) 
	cp $(include_dirs)/*.h $(exportheader_dir)

.PHONY: clean
clean:
	$(RM) $(alg_objects) $(test_objects) $(bin_dir)/$(programs) $(bin_dir)/$(libs) $(exportheader_dir)/*.h $(extra_clean)

 
