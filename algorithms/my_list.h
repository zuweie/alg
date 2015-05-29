#ifndef __LIST_H__
#define __LIST_H__

#include "kv.h"

#define LIST_HEAD(l) (&(l->sentinel))
#define LIST_TAIL(l) (&(l->sentinel))
#define LIST_FIRST(l) LIST_HEAD(l)->next
#define LIST_LAST(l)  LIST_TAIL(l)->prev

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
int insert_list(list_t* plist, node_t *pnode);

#endif
