#include <stdlib.h>
#include "my_rbtree.h"

int init_rbtree(rbtree_t* pt){
   pt->nil->color = BLACK;
   pt->nil->parent = NULL;
   pt->nil->left   = NULL;
   pt->nil->right  = NULL;

   pt->root = RB_NIL(pt);
   pt->size = 0;
   // init nil node;
   return 0;
}

int init_rbnode(rbtree_t* prb, rbnode_t* pnode, kv_t kv){
   pnode->parent = RB_NIL(prb);
   pnode->left   = RB_NIL(prb);
   pnode->right  = RB_NIL(prb);
   pnode->kv     = kv;
   return 0;
}

rbnode_t* rbtree_minimum (rbnode_t* pn){
    rbnode_t* pm = pn->left;
    while(pm->left != NULL){
       pm = pm->left;
    }
    return pm;
}

rbnode_t* rbtree_maximum(rbnode_t* pn){
   rbnode_t* pmx = ptnode->right;
   while(pmx->right != NULL){
      pmx = pmx->right;
   }
   return pmx;
}

rbnode_t* rbtree_successor(rbnode_t* ptnode){
   if (ptnode->right != NULL){
      return tree_minimum(ptnode->right);
   }
   rbnode_t* pp = ptnode->parent;
   while( pp != NULL && ptnode == pp->right){
      ptnode = pp;
      pp = ptnode->parent;
   }
   return pp;
}

rbnode_t* rbtree_presuccessor(rbnode_t* ptnode){
   if (ptnode->left != NULL){
	return tree_maximum(ptnode->left);
   }

   rbnode_t* pp = ptnode->parent;
   while(pp != NULL && ptnode == pp->left){
       ptnode = pp;
       pp = ptnode->parent;
   }
   return pp;
}

