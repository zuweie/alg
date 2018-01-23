#ifndef _LIST_NODE_H_
#define _LIST_NODE_H_

#include "_entity.h"

typedef struct _ListNode {

  Entity*  _entity;
  struct _ListNode* prev;
  struct _ListNode* next;

} ListNode;

#endif
