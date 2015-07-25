#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>


#include "kv.h"
#include "heap.h"
#include "my_tree.h"
#include "my_list.h"
#include "my_tool.h"
#include "my_rbtree.h"

void fill_kv_array_random(kv_t kv_arr[], size_t size){
   srand(time(NULL));
   int i;
   for (i=0; i<size; ++i){
      kv_arr[i].key = rand() % 10000;
      kv_arr[i].pdata = NULL;
   }
}

void print_kv_key(kv_t kv_arr[], size_t size){
   int i;
   printf("\nkey: ");
   for (i=0; i<size; ++i){
      printf("%d ", kv_arr[i].key);
   }
   printf("\n");
}

void print_heap(kv_t kv_arr[], size_t heap_sz){

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

void fill_linked_list_random(list_t *plist, size_t size){
   int i;
   srand(time(NULL));
   for (i=0; i<size; ++i){
	node_t* node = (node_t*)malloc(sizeof(node_t));
	node->kv.key = rand() % 1000;
	node->kv.pdata = NULL;
	insert_list_at_head(plist, node);
   }
}

void cleanup_linked_list(list_t* plist){
   node_t *pf = LIST_FIRST(plist);
   for(pf = LIST_FIRST(plist); pf != LIST_TAIL(plist); pf = pf->next){
	free(pf);
   }
}
void print_linked_list(list_t *plist, BOOLEAN reverse){

    node_t *pf;
    printf("\n");
    if(reverse){
	printf("print reverse : \n");
     	for (pf = LIST_LAST(plist); pf != LIST_HEAD(plist); pf = pf->prev){
	   printf("%d ", pf->kv.key);
        }
    }else{
	for (pf = LIST_FIRST(plist); pf != LIST_TAIL(plist); pf = pf->next){
	   printf("%d ", pf->kv.key);
        }
    }
}


void print_c(size_t n, char c){
     int i=0; 
     for (;i<n; ++i){
        putchar(c);
     }
}

void get_tree_node(tnode_t* pn, list_t* plist, int level){

    if (pn != NULL){

	int nextlevel = level+1;
	 node_t* pnode = NULL;
	 list_t* plevel = NULL;

	 search_list(plist, level, &pnode);
	
         if (pnode == NULL){
            // 新建一个节点
            pnode = (node_t*)malloc(sizeof(node_t));
	    // 在此建造一条新的list作为新level的容器。
            plevel = (list_t*)malloc(sizeof(list_t));
	    
 	    //printf("create and insert new level list (%d)\n", level);
	    init_list(plevel);

	    pnode->kv.key = level;
            pnode->kv.pdata = (void*)plevel;
	    insert_list_at_tail(plist, pnode);
         }else{
	   plevel = (list_t*)pnode->kv.pdata;
         }

         // 将树的节点放入相应的level的list中
         node_t* ptt = (node_t*)malloc(sizeof(node_t));
	 ptt->kv.key = (long)pn;
	 ptt->kv.pdata = (void*)pn;
         insert_list_at_tail(plevel, ptt); 

	 get_tree_node(pn->left, plist, nextlevel);
	 get_tree_node(pn->right, plist, nextlevel);
    }
}

char* is_what(tnode_t* pn){
	
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

void print_tree(tree_t* pt, size_t width){

     list_t llist;
     init_list(&llist);

     get_tree_node(pt->root, &llist, 0);

     // print the tree
     node_t *pnode = NULL;
     for (pnode = LIST_FIRST(&llist); pnode != LIST_TAIL(&llist); pnode=pnode->next){
	  list_t* plevel = (list_t*)pnode->kv.pdata;
	  int level      = pnode->kv.key;

	  node_t* pn = NULL;
	  for (pn = LIST_FIRST(plevel); pn != LIST_TAIL(plevel); pn = pn->next){
		tnode_t* pt = (tnode_t*) pn->kv.pdata;
		printf(" %d(l:%d p:%d %s) ", pt->kv.key, level, pt->parent !=NULL?pt->parent->kv.key:0, is_what(pt));
          }
	  printf("\n");
     }
     
     // clean up all the malloc data
     
     for (pnode = LIST_FIRST(&llist); pnode != LIST_TAIL(&llist); pnode=pnode->next){
	list_t* plevel = (list_t*)pnode->kv.pdata;
        int level      = pnode->kv.key;
        //printf("clean up %d level data\n", level);
	node_t* pn = NULL;
	
	while(pop_list(plevel, &pn)){
	   
	   free(pn);
        }
	free(plevel);
	pnode->kv.pdata = NULL;
     }
}

int get_rb_node(rbtree_t* prb, rbnode_t* ptn, list_t* plist, int level, int* lc){

    if (ptn != NULL){
    	
	node_t* pn = (node_t*) malloc (sizeof (node_t));
        pn->kv.key = level;
        pn->kv.pdata = (void*) ptn;
	
        insert_list_at_tail(plist, pn);

	if (*lc < level) *lc = level;	

        get_rb_node(prb, ptn->left, plist, level+1, lc);
	get_rb_node(prb, ptn->right, plist, level+1, lc);

    }
    return 0;
}

char* get_color(rbnode_t* pn){
    if (pn->color == BLACK){
	return "b";
    }else{
	return "r";
    }
}

char* get_side(rbnode_t* pn){
   if (pn->parent && pn->parent->left == pn){
	return "l";
   }else if (pn->parent && pn->parent->right == pn){
	return "r";
   }else
	return "o";
}

int print_rb_node(list_t* plist, int level){
    node_t* pf;
    int i;
    printf("\n");
    for (i=0; i<=level; ++i){
        for (pf = LIST_FIRST(plist); pf != LIST_TAIL(plist); pf = pf->next){
	     if (pf->kv.key == i){
		rbnode_t* ptn = (rbnode_t*)(pf->kv.pdata);
		printf("%d(p:%d,c:%s,s:%s) ", ptn->kv.key, ptn->parent?ptn->parent->kv.key:-1, get_color(ptn),get_side(ptn)); 
             }
        }
	printf("\n");
    }
    printf("\n");
}

int clear_up_list(list_t* plist){
    node_t* pn = NULL;
    while(pop_list(plist, &pn)){
	if (pn) free(pn);
	pn = NULL;
    } 
    return 0;
}

void print_rb_tree(rbtree_t* prb){
    list_t list;
    init_list(&list);
    int lc = -1;
    get_rb_node(prb, prb->root, &list, 0, &lc);
    print_rb_node(&list, lc);
    clear_up_list(&list);
}


