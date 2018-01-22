#include <stdlib.h>
#include "_rb_tree.h"

extern int init_rbtree(RBTree* pt)
{

   pt->root = NULL;
   pt->size = 0;
   // init nil node;
   return 0;
}

extern int init_rbnode(RBTreeNode* pnode, Entity data)
{
   pnode->parent = NULL;
   pnode->left   = NULL;
   pnode->right  = NULL;
   pnode->_entity     = data;
   return 0;
}

extern int init_rbnode_entity(RBTree* prb, RBTreeNode* pnode, int key, void* v)
{
   pnode->parent = NULL;
   pnode->left   = NULL;
   pnode->right  = NULL;
   pnode->_entity.key = key,
   pnode->_entity.pdata = v;
   return 0;
}

extern RBTreeNode* rbtree_minimum (RBTreeNode* pn)
{
    
    while(pn->left != NULL){
       pn = pn->left;
    }
    return pn;
}

extern RBTreeNode* rbtree_maximum(RBTreeNode* pn)
{

   while(pn->right != NULL){
      pn = pn->right;
   }
   return pn;
}

extern RBTreeNode* rbtree_successor(RBTreeNode* ptnode)
{
   if (ptnode->right != NULL){
      return rbtree_minimum(ptnode->right);
   }
   RBTreeNode* pp = ptnode->parent;
   while( pp != NULL && ptnode == pp->right){
      ptnode = pp;
      pp = ptnode->parent;
   }
   return pp;
}

extern RBTreeNode* rbtree_presuccessor(RBTreeNode* ptnode)
{

   if (ptnode->left != NULL){
	return rbtree_maximum(ptnode->left);
   }

   RBTreeNode* pp = ptnode->parent;
   while(pp != NULL && ptnode == pp->left){
       ptnode = pp;
       pp = ptnode->parent;
   }
   return pp;
}

extern int left_rotate(RBTree* prb, RBTreeNode* px)
{
   // 先东自己的右子树。
   // py为px 的右子树。
   // 将py的左子树变成自己的右子树了。
   // 也就市讲自己的孙子变为儿子了。

	RBTreeNode* py = px->right;
   px->right    = py->left;
   
   if (py->left != NULL)
   	py->left->parent = px;
    
   // 设置py的新老爸
   py->parent = px->parent;

   // 设置py新老板的新儿子。
   if (px->parent == NULL){
	// 这里说明px是root
        prb->root = py;
   }else if (px == px->parent->left){
	// px 是他老子的左子树。
	px->parent->left = py;
   }else{
        // px 是他老子的右子树。
	px->parent->right = py;
   }
    
   
   py->left = px;
   px->parent = py;
   return 0;
}

extern int right_rotate(RBTree* prb, RBTreeNode* px)
{

	RBTreeNode* py = px->left;
   px->left     = py->right;
   
   if (py->right != NULL)
   	py->right->parent = px;

   py->parent = px->parent;

   if(px->parent == NULL){
      prb->root = py;
   }else if (px->parent->left == px){
      px->parent->left = py;
   }else{
      px->parent->right = py;
   }
   py->right = px;
   px->parent = py;
   return 0;
}

extern RBTreeNode* rb_search(RBTreeNode* pt, int key)
{
    if (pt == NULL || pt->_entity.key == key){
        return pt;
    }

    if (key < pt->_entity.key){
    	return rb_search(pt->left, key);
    }else{
    	return rb_search(pt->right, key);
    }
}


