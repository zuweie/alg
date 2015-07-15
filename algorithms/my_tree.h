#ifndef __BIN_TREE_H__
#define __BIN_TREE_H__

#include "kv.h"

typedef struct t_node {
  kv_t kv;
  struct t_node* parent;
  struct t_node* left;
  struct t_node* right;
} tnode_t;

typedef struct _tree{
  tnode_t* root;
  size_t   size;
} tree_t;

int init_tnode(tnode_t* pt, kv_t kv);
int init_tree(tree_t* ptree);
int inorder_tree_walk (tnode_t* ptnode, int (*tnode_func)(tnode_t* ptnode));
tnode_t* tree_search(tnode_t* ptnode, int key);
tnode_t* tree_minimum (tnode_t* ptnode);
tnode_t* tree_maximum(tnode_t* ptnode);
tnode_t* tree_successor(tnode_t* ptnode);
tnode_t* tree_presuccessor(tnode_t* ptnode);
int tree_insert(tree_t* pt, tnode_t* pz);
tnode_t* _tree_delete(tree_t* pt, tnode_t* pz);
tnode_t* tree_delete(tree_t* pt, int key);
#endif
