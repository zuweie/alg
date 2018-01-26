#ifndef _BIN_TREE_H_
#define _BIN_TREE_H_

#include "_entity.h"

typedef struct _TreeNode {
  Entity _entity;
  struct _TreeNode* parent;
  struct _TreeNode* left;
  struct _TreeNode* right;
} TreeNode;

typedef struct _Tree{
	TreeNode* root;
	size_t   size;
} Tree;

extern TreeNode* create_tnode(Entity kv);
extern int init_tree(Tree* ptree);
extern int inorder_tree_walk (TreeNode* ptnode, int (*tnode_func)(TreeNode* ptnode));
extern TreeNode* tree_search(TreeNode* ptnode, void* to_match, Entity** entity);
extern TreeNode* tree_minimum (TreeNode* ptnode);
extern TreeNode* tree_maximum(TreeNode* ptnode);
extern TreeNode* tree_successor(TreeNode* ptnode);
extern TreeNode* tree_presuccessor(TreeNode* ptnode);
extern int tree_insert(Tree* pt, Entity e);
extern TreeNode* _tree_delete(Tree* pt, TreeNode* pz);
extern TreeNode* tree_delete(Tree* pt, int key);
#endif
