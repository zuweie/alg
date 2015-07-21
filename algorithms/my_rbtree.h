#ifndef __RB_TREE_H__
#define __RB_TREE_H__

#include "kv.h"

#define RED = 1;
#define BLACK = 0;

#define RB_NIL(pt) (&((pt)->nil))

typedef struct _rb_tnode {

   char color;
   kv_t kv;
   struct rb_tnode* parent;  
   struct rb_tnode* left;
   struct rb_tnode* right;

}rbnode_t;

typedef struct _rb_tree {
   
   rbnode_t* root;

   // 红黑树哨兵节点 nil
   rbnode_t  nil;
   size_t    size;

}rbtree_t;


int init_rbtree(rbtree_t* pt);
int init_rbnode(rbnode_t* pnode, kv_t kv);
int left_rotate(rbtree_t* prb, rbnode_t* pnode);
int right_rotate(rbtree_t* prb, rbnode_t* pnode);
int rb_insert_fixup(rbtree_t* prb, rbnode_t* pnode);
int rb_insert(rbtree_t* prb, rbnode_t* pnode);
int rb_delete_fixup(rbtree_t* prb, rbnode_t* pnode);
int _rb_delete(rbtree_t* prb, rbnode_t* pnode);
int rb_delete(rbtree_t* prb, int key);

#endif
