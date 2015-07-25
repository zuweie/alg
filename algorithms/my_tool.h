#ifndef __MY_TOOL_H__
#define __MY_TOOL_H__

#include "my_list.h"
#include "my_tree.h"
#include "my_rbtree.h"

#define BOOLEAN int
#define TRUE 1
#define FALSE 0

void fill_kv_array_random(kv_t kv_arr[], size_t size);
void print_kv_key(kv_t kv_arr[], size_t size);
void print_heap(kv_t kv_arr[], size_t size);
void fill_linked_list_random(list_t* plist, size_t size);
void print_linked_list(list_t* plist, BOOLEAN reverse);
void cleanup_linked_list(list_t* plist);
void print_tree(tree_t* pt, size_t width);
void print_rb_tree(rbtree_t* prb);
#endif
