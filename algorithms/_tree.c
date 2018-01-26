#include <stdlib.h>
#include "_tree.h"

extern TreeNode* create_tnode(Entity kv)
{

    TreeNode* pt = (TreeNode*)malloc(sizeof(TreeNode));

    pt->parent = NULL;
    pt->left   = NULL;
    pt->right  = NULL;
    pt->_entity = kv;

    return pt;
}

extern int init_tree(Tree* ptree)
{
    ptree->root = NULL;
    ptree->size = 0;
    return 0;
}

extern int inorder_tree_walk (TreeNode* ptnode, int (*tnode_func)(TreeNode* ptnode))
{
    if (ptnode != NULL){
	    inorder_tree_walk(ptnode->left, tnode_func);
	    tnode_func(ptnode);
	    inorder_tree_walk(ptnode->right, tnode_func);
    }
    return 0;
}

extern TreeNode* tree_search(TreeNode* ptnode, void* to_match, Entity** entity)
{
   
    if (ptnode == NULL || ptnode->_entity.compare(&(ptnode->_entity), to_match) == 0){
        if (ptnode && entity) 
            *entity = &(ptnode->_entity);
	    return ptnode;
    }
    if (ptnode->_entity.compare(&(ptnode->_entity), to_match) > 0){
	    return tree_search (ptnode->left, to_match, entity);
    }else{
	    return tree_search (ptnode->right, to_match, entity);
    }
}

extern TreeNode* tree_minimum (TreeNode* ptnode)
{

    while(ptnode->left != NULL){
       ptnode = ptnode->left;
    }
    return ptnode;
}

extern TreeNode* tree_maximum(TreeNode* ptnode)
{

   while(ptnode->right != NULL){
      ptnode = ptnode->right;
   }
   return ptnode;
}

extern TreeNode* tree_successor(TreeNode* ptnode)
{
   if (ptnode->right != NULL){
      return tree_minimum(ptnode->right);
   }
   TreeNode* pp = ptnode->parent;
   while( pp != NULL && ptnode == pp->right){
      ptnode = pp;
      pp = ptnode->parent;
   }
   return pp;
}

extern TreeNode* tree_presuccessor(TreeNode* ptnode)
{
   if (ptnode->left != NULL){
	return tree_maximum(ptnode->left);
   }

   TreeNode* pp = ptnode->parent;
   while(pp != NULL && ptnode == pp->left){
       ptnode = pp;
       pp = ptnode->parent;
   }
   return pp;
}

extern int tree_insert(Tree* pt, Entity e)
{

    TreeNode* py = NULL;
	TreeNode* px = pt->root;

    TreeNode* pz = create_tnode(e);

    while(px != NULL){
       py = px;
       
       if (pz->_entity.compare(&(pz->_entity), &(py->_entity)) < 0){
           px = px->left;	   		
       }else{
           px = px->right;
       }
    }

   pz->parent = py;
   if (py == NULL){
       // 树是空的，把节点放在root里
       pt->root = pz;
   }else{
       
       if (py->_entity.compare(&(py->_entity), &(pz->_entity)) > 0){
	        py->left = pz;
       }else{
	        py->right = pz;
       }
   }
   return 0;
}

// 这里的中心思想就是将pz的后继py抽出来，
// 然后将py的数据复制入pz中。

extern TreeNode* _tree_delete(Tree* pt, TreeNode* pz)
{
  
	TreeNode* py = NULL;
	TreeNode* px = NULL;

   if (pz->left != NULL || pz->right != NULL){
	    py = pz;      
   }else{
        py = tree_successor(pz);
   }
   
   
   // 这里将 py 抽出去了。 也就是将 pz的后继 抽出去了
   if (py->left != NULL)
	    px = py->left;
   else
        px = py->right;

   if (px != NULL)
	px->parent = py->parent;
  
   if (py == NULL)
        pt->root = px;
   else if (py == py->parent->left)
	    // py 是他老子的左孩子
        // 把px设为py老子的左孩子
	    py->parent->left = px;
   else
	    // py 是他老子的右孩子
        // 把px设为py老子的右孩子
   	    py->parent->right = px;

   if (py != pz){
       Entity kk = pz->_entity;
       pz->_entity = py->_entity;
       py->_entity = kk;
   }
   pt->size--;
   return py;
}

extern int tree_delete(Tree* pt, void* to_match, Entity* _entity)
{
    
	TreeNode* pn = tree_search(pt->root, to_match, NULL);
    TreeNode* pd =  _tree_delete(pt,  pn);

    if (pn){
        if (_entity){
            *_entity = pn->_entity;
        }
        free(pn);
    }
    return pt->size;
}

