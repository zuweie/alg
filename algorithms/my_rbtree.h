#ifndef __RB_TREE_H__
#define __RB_TREE_H__

#include "kv.h"

#define RED 0
#define BLACK 1

typedef struct _rb_tnode {

   char color;
   kv_t kv;
   struct _rb_tnode* parent;  
   struct _rb_tnode* left;
   struct _rb_tnode* right;

}rbnode_t;

typedef struct _rb_tree {
   
   rbnode_t* root;
   size_t    size;

}rbtree_t;

int init_rbtree(rbtree_t* pt);
int init_rbnode(rbnode_t* pnode, kv_t kv);
rbnode_t* rbtree_minimum (rbnode_t* pn);
rbnode_t* rbtree_maximum(rbnode_t* pn);
rbnode_t* rbtree_successor(rbnode_t* ptnode);
rbnode_t* rbtree_presuccessor(rbnode_t* ptnode);
int left_rotate(rbtree_t* prb, rbnode_t* px);
int right_rotate(rbtree_t* prb, rbnode_t* px);
rbnode_t* rb_search(rbnode_t* pt, int key);
int rb_insert_fixup(rbtree_t* prb, rbnode_t* pz);
int rb_insert(rbtree_t* prb, rbnode_t* pz);
int rb_delete_fixup(rbtree_t* prb, rbnode_t* px, rbnode_t* px_parent, int is_left);
rbnode_t* _rb_delete(rbtree_t* prb, rbnode_t* pz);
rbnode_t* rb_delete(rbtree_t* prb, int key);

#endif
