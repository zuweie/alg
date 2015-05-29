#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "my_tool.h"
#include "kv.h"
#include "heap.h"
#include "my_list.h"

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
	insert_list(plist, node);
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
