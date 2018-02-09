local_dir      := $(project_dir)/algorithms
local_sources  := _hash.c _d_linked_list.c _select.c  _tree.c _sort.c _heap.c _rb_tree.c _entity.c
local_src      := $(addprefix $(local_dir)/, $(local_sources))
local_ex_clean := $(local_dir)/*.*~

sources     += $(local_src)
extra_clean += $(local_ex_clean) 




  