int left_rotate(rbtree_t* prb, rbnode_t* px){
   // 先东自己的右子树。
   // py为px 的右子树。
   // 将py的左子树变成自己的右子树了。
   // 也就市讲自己的孙子变为儿子了。

   rbnode_t* py = px->rigth;
   px->right    = py->left;
   py->left->parent = px;
    
   // 设置py的新老爸
   py->parent = px->parent;

   // 设置py新老板的新儿子。
   if (px->parent == RB_NIL(prb)){
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

int right_rotate(rbtree_t* prb, rbnode_t* px){
   rbnode_t* py = px->left;
   px->left     = py->right;
   py->right->parent = px;

   py->parent = px->parent;

   if(px->parent == RB_NIL(prb)){
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

rbnode_t* rb_search(rbtree_t* prb, rbnode_t* pt, int key){
    if (pt == RB_NIL(prb) || pt->kv.key == key){
        return pt;
    }

    if (key < pt->kv.key){
	return rb_search(prb, pt->left, key);
    }else{
	return rb_search(prb, pt->right, key);
    }
}

int rb_insert_fixup(rbtree_t* prb, rbnode_t* pz){
    while( pz->parent->color == RED){

       // 能来到这里都违反了性质4 ： 老子是红色。但自己也是红色。
       // pz的老子是左子树
       if (pz->parent == pz->parent->parent->left){
	   // py 是 pz 老子的右兄弟。也就是其右叔叔
           rbnode_t* py = pz->parent->parent->right;
	   
	   if (py->color == RED){
               // 如果其叔叔是红色 case 1
               // 将pz老子染为黑色
               pz->parent->color = BLACK;
	       // 将pz的叔叔py染为黑色。
               py->color = BLACK;
	       // 将pz的祖父染为红色。
               pz->parent->parent = RED;
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
           rbnode_t* py = pz->parent->parent->left;
	   if (py->color == RED){
              //如果其叔叔是红色 CASE 1
              // 将pz的老子染为黑色。
	      pz->parent->color = BLACK;
	      // 将pz的左叔叔染为黑色
              py->color = BLACK;
	      // 将祖父染为红色
	      pz->parent->parent = RED;
	      // pz的指针跳到祖父哪里。妈的如果祖父是root 那么case三怎么执行啊
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

int rb_insert(rbtree_t* prb, rbnode_t* pnode){
    rbnode_t* py = RB_NIL(prb);
    rbnode_t* px = prb->root;
    
    while(px != RB_NIL(prb)){
        py = px;
        if (pz->kv.key < px->kv.key){
	    px = px->left;
        }else{
	    px = px->right;
        }
    }
    
    pz->parent = py;

    if (py == RB_NIL(prb)){
	prb->root = pz;
    }else if (pz->kv.key < py->kv.key){
	py->left = pz;
    }else{
        py->right = pz;
    }

    pz->left = RB_NIL(prb);
    pz->right = RB_NIL(prb);
    pz->color = RED;
    return rb_insert_fixup(prb, pz);
}

int rb_delete_fixup(rbtree_t* prb, rbnode_t* px){

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

    rbnode_t pw;
    while(px != prb->root &&  px->color = BLACK){
	if (px == px->parent->left){
	    // 如果px是左孩子。
            // 取pw为px的右兄弟。
	    pw = px->parent->right;
            if (pw->color == RED){
		//CASE 1
		//若pw是红色。将其染为黑色
		pw->color = BLACK;
		// 将其老子染为红色。
		pw->parent = RED;
	        // 将老子转下来. px->parent 其实和 pw->parent 是一样的。
                left_rotate(prb, px->parent);
		// 左转了一下以后pw变成px的老子的老子。
                // 再把pw移下来变回px的右兄弟。
   		pw = px->parent->right;
	     }
             if (pw->left->color == BLACK && pw->right->color == BLACK){
                // 若是pw的两个儿子都是黑色的。CASE 2
		// 将其pw染为红色
		 pw->color = RED;
		 px = px->parent;
              }else{ 
                   // CASE 3 
		 if (pw->right == BLACK){
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
	         pw->color = px->parent->color;
		 px->parent->color = BLACK;
                 pw->right->color  = BLACK;
		 left->rotate(T, px->parent);
		 prb->root = px;
               } // else
            }
        }else{
	    // px 为右孩子
	    // pw 为其左叔叔
	    pw = px->parent->lef;
	    if (pw->color == RED){
                // CASE 1
                pw->color = RED;
                right_rotate(prb, px);
                pw = px->parent->left;
            }
	    
            if (pw->left->color == BLACK && pw->right->color){
		// CASE 2
                pw->color = RED;
                px = px->parent;
            }else{
                // CASE 3
                if (pw->left = BLACK){
                   pw->right = BLACK;
	           left_rotate(prb, pw);
                   pw = px->parent->left; 
                }
		pw->color = px->parent->color;
                px->parent = BLACK;
	        pw->left->color = BLACK;
	        right_rotate(prb, px->parent);
                // 完全不能理解为毛这里要将px设置为根，难道进入CASE 4 就到顶部了么?
	        prb->root = px;
            }
        }
    }// while
    px->color = BLACK;
}

rbnode_t* _rb_delete(rbtree_t* prb, rbnode_t* pz){
    rbnode_t* py;
    rbnode_t* px
    if (pz->left == RB_NIL(prb) || pz->right == RB_NIL(prb)){
	py = pz;
    }else{
	py = rbtree_successor(pz);
    }

    if (py->left != RB_NIL(prb)){
	px = py->left;
    }else{
	px = py->right;
    }

    px->parent = py->parent;
    
    if (py == RB_NIL(prb)){
	prb->root = px;
    }else if (py == py->parent->left){
	py->parent->left = px;
    }else{
	py->parent->right = px;
    }
    
    if (py != pz){
	kv_t kv = pz->kv;
	pz->kv = py->kv;
        py->kv = kv;
    }
    
    if (py->color = BLACK){
	rb_delete_fixup(prb, px);
    }

    return py;
}

rbnode_t* rb_delete(rbtree_t* prb, int key){
    rbnode_t* pz = rb_search(prb, prb->root, key);
    if (pz != RB_NIL(prb))
	return _rb_delete(prb, pz);
}


