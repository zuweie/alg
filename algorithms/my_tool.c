#include <stdio.h>
#include "kv.h"

void fill_kv_array_random(KV kv_arr[], size_t size){
   srand(time(NULL));
   int i;
   for (i=0; i<size; ++i){
      kv_arr[i].key = rand() % 1000;
      kv_arr[i].pdata = NULL;
   }
}

void print_kv_key(KV kv_arr[], size_t size){
   int i;
   printf("key: ");
   for (i=0; i<size; ++i){
      printf("%d ", kv_arr[i].key);
   }
   printf("\n");
}
