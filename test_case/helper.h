#ifndef _HELPER_H_
#define _HELPER_H_
#include "_entity.h"
#include "_d_linked_list.h"

#define BOOLEAN int
#define TRUE 1
#define FALSE 0

extern void init_ie_arr(Entity _arr[], size_t size);
extern void print_entity(Entity* e);
extern void print_entity_arr(Entity kv_arr[], size_t size);
extern void print_heap(Entity kv_arr[], size_t heap_sz);
extern void fill_linked_list_random(DLinkedList* plist, Entity _arr[], int arr_size);
extern void print_linked_list(DLinkedList *plist, BOOLEAN reverse);
extern int cleanup_listnode(Entity* e);

#endif