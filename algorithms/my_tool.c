#include <stdio.h>
#include <math.h>

#include "kv.h"
#include "heap.h"
void fill_kv_array_random(kv_t kv_arr[], size_t size){
   srand(time(NULL));
   int i;
   for (i=0; i<size; ++i){
      kv_arr[i].key = rand() % 1000;
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
