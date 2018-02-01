#include <stdio.h>
#include <stdlib.h>
#include "_entity.h"
#include "_sort.h"
#define MAX 0x7fffffff

#define SORT_DEBUG

extern int insertion_sort(Entity kv_arr[], size_t size, ecompare compare) {
   
   int i, j; 
   for(j=1; j<size; ++j){
	   Entity tmp = kv_arr[j];
      i = j-1;
      while( i>=0 && compare(&kv_arr[i], &tmp) == 1){
    	  kv_arr[i+1] = kv_arr[i];
          i = i-1; 
      }
      kv_arr[i+1] = tmp;
   }
   return 0;
}

extern int merge_sort(Entity kv_arr[], size_t s1, size_t s2, ecompare compare){
    if (s1 < s2){
    	size_t sm = (s1+s2)/2;
		merge_sort(kv_arr, s1, sm, compare);
        merge_sort(kv_arr, sm+1, s2, compare);
        merge(kv_arr, s1, sm, s2, compare);
    }
    return 0;
}

extern int merge(Entity kv_arr[], size_t s1, size_t sm, size_t s2, ecompare compare)
{ 
   size_t i,j, k;
   size_t l_sz = sm-s1+1;
   size_t r_sz = s2-sm;
   Entity lkv_arr[l_sz];
   Entity rkv_arr[r_sz];

   for(i=0; i<l_sz; ++i){
	lkv_arr[i] = kv_arr[s1+i];
   }

   for (j=0; j<r_sz; ++j){
    rkv_arr[j] = kv_arr[sm+1+j];
   }

   //lkv_arr[l_sz] = i2e(MAX);
   //rkv_arr[r_sz] = i2e(MAX);

   for (i=0, j=0, k=0; k<(s2-s1+1); ++k){
    if (i == l_sz) {
        kv_arr[s1+k] = rkv_arr[j];
	    j++;
    }else if (j == r_sz){
        kv_arr[s1+k] = lkv_arr[i];
	    i++;
    }else{
        if (compare(&lkv_arr[i], &rkv_arr[j]) <= 0){
	        kv_arr[s1+k] = lkv_arr[i];
	        i++;
	    }else{
	        kv_arr[s1+k] = rkv_arr[j];
	        j++;
	    }
    }

   }
   return 0;
}

extern int partition(Entity arr[], int p, int r, ecompare compare){

    // 将最后一个做为标杆
    //int key = arr[r].key;
    Entity er = arr[r];
    int i = p-1;
    int j;
    Entity tmp;

    // 将大于最后一个的甩在后面
    // 将小于最后一个的甩在前面。
    // 最后将最后一个和甩下的一个交换。
    // 这就完成了将一个部分序列分开两部分了。

    for (j=p; j<=r-1; ++j){
        if (compare(&arr[j], &er) <= 0 ){
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

extern int randomized_partition(Entity arr[], int p, int r, ecompare compare){
   srand(time(NULL));
   int dest = r - p + 1;
   int i = ( rand() % dest ) + p;

   Entity tmp = arr[p];
   arr[p] = arr[i];
   arr[i] = tmp;

   return partition(arr, p, r, compare);
}

extern int quick_sort(Entity arr[], int p, int r, ecompare compare, int (* partition_func)(Entity[], int, int, ecompare)){

   if (p < r){
       int q = partition_func(arr, p, r, compare);
       quick_sort(arr, p, q-1, compare, partition_func);
       quick_sort(arr, q+1, r, compare, partition_func);
   }
   return 0;
}

