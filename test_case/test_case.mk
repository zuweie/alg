local_dir      := $(project_dir)/test_case
local_sources  := test_alg.c helper.c
local_src      := $(addprefix $(local_dir)/, $(local_sources))
local_ex_clean := $(local_dir)/*.*~
    
test_sources   += $(local_src)
extra_clean += $(local_ex_clean) 
