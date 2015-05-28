#include <stdio.h>

#include "kv.h"

#define MAX 0x7fffffff

#define SORT_DEBUG

int insertion_sort(kv_t kv_arr[], size_t size) {
   int i, j; 
   for(j=1; j<size; ++j){
      kv_t tmp = kv_arr[j];
      i = j-1;
      while( i>=0 && kv_arr[i].key > tmp.key){
	 kv_arr[i+1] = kv_arr[i];
         i = i-1; 
      }
      kv_arr[i+1] = tmp;
   }
   return 0;
}

int merge_sort(kv_t kv_arr[], size_t s1, size_t s2){
    if (s1 < s2){
	size_t sm = (s1+s2)/2;
	merge_sort(kv_arr, s1, sm);
        merge_sort(kv_arr, sm+1, s2);
	merge(kv_arr, s1, sm, s2);
    }
}

int merge(kv_t kv_arr[], size_t s1, size_t sm, size_t s2){
   
#ifdef SORT_DEBUG
   printf("index : %d %d %d \n", (int)s1, (int)sm, (int)s2);
#endif 
   size_t i,j, k;
   size_t l_sz = sm-s1+1;
   size_t r_sz = s2-sm;
   kv_t lkv_arr[l_sz+1];
   kv_t rkv_arr[r_sz+1];
   for(i=0; i<l_sz; ++i){
	lkv_arr[i] = kv_arr[s1+i];
   }

   for (j=0; j<r_sz; ++j){
        rkv_arr[j] = kv_arr[sm+1+j];
   }

#ifdef SORT_DEBUG
   printf("原来的数组 : ");
   for(i=0; i<s2-s1+1; i++){
	printf("%d ", kv_arr[s1+i].key);
   }
   printf("\n");
   printf("分后左数组 : ");
   for(i=0; i<l_sz; ++i){
	printf("%d ", lkv_arr[i].key);
   }
   printf("分组右数组 : ");
   for(j=0; j<r_sz; ++j){
	printf("%d ", rkv_arr[j].key);
   }
   printf("\n");
#endif

   lkv_arr[l_sz].key = MAX;
   rkv_arr[r_sz].key = MAX;

   for (i=0, j=0, k=0; k<(s2-s1+1); ++k){
	if (lkv_arr[i].key < rkv_arr[j].key){
	   kv_arr[s1+k] = lkv_arr[i];
	   i++;
	}else{
	   kv_arr[s1+k] = rkv_arr[j];
	   j++;
	}
   }

#ifdef SORT_DEBUG
   printf("合拼后数组 : ");
   for(i=0; i<s2-s1+1; i++){
	printf("%d ", kv_arr[s1+i].key);
   }
   printf("\n\n");
#endif
   return 0;
}

int partition(kv_t arr[], int p, int r){

    // 将最后一个做为标杆
    int key = arr[r].key;
    int i = p-1;
    int j;
    kv_t tmp;

    // 将大于最后一个的甩在后面
    // 将小于最后一个的甩在前面。
    // 最后将最后一个和甩下的一个交换。
    // 这就完成了将一个部分序列分开两部分了。

    for (j=p; j<=r-1; ++j){
	if (arr[j].key <= key){
            if (i != j){
		++i;
	        tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp; 
	    }else{
	        ++i;
	    }    
        }
    }
    tmp = arr[i+1];
    arr[i+1] = arr[r];
    arr[r] = tmp;
    return i+1;
}

int randomized_partition(kv_t arr[], int p, int r){
   srand(time(NULL));
   int dest = r - p + 1;
   int i = ( rand() % dest ) + p;

   kv_t tmp = arr[p];
   arr[p] = arr[i];
   arr[i] = tmp;

   partition(arr, p, r);
}

int quick_sort(kv_t arr[], int p, int r, int (* partition_func)(kv_t arr[], int p, int r)){

   if (p < r){
       int q = partition_func(arr, p, r);
       quick_sort(arr, p, q-1, partition_func);
       quick_sort(arr, q+1, r, partition_func);
   }
}