extern int rb_insert_fixup(RBTree* prb, RBTreeNode* pz)
{

    while(pz->parent != NULL &&  pz->parent->color == RED){

       // 能来到这里都违反了性质4 ： 老子是红色。但自己也是红色。
       // pz的老子是左子树

       if (pz->parent == pz->parent->parent->left){
	   // py 是 pz 老子的右兄弟。也就是其右叔叔
    	   RBTreeNode* py = pz->parent->parent->right;
	   
	   if (py != NULL && py->color == RED){
               // 如果其叔叔是红色 case 1
               // 将pz老子染为黑色
               pz->parent->color = BLACK;
	       // 将pz的叔叔py染为黑色。
               py->color = BLACK;
	       // 将pz的祖父染为红色。
               pz->parent->parent->color = RED;
	       // pz的指针跳到祖父哪里，进入下一伦循环。
	       pz = pz->parent->parent;
	       // 下一伦循环的时候自己也是红色。
               // 进去了就违反了性质4。
           }else{
               // case 2 3
	       if(pz == pz->parent->right){
                  // case 2 算法导论的 p171 页。
                  // 如果pz自己是右子树。这里还包含了一个隐藏条件就是，pz的右叔叔是黑色的。
                  // 如果pz的右叔叔是红色的，就会进入上面case1的处理。
                  // pz的指针跳到其父亲哪里。
              
                  pz = pz->parent;
                  // 然后左转一下。将pz。 这里旋转一下就是将其撸直了，让其出现case 3的情况。
                  left_rotate(prb, pz);
               }
               // case 3 这里无论如何都要做出调整的。
               pz->parent->color = BLACK;
               pz->parent->parent->color = RED;
               right_rotate(prb, pz->parent->parent);
	   } 
       }else{
	   // py 的 pz 是左子树， 也就是左叔叔。
    	   RBTreeNode* py = pz->parent->parent->left;
	   if (py != NULL && py->color == RED){
              //如果其叔叔是红色 CASE 1
              // 将pz的老子染为黑色。
	      pz->parent->color = BLACK;
	      // 将pz的左叔叔染为黑色
              py->color = BLACK;
	      // 将祖父染为红色
	      pz->parent->parent->color = RED;
	      // pz的指针跳到祖父哪里。妈的如果祖父是root
	      pz = pz->parent->parent;
              // 下一伦循环的时候自己也是红色。
              // 进去了就违反了性质4。
           }else{
	       // CASE 2 3
               if (pz == pz->parent->left){
	           // 如果pz是左子树。这里还包含了一个隐藏条件，pz的左叔叔。
		   // case 2 算法导论的 p171 页。
                  // 如果pz自己是右子树。这里还包含了一个隐藏条件就是，pz的右叔叔是黑色的。
                  // 如果pz的右叔叔是红色的，就会进入上面case1的处理。
                  // pz的指针跳到其父亲哪里。
	          pz = pz->parent;
                  right_rotate(prb, pz);
	       }

	       pz->parent->color = BLACK;
               pz->parent->parent->color = RED;
               left_rotate(prb, pz->parent->parent);
           }
       }
    }
    prb->root->color = BLACK;
    return 0;
}

extern int rb_insert(RBTree* prb, RBTreeNode* pz)
{
	RBTreeNode* py = NULL;
	RBTreeNode* px = prb->root;
    
    while(px != NULL){
        py = px;
        if (pz->_entity.key < px->_entity.key){
        	px = px->left;
        }else{
        	px = px->right;
        }
    }
    
    pz->parent = py;

    if (py == NULL){
    	prb->root = pz;
    }else if (pz->_entity.key < py->_entity.key){
    	py->left = pz;
    }else{
        py->right = pz;
    }

    pz->left = NULL;
    pz->right = NULL;
    pz->color = RED;
    return rb_insert_fixup(prb, pz);
}

