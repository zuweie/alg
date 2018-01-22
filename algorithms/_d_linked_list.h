#ifndef  _D_LINKED_LIST_H_
#define _D_LINKED_LIST_H_

#include "_entity.h"
#include "_list_node.h"

#define LIST_HEAD(pl) (&((pl)->sentinel))
#define LIST_TAIL(pl) (&((pl)->sentinel))
#define LIST_FIRST(pl) LIST_HEAD(pl)->next
#define LIST_LAST(pl)  LIST_TAIL(pl)->prev

typedef struct _DLinkedList {

  ListNode sentinel;
  size_t  size;

} DLinkedList;


int init_list(DLinkedList* plist);
int search_list(DLinkedList* plist, int key, ListNode** pnode);
int delete_list(DLinkedList* plist, int key, ListNode** pnode);
int insert_list_at_head(DLinkedList* plist, ListNode *pnode);
int insert_list_at_tail(DLinkedList* plist, ListNode *pnode);
int get_node(DLinkedList* plist, int i, ListNode** pnode);
int pop_list(DLinkedList* plist, ListNode** pnode);
#endif
