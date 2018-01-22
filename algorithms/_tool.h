#ifndef __MY_TOOL_H__
#define __MY_TOOL_H__

#include "_d_linked_list.h"
#include "_tree.h"
#include "_rb_tree.h"

#define BOOLEAN int
#define TRUE 1
#define FALSE 0

void fill_kv_array_random(Entity kv_arr[], size_t size);
void print_kv_key(Entity kv_arr[], size_t size);
void print_heap(Entity kv_arr[], size_t size);
void fill_linked_list_random(DLinkedList* plist, size_t size);
void print_linked_list(DLinkedList* plist, BOOLEAN reverse);
void cleanup_linked_list(DLinkedList* plist);
void print_tree(Tree* pt, size_t width);
void print_rb_tree(RBTree* prb);
#endif
