#include <stdlib.h>
#include "_d_linked_list.h"

extern int dlist_init(DLinkedList* plist){
   plist->size = 0;
   LIST_FIRST(plist) = LIST_HEAD(plist);
   LIST_LAST(plist)  = LIST_TAIL(plist);
   return 0;
}

// 再头部添加
extern int dlist_put(DLinkedList* plist, Entity e) 
{
    ListNode* pnode = (ListNode*) malloc(sizeof(ListNode));
    pnode->_entity = e;
    
    ListNode* ph = LIST_HEAD(plist);
    ListNode* pf = LIST_FIRST(plist);

    ph->next = pnode;
    pnode->next = pf;
    
    pf->prev = pnode;
    pnode->prev = ph;
    return ++(plist->size);
}

// 在尾部添加
extern int dlist_push(DLinkedList* plist, Entity e)
{
    ListNode* pnode = (ListNode*) malloc(sizeof(ListNode));
    pnode->_entity = e;

    ListNode* pt = LIST_TAIL(plist);
    ListNode* pl = LIST_LAST(plist);

    pt->prev = pnode;
    pnode->prev = pl;

   pl->next = pnode;
   pnode->next = pt;
   return ++(plist->size);
}

extern ListNode* dlist_find(DLinkedList* plist, void* to_match, Entity** _entity)
{
    ListNode* pf;
    if (_entity)
        *_entity = NULL;
    int i=0;

    for(pf = LIST_FIRST(plist); pf != LIST_TAIL(plist); pf = pf->next){
        if (pf->_entity.compare(&(pf->_entity), to_match) == 0){
            if (_entity)
                *_entity =  &(pf->_entity);
            return pf;
	    }
    }
    return NULL;
}

extern int dlist_remove(DLinkedList* plist, void* to_match, Entity* _entity)
{
    ListNode* pf = dlist_find(plist, to_match, NULL);
    
    /*
    for (pf = LIST_FIRST(plist); pf != LIST_TAIL(plist); pf = pf->next){
        if (pf->_entity.compare(&(pf->_entity), to_match) == 0) break;
    }
    */

    if (pf) {
        pf->prev->next = pf->next;
        pf->next->prev = pf->prev;
        if (_entity) {
            *_entity = pf->_entity;
        }
        free(pf);
        --(plist->size);
    }
    return plist->size;
}

extern int dl_remove_all(DLinkedList* plist)
{
    ListNode* pf = LIST_FIRST(plist);
    while(pf != LIST_TAIL(plist)){
        pf->prev->next = pf->next;
        pf->next->prev = pf->prev;
        pf->_entity.cleanup && pf->_entity.cleanup(&(pf->_entity));
        // fee node;
        free(pf);
        pf = LIST_FIRST(plist);
    }
    plist->size = 0;
    return 0;
}

