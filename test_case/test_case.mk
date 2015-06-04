local_dir      := ~/WorkShop/code/Algorithms/test_case
local_sources   := test_alg.c
local_src      := $(addprefix $(local_dir)/, $(local_sources))
local_obj      := $(subst .c, .o, $(local_src))
local_ex_clean := $(local_dir)/*.*~
    
sources     += $(local_src)
extra_clean += $(local_ex_clean) 
