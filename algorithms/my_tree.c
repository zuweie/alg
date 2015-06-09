#include <stdio.h>
#include "my_tree.h"

int init_tree(tree_t* ptree){
    ptree->root = NULL;
    ptree->size = 0; 
}

int inorder_tree_walk (tnode_t* ptnode, int (*tnode_func)(tnode_t* ptnode)){
    if (ptnode != NULL){
	inorder_tree_walk(ptnode->left, tnode_func);
	tnode_func(ptnode);
	inorder_tree_walk(ptnode->right, tnode_func);
    }
    return 0;
}

tnode_t* tree_search(tnode_t* ptnode, int key){
    if (ptnode == NULL || ptnode->kv.key == key){
	return ptnode;
    }
    if (key < ptnode->kv.key){
	return tree_search (ptnode->left, key);
    }else{
	return tree_search (ptnode->right, key);
    }
}

tnode_t* tree_minimum (tnode_t* ptnode){
    tnode_t* pt = ptnode->left;
    while(pt != NULL){
       pt = pt->left;
    }
    return pt;
}

tnode_t* tree_maximum(tnode_t* ptnode){
   tnode_t* pt = ptnode->right;
   while(pt != NULL){
      pt = pt->right;
   }
   return pt;
}

tnode_t* tree_successor(tnode_t* ptnode){
   if (ptnode->right != NULL){
      return tree_minimum(ptnode->right);
   }
   tnode_t* pp = ptnode->parent;
   while( pp != NULL && ptnode == pp->right){
      ptnode = pp;
      pp = ptnode->parent;
   }
   return pp;
}

tnode_t* tree_presuccessor(tnode_t* ptnode){
   if (ptnode->left != NULL){
	return tree_maximum(ptnode->left);
   }

   tnode_t* pp = ptnode->parent;
   while(pp != NULL && ptnode == pp->left){
       ptnode = pp;
       pp = ptnode->parent;
   }
   return pp;
}