extern int rb_delete_fixup(RBTree* prb, RBTreeNode* px, RBTreeNode* px_parent, int is_left)
{

    /*
     * 麻痹，好鸡巴复杂的逻辑啊。到底是怎么回事。谁他妈的发明红黑树啊。
     * 这里要好好说明算法的过程：
     * 1 删除z时候，y所在的位置：在rbtree中y一班是z的后置，于是y就差不多在底层：若y有右孩子那么y就在倒数第二层，x在底层。y没有右孩子y就在底层。
     *   详细见tree的删除过程
     *                            y
     *                            |
     *                            \
     *                             x (可能是NIL)
     *
     * 2 角色，y 是黑色的。x是他孩子（可能是NIL，黑色的)。在fixup的函数里面 y z是看不到的。他们的delete函数里面。
     *       y,被删掉的z的后继，是补充到z的位置上去的。
     *       x,y的左孩子或者右孩子。是补充到y的位置上去的。
     *
     * 3 分析，当y是黑色，被补充到z的位置上去的时候，y所在的位置就少了一个黑色。于是便不平衡。于是假设补充到y位置上的x继承y的黑色。也就是x有两个颜色。
     *   如果x是红色（那时x是红黑色）。那就皆大欢喜。直接将其变为黑色，（y的黑色便被保留了下来。大循环结束）。但如果x是黑色。他妈的就很鸡巴麻烦。
     *   x就有两个黑色。然后算法就是通过各种变态的旋转，旋转过程，保持颜色的平衡。将两个黑色往上扔，扔到再遇到红的节点
     *   (直接拉黑，等于那个少的分支黑加一，算法结束）。若是一直往上都没遇上红的。那让其到根部。那么从根出发的，多少重黑色都没问题。
     *
     */

    // 这里的px很可能是NULL
    // 若为NULL 则 那个    
	RBTreeNode* pw;
    while(px == NULL || (px != prb->root &&  px->color == BLACK)){
        
        if (px != NULL){
            px_parent = px->parent;
	    if (px == px_parent->left)
		is_left = 1;
	    else
		is_left = 0;
        }

	if (is_left){
	    	// 如果px是左孩子。
            // 取pw为px的右兄弟。
	    pw = px_parent->right;
        if (pw->color == RED){
            	//CASE 1
            	//若pw是红色。将其染为黑色
        		pw->color = BLACK;
        		// 将其老子染为红色。
        		px_parent = RED;
        		// 将老子转下来. px->parent 其实和 pw->parent 是一样的。
                left_rotate(prb, px_parent);
                // 左转了一下以后pw变成px的老子的老子。
                // 再把pw移下来变回px的右兄弟。
                pw = px_parent->right;
	     }
        if ((pw->left == NULL || pw->left->color == BLACK)
	       && (pw->right ==  NULL || pw->right->color == BLACK)){
                // 若是pw的两个儿子都是黑色的。CASE 2
        	// 将其pw染为红色
        	pw->color = RED;
        	px = px_parent;
        }else{
                   // CASE 3 
		 if (pw->right == NULL || pw->right->color == BLACK){
                      // 将CASE 3 转变为CASE 4
		      // 这里有一个右孩子是黑色，且左孩子是红色。
		      // 就将其红色的左孩子染为黑色。
		    pw->left->color = BLACK;
                      // 然后将自己染为红色
		    pw->color = RED;
		      // 把自己的左孩子右转上去。
		    right_rotate(prb, pw);
		    pw = pw->parent->right;
         }
		   // CASE 4 
	         pw->color = px_parent->color;
		 px_parent->color = BLACK;
		 if (pw->right)
                     pw->right->color  = BLACK;
		 left_rotate(prb, px_parent);
		 px = prb->root;
               } // else
        }else{
	    // px 为右孩子
	    // pw 为其左叔叔
	    pw = px_parent->left;
	    if (pw->color == RED){
                // CASE 1
                pw->color = BLACK;
                px_parent->color = RED;
                right_rotate(prb, px_parent);
                pw = px_parent->left;
            }
	    
            if ((pw->left == NULL || pw->left->color == BLACK) 
             && (pw->right == NULL || pw->right->color == BLACK)){
		// CASE 2
                pw->color = RED;
                px = px_parent;
            }else{
                // CASE 3
                if (pw->left == NULL || pw->left->color == BLACK){
                   pw->right->color = BLACK;
                   pw->color = RED;
                   left_rotate(prb, pw);
                   pw = px_parent->left; 
                }
                // CASE 4 
                pw->color = px_parent->color;
                px_parent->color = BLACK;
                if (pw->left)
                	pw->left->color = BLACK;
                right_rotate(prb, px_parent);
                px = prb->root;
            } // else
        }
    }// big while
    px->color = BLACK;
    return 0;
}

extern RBTreeNode* _rb_delete(RBTree* prb, RBTreeNode* pz)
{
	RBTreeNode* py;
	RBTreeNode* px;
    int is_left = 0;
    if (pz->left == NULL || pz->right == NULL){
    	py = pz;
    }else{
    	py = rbtree_successor(pz);
    }

    if (py->left != NULL){
    	px = py->left;
    }else{
    	px = py->right;
    }
	
    if (px != NULL)
    	px->parent = py->parent;
    
    if (py->parent == NULL){
    	prb->root = px;
    }else if (py == py->parent->left){
    	py->parent->left = px;
    	is_left = 1;
    }else{
    	py->parent->right = px;
    	is_left = 0;
    }
    
    if (py != pz){
    	Entity data = pz->_entity;
		pz->_entity = py->_entity;
        py->_entity = data;
    }
    
    if (py->color == BLACK && py->parent != NULL){
    	rb_delete_fixup(prb, px, py->parent, is_left);
    }

    --prb->size;

    return py;
}

extern RBTreeNode* rb_delete(RBTree* prb, int key)
{
	RBTreeNode* pz = rb_search(prb->root, key);
    if (pz)
    	return _rb_delete(prb, pz);
    return pz;
}

