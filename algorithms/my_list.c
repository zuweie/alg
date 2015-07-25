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

// insert like head
int insert_list_at_head(list_t* plist, node_t* pnode){
    node_t* ph = LIST_HEAD(plist);
    node_t* pf = LIST_FIRST(plist);

    ph->next = pnode;
    pnode->next = pf;
    
    pf->prev = pnode;
    pnode->prev = ph;
    return ++(plist->size);
}

int insert_list_at_tail(list_t* plist, node_t* pnode){
    node_t* pt = LIST_TAIL(plist);
    node_t* pl = LIST_LAST(plist);

    pt->prev = pnode;
    pnode->prev = pl;

   pl->next = pnode;
   pnode->next = pt;
   return ++(plist->size);
}

int get_node(list_t* plist, int i, node_t** pnode){
    *pnode = NULL;
    node_t* pn;
    int j;
    int hs = (plist->size) / 2;
    if (i <= hs)
	// 从头开始找起
	for (pn = LIST_FIRST(plist), j=0; 
	     pn != LIST_TAIL(plist), j != i; 
	     pn = pn->next, ++j);
    else
        // 从尾部开始找起
	for (pn = LIST_LAST(plist), j=plist->size-1;
	     pn != LIST_HEAD(plist), j != i;
	     pn = pn->prev, --j);

    if (j == i)
    	*pnode = pn;

    return 0;
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

int pop_list(list_t* plist, node_t** pnode){
     if (plist->size != 0){
       node_t* pn = LIST_LAST(plist);
       return delete_list(plist, pn->kv.key, pnode);
     }else{
	*pnode = NULL;
        return plist->size;
     }
}
