#include <stdlib.h>
#include "_d_linked_list.h"

extern int dlist_init(DLinkedList* plist){
   plist->size = 0;
   LIST_FIRST(plist) = LIST_HEAD(plist);
   LIST_LAST(plist)  = LIST_TAIL(plist);
   return 0;
}

extern Entity* dlist_search(DLinkedList* plist, int key){
	ListNode* pf;
    for(pf = LIST_FIRST(plist); pf != LIST_TAIL(plist); pf = pf->next){
        if (pf->_entity->key == key){
	        return pf->_entity;
	    }
    }
    return NULL;
}

// insert like head
extern int dlist_insert_at_head(DLinkedList* plist, Entity* entity){

	ListNode* phead = LIST_HEAD(plist);
	ListNode* pfirst = LIST_FIRST(plist);

    ListNode* pnode = (ListNode*)malloc(sizeof(ListNode));
    pnode->_entity = entity;
    
    phead->next = pnode;
    pnode->next = pfirst;
    
    pfirst->prev = pnode;
    pnode->prev = phead;

    return ++(plist->size);
}

extern int dlist_insert_at_tail(DLinkedList* plist, Entity* entity){

	ListNode* ptail = LIST_TAIL(plist);
	ListNode* plast = LIST_LAST(plist);

    ListNode* pnode = (ListNode*)malloc(sizeof(ListNode));
    pnode->_entity = entity;

    ptail->prev = pnode;
    pnode->prev = plast;

    plast->next = pnode;
    pnode->next = ptail;
   
    return ++(plist->size);
}

extern Entity* get_at (DLinkedList* plist, int i){

    ListNode* pn;
    int j;
    int middle = (plist->size) / 2;
    if (i <= middle){
    // 从头开始找起
	    for (pn = LIST_FIRST(plist), j=0; 
	        pn != LIST_TAIL(plist), j != i; 
	        pn = pn->next, ++j);
    }else{
        // 从尾部开始找起
	    for (pn = LIST_LAST(plist), j=plist->size-1;
	        pn != LIST_HEAD(plist), j != i;
	        pn = pn->prev, --j);
    }

    if (j == i)
        return pn->_entity;
    return NULL;
}

extern Entity* dlist_remove(DLinkedList* plist, int key){

    /*
    if (*pnode){
    	(*pnode)->prev->next = (*pnode)->next;
        (*pnode)->next->prev = (*pnode)->prev;
        return --(plist->size);
    }else{
    	return -1;
    }
    */
}

extern int delete_list(DLinkedList* plist, ListNode* pnode) 
{
    if (LIST_SIZE(plist)){
        pnode->prev->next = pnode->next;
        pnode->next->prev = pnode->prev;
        return --(plist->size);
    }
}

extern int pop_list(DLinkedList* plist, ListNode** pnode){
     if (plist->size != 0){
    	 ListNode* pn = LIST_LAST(plist);
         //return delete_list(plist, pn->_entity.key, pnode);
         return delete_list(plist, pn);
     }else{
	    *pnode = NULL;
        return plist->size;
     }
}

