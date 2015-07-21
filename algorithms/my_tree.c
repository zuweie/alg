#include <stdlib.h>
#include "my_tree.h"

int init_tnode(tnode_t* pt, kv_t kv){
    pt->parent = NULL;
    pt->left   = NULL;
    pt->right  = NULL;
    pt->kv = kv;
    return 0;
}

int init_tree(tree_t* ptree){
    ptree->root = NULL;
    ptree->size = 0;
    return 0;
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
    while(pt->left != NULL){
       pt = pt->left;
    }
    return pt;
}

tnode_t* tree_maximum(tnode_t* ptnode){
   tnode_t* pt = ptnode->right;
   while(pt->right != NULL){
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

int tree_insert(tree_t* pt, tnode_t* pz){

   tnode_t* py = NULL;
   tnode_t* px = pt->root;

   while(px != NULL){
       py = px;
       // 一直往下走，走到就是叶子所在地方
       if (pz->kv.key < py->kv.key){
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
	//
       if (py->kv.key > pz->kv.key){
	  py->left = pz;
       }else{
	  py->right = pz;
       }
   }
   return 0;
}

// 这里的中心思想就是将pz的后继py抽出来，
// 然后将py的数据复制入pz中。

tnode_t* _tree_delete(tree_t* pt, tnode_t* pz){
  
   tnode_t* py = NULL;
   tnode_t* px = NULL;

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

   // end 将py 抽出去了。   

   if (py != pz){
       kv_t kk = pz->kv;
       pz->kv = py->kv;
       py->kv = kk;
   }
   
   return py;
}

tnode_t* tree_delete(tree_t* pt, int key){
   tnode_t* pn = tree_search(pt->root,key);
   return _tree_delete(pt,  pn);
}
