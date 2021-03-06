#include <stdlib.h>
#include "_entity.h"
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

extern ListNode* dlist_find(DLinkedList* plist, ListNode* start_from, Entity e, Ecmp filter, Entity** _entity)
{
    ListNode* pf;
    if (_entity)
        *_entity = NULL;

    for(pf = start_from; pf != LIST_TAIL(plist); pf = pf->next){
        if ( filter && filter(&(pf->_entity), &e) ){
           if (_entity)
                *_entity =  &(pf->_entity);
            return pf;
	    }
    }
    return NULL;
}

extern ListNode* dlist_remove(DLinkedList* plist, ListNode* start_from, Entity e, Ecmp filter, Entity* _entity)
{
    ListNode* pf = dlist_find(plist, start_from, e, filter,  NULL);
    ListNode* next = NULL;
    if (pf) {
        next = pf->next;
        pf->prev->next = pf->next;
        pf->next->prev = pf->prev;
        if (_entity) {
            *_entity = pf->_entity;
        }
        free(pf);
        --(plist->size);
    }
    return next;
}

extern int dlist_remove_all(DLinkedList* plist, int (*cleanup)(Entity* e))
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

