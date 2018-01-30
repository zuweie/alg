#include "_entity.h"

extern void init_ie_arr(Entity _arr[], size_t size);
extern void print_entity(Entity* e);
extern void print_entity_arr(Entity kv_arr[], size_t size);
extern void print_heap(Entity kv_arr[], size_t heap_sz);
extern void fill_linked_list_random(DLinkedList* plist, Entity _arr[], arr_size);
extern void cleanup_listnode(Entity* e);