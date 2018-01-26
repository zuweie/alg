#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "_entity.h"
#include "_heap.h"
#include "_tree.h"
#include "_d_linked_list.h"
#include "_tool.h"
#include "_rb_tree.h"

void fill_kv_array_random(Entity kv_arr[], size_t size){
   srand(time(NULL));
   int i;
   for (i=0; i<size; ++i){
      kv_arr[i].key = rand() % 10000;
      kv_arr[i].pdata = NULL;
   }
}

void print_kv_key(Entity kv_arr[], size_t size){
   int i;
   printf("\n key: ");
   for (i=0; i<size; ++i){
      printf("%d ", kv_arr[i].key);
   }
   printf("\n");
}

void print_heap(Entity kv_arr[], size_t heap_sz){

   int h = log2(heap_sz);
   int hi, lb, li, lsz; 
   printf("\n");
   for (hi=0; hi<h; ++hi){
       lb = pow(2, hi) -1;
       lsz = pow(2, hi);
       for (li=0; li<lsz; ++li){
	  int i = li + lb;
          if(i < heap_sz){
		printf("%d ", kv_arr[i].key);
	  }
       }
       printf("\n");
   }
}

void fill_linked_list_random(DLinkedList *plist, size_t size){
   int i;
   srand(time(NULL));
   for (i=0; i<size; ++i){
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	node->_entity.key = rand() % 1000;
	node->_entity.pdata = NULL;
	insert_list_at_head(plist, node);
   }
}

void cleanup_linked_list(DLinkedList* plist){
	ListNode *pf = LIST_FIRST(plist);
   for(pf = LIST_FIRST(plist); pf != LIST_TAIL(plist); pf = pf->next){
	free(pf);
   }
}

void print_linked_list(DLinkedList *plist, BOOLEAN reverse){

	ListNode *pf;
    printf("\n");
    if(reverse){
	printf("print reverse : \n");
     	for (pf = LIST_LAST(plist); pf != LIST_HEAD(plist); pf = pf->prev){
	   printf("%d ", pf->_entity.key);
        }
    }else{
	for (pf = LIST_FIRST(plist); pf != LIST_TAIL(plist); pf = pf->next){
	   printf("%d ", pf->_entity.key);
        }
    }
}

void print_c(size_t n, char c){
     int i=0; 
     for (;i<n; ++i){
        putchar(c);
     }
}

void get_tree_node(TreeNode* pn, DLinkedList* plist, int level){

    if (pn != NULL){

	int nextlevel = level+1;
	 ListNode* pnode = NULL;
	 DLinkedList* plevel = NULL;

	 search_list(plist, level, &pnode);
	
     if (pnode == NULL){
            // 新建一个节点
            pnode = (ListNode*)malloc(sizeof(ListNode));
	    // 在此建造一条新的list作为新level的容器。
            plevel = (DLinkedList*)malloc(sizeof(DLinkedList));
	    
 	    //printf("create and insert new level list (%d)\n", level);
	    init_list(plevel);

	    pnode->_entity.key = level;
            pnode->_entity.pdata = (void*)plevel;
	    insert_list_at_tail(plist, pnode);
    }else{
	   plevel = (DLinkedList*)pnode->_entity.pdata;
   }

         // 将树的节点放入相应的level的list中
     ListNode* ptt = (ListNode*)malloc(sizeof(ListNode));
	 ptt->_entity.key = (long)pn;
	 ptt->_entity.pdata = (void*)pn;
     insert_list_at_tail(plevel, ptt);

	 get_tree_node(pn->left, plist, nextlevel);
	 get_tree_node(pn->right, plist, nextlevel);
    }
}

char* is_what(TreeNode* pn){
	
   if (pn != NULL && pn->parent == NULL){
	return "root";
   }else if (pn != NULL && pn->parent->left == pn){
	return "left";
   }else if (pn != NULL && pn->parent->right == pn){
	return "right";
   }else{
	return "NULL";
   }
}

void print_tree(Tree* pt, size_t width){

     DLinkedList llist;
     init_list(&llist);

     get_tree_node(pt->root, &llist, 0);

     // print the tree
     ListNode *pnode = NULL;
     for (pnode = LIST_FIRST(&llist); pnode != LIST_TAIL(&llist); pnode=pnode->next){
	  DLinkedList* plevel = (DLinkedList*)pnode->_entity.pdata;
	  int level      = pnode->_entity.key;

	  ListNode* pn = NULL;
	  for (pn = LIST_FIRST(plevel); pn != LIST_TAIL(plevel); pn = pn->next){
		TreeNode* pt = (TreeNode*) pn->_entity.pdata;
		printf(" %d(l:%d p:%d %s) ", pt->_entity.key, level, pt->parent !=NULL?pt->parent->_entity.key:0, is_what(pt));
          }
	  printf("\n");
     }
     
     // clean up all the malloc data
     
     for (pnode = LIST_FIRST(&llist); pnode != LIST_TAIL(&llist); pnode=pnode->next){
	DLinkedList* plevel = (DLinkedList*)pnode->_entity.pdata;
        int level      = pnode->_entity.key;
        //printf("clean up %d level data\n", level);
	ListNode* pn = NULL;
	
	while(pop_list(plevel, &pn)){
	   
	   free(pn);
        }
	free(plevel);
	pnode->_entity.pdata = NULL;
     }
}

int get_rb_node(RBTree* prb, RBTreeNode* ptn, DLinkedList* plist, int level, int* lc){

    if (ptn != NULL){
    	
    	ListNode* pn = (ListNode*) malloc (sizeof (ListNode));
        pn->_entity.key = level;
        pn->_entity.pdata = (void*) ptn;
	
        insert_list_at_tail(plist, pn);

	if (*lc < level) *lc = level;	

        get_rb_node(prb, ptn->left, plist, level+1, lc);
        get_rb_node(prb, ptn->right, plist, level+1, lc);

    }
    return 0;
}

char* get_color(RBTreeNode* pn){
    if (pn->color == BLACK){
	return "b";
    }else{
	return "r";
    }
}

char* get_side(RBTreeNode* pn){
   if (pn->parent && pn->parent->left == pn){
	return "l";
   }else if (pn->parent && pn->parent->right == pn){
	return "r";
   }else
	return "o";
}

int print_rb_node(DLinkedList* plist, int level){
    ListNode* pf;
    int i;
    printf("\n");
    for (i=0; i<=level; ++i){
        for (pf = LIST_FIRST(plist); pf != LIST_TAIL(plist); pf = pf->next){
	     if (pf->_entity.key == i){
	    	 	 RBTreeNode* ptn = (RBTreeNode*)(pf->_entity.pdata);
	    	 	 printf("%d(p:%d,c:%s,s:%s) ", ptn->_entity.key, ptn->parent?ptn->parent->_entity.key:-1, get_color(ptn),get_side(ptn));
             }
        }
	printf("\n");
    }
    printf("\n");
    return 0;
}

int clear_up_list(DLinkedList* plist){
    ListNode* pn = NULL;
    while(pop_list(plist, &pn)){
	if (pn) free(pn);
	pn = NULL;
    } 
    return 0;
}

void print_rb_tree(RBTree* prb){
    DLinkedList list;
    init_list(&list);
    int lc = -1;
    get_rb_node(prb, prb->root, &list, 0, &lc);
    print_rb_node(&list, lc);
    clear_up_list(&list);
}


