local_dir      := $(project_dir)/algorithms
local_sources  := my_hash.c my_list.c my_select.c my_tool.c my_tree.c sort.c heap.c my_rbtree.c
local_src      := $(addprefix $(local_dir)/, $(local_sources))
local_obj      := $(subst .c, .o, $(local_src))
local_ex_clean := $(local_dir)/*.*~

sources     += $(local_src)
extra_clean += $(local_ex_clean) 




  
