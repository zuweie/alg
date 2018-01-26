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

extern RBTreeNode* create_rbnode( Entity data);

extern RBTreeNode* rbtree_minimum (RBTreeNode* pn);

extern RBTreeNode* rbtree_maximum(RBTreeNode* pn);

extern RBTreeNode* rbtree_successor(RBTreeNode* ptnode);

extern RBTreeNode* rbtree_presuccessor(RBTreeNode* ptnode);

extern int left_rotate(RBTree* prb, RBTreeNode* px);

extern int right_rotate(RBTree* prb, RBTreeNode* px);

extern RBTreeNode* rb_search(RBTreeNode* pt, void* to_match, Entity** entity);

extern int rb_insert_fixup(RBTree* prb, RBTreeNode* pz);

extern int rb_insert(RBTree* prb, Entity e);

extern int rb_delete_fixup(RBTree* prb, RBTreeNode* px, RBTreeNode* px_parent, int is_left);

extern int rb_delete(RBTree* prb, void* to_match, Entity *entity);

#endif