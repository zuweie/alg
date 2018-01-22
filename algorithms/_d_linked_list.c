#include <stdlib.h>

#include "_d_linked_list.h"

extern int init_list(DLinkedList* plist){
   plist->size = 0;
   LIST_FIRST(plist) = LIST_HEAD(plist);
   LIST_LAST(plist)  = LIST_TAIL(plist);
   return 0;
}

extern int search_list(DLinkedList* plist, int key, ListNode** pnode){
	ListNode* pf;
    *pnode = NULL; 
    for(pf = LIST_FIRST(plist); pf != LIST_TAIL(plist); pf = pf->next){
        if (pf->_entity.key == key){
	   *pnode = pf;
           break;
	}
    }
    return 0;
}

// insert like head
extern int insert_list_at_head(DLinkedList* plist, ListNode* pnode){
	ListNode* ph = LIST_HEAD(plist);
	ListNode* pf = LIST_FIRST(plist);

    ph->next = pnode;
    pnode->next = pf;
    
    pf->prev = pnode;
    pnode->prev = ph;
    return ++(plist->size);
}

extern int insert_list_at_tail(DLinkedList* plist, ListNode* pnode){
	ListNode* pt = LIST_TAIL(plist);
	ListNode* pl = LIST_LAST(plist);

    pt->prev = pnode;
    pnode->prev = pl;

   pl->next = pnode;
   pnode->next = pt;
   return ++(plist->size);
}

extern int get_node(DLinkedList* plist, int i, ListNode** pnode){
    *pnode = NULL;
    ListNode* pn;
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

extern int delete_list(DLinkedList* plist, int key, ListNode** pnode){

    search_list(plist, key, pnode);

    if (*pnode){
    	(*pnode)->prev->next = (*pnode)->next;
        (*pnode)->next->prev = (*pnode)->prev;
        return --(plist->size);
    }else{
    	return -1;
    }
}

extern int pop_list(DLinkedList* plist, ListNode** pnode){
     if (plist->size != 0){
    	 ListNode* pn = LIST_LAST(plist);
       return delete_list(plist, pn->_entity.key, pnode);
     }else{
	*pnode = NULL;
        return plist->size;
     }
}

