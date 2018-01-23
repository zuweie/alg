#include <stdlib.h>
#include <string.h>
#include "_d_linked_list.h"
#include "_set.h"

extern int set_init(Set* pset) 
{
    return init_list(pset);
}


extern int set_insert(Set* pset, Set* pnode) 
{
    int is_member;
    if ((is_member = set_is_member(pset, pnode)) ==0 ){
        return insert_list_at_tail(pset, pnode);
    }else{
        return is_member;
    }
}

extern int set_remove(Set* pset, int key, ) 
{
    
}