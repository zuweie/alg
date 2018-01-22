#ifndef __RB_TREE_H__
#define __RB_TREE_H__

#include "_entity.h"

#define RED 0
#define BLACK 1

typedef struct _RBTreeNode {

   char color;
   Entity _entity;
   struct _RBTreeNode* parent;
   struct _RBTreeNode* left;
   struct _RBTreeNode* right;

}RBTreeNode;

typedef struct _RBTree {
   
   RBTreeNode* root;
   size_t    size;

}RBTree;

extern int init_rbtree(RBTree* pt);

extern int init_rbnode(RBTreeNode* pnode, Entity data);

extern int init_rbnode_entity(RBTree* prb, RBTreeNode* pnode, int key, void* v);

extern RBTreeNode* rbtree_minimum (RBTreeNode* pn);

extern RBTreeNode* rbtree_maximum(RBTreeNode* pn);

extern RBTreeNode* rbtree_successor(RBTreeNode* ptnode);

extern RBTreeNode* rbtree_presuccessor(RBTreeNode* ptnode);

extern int left_rotate(RBTree* prb, RBTreeNode* px);

extern int right_rotate(RBTree* prb, RBTreeNode* px);

extern RBTreeNode* rb_search(RBTreeNode* pt, int key);

extern int rb_insert_fixup(RBTree* prb, RBTreeNode* pz);

extern int rb_insert(RBTree* prb, RBTreeNode* pz);

extern int rb_delete_fixup(RBTree* prb, RBTreeNode* px, RBTreeNode* px_parent, int is_left);

extern RBTreeNode* _rb_delete(RBTree* prb, RBTreeNode* pz);

extern RBTreeNode* rb_delete(RBTree* prb, int key);

#endif
