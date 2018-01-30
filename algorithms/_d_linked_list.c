#include <stdlib.h>
#include "_entity.h"
#include "_d_linked_list.h"

extern int dlist_init(DLinkedList* plist, ecompare func){
   plist->size = 0;
   LIST_FIRST(plist) = LIST_HEAD(plist);
   LIST_LAST(plist)  = LIST_TAIL(plist);
   if (func) {
       plist->compare = func;
   }else{
       plist->compare = base_compare;
   }
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

extern ListNode* dlist_find(DLinkedList* plist, Entity e, Entity** _entity)
{
    ListNode* pf;
    if (_entity)
        *_entity = NULL;
    int i=0;

    for(pf = LIST_FIRST(plist); pf != LIST_TAIL(plist); pf = pf->next){
        if (plist->compare(&(pf->_entity), &e) == 0){
            if (_entity)
                *_entity =  &(pf->_entity);
            return pf;
	    }
    }
    return NULL;
}

extern int dlist_remove(DLinkedList* plist, Entity e, Entity* _entity)
{
    ListNode* pf = dlist_find(plist, e, NULL);
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

extern int dl_remove_all(DLinkedList* plist, int (*cleanup)(Entity* e))
{
    ListNode* pf = LIST_FIRST(plist);
    while(pf != LIST_TAIL(plist)){
        pf->prev->next = pf->next;
        pf->next->prev = pf->prev;
        // fee node;
        if (cleanup) {
            cleanup(&(pf->_entity));
        }
        free(pf);
        pf = LIST_FIRST(plist);
    }
    plist->size = 0;
    return 0;
}

