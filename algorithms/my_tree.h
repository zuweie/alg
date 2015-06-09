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

#endif
