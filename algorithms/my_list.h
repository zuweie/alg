#ifndef __LIST_H__
#define __LIST_H__

#include "kv.h"

#define LIST_HEAD(pl) (&((pl)->sentinel))
#define LIST_TAIL(pl) (&((pl)->sentinel))
#define LIST_FIRST(pl) LIST_HEAD(pl)->next
#define LIST_LAST(pl)  LIST_TAIL(pl)->prev

typedef struct l_node {

  kv_t kv;
  struct l_node* prev;
  struct l_node* next;  
	
} node_t;

typedef struct linked_list {

  node_t sentinel;
  size_t  size;

} list_t;


int init_list(list_t* plist);
int search_list(list_t* plist, int key, node_t** pnode);
int delete_list(list_t* plist, int key, node_t** pnode);
int insert_list_at_head(list_t* plist, node_t *pnode);
int insert_list_at_tail(list_t* plist, node_t *pnode);
int get_node(list_t* plist, int i, node_t** pnode);
int pop_list(list_t* plist, node_t** pnode);
#endif
