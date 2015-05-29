#include <stdlib.h>

#include "my_list.h"

int init_list(list_t* plist){
   plist->size = 0;
   LIST_FIRST(plist) = LIST_HEAD(plist);
   LIST_LAST(plist)  = LIST_TAIL(plist);
}

int search_list(list_t* plist, int key, node_t** pnode){
    node_t* pf;
    *pnode = NULL; 
    for(pf = LIST_FIRST(plist); pf != LIST_TAIL(plist); pf = pf->next){
        if (pf->kv.key == key){
	   *pnode = pf;
           break;
	}
    }
    return 0;
}

// insert a node before a 'key' node
int insert_list(list_t* plist, node_t* pnode){
    node_t* ph = LIST_HEAD(plist);
    node_t* pf = LIST_FIRST(plist);

    ph->next = pnode;
    pnode->next = pf;
    
    pf->prev = pnode;
    pnode->prev = ph;
    return ++(plist->size);
}

int delete_list(list_t* plist, int key, node_t** pnode){

    search_list(plist, key, pnode);

    if (*pnode){
	(*pnode)->prev->next = (*pnode)->next;
        (*pnode)->next->prev = (*pnode)->prev;
	return --(plist->size);
    }else{
	return -1;
    }
}

