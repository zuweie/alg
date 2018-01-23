#include <stdio.h>
#include "_entity.h"
#include "_sort.h"

extern int select_max_min(Entity arr[], size_t size, Entity** pmax, Entity** pmin){

    int i,j;
    if ((size % 2) == 0){
       // 偶数
       if (arr[0].key >= arr[1].key){
	        *pmax = &arr[0];
	        *pmin = &arr[1];
       }else{
	        *pmax = &arr[1];
	        *pmin = &arr[0];
       }
       i=2;
    }else{
       // 奇数
       *pmax = &arr[0];
       *pmin = &arr[0];
       i=1;
    }
 
    for (; i<size; i+=2){
	    if (arr[i].key < arr[i+1].key){
	        *pmin = (arr[i].key < (*pmin)->key) ? &arr[i] : *pmin;
           *pmax = (arr[i+1].key > (*pmax)->key) ? &arr[i+1] : *pmax;
        }else{
	        *pmin = (arr[i+1].key < (*pmin)->key) ? &arr[i+1] : *pmin;
	        *pmax = (arr[i].key > (*pmax)->key) ? &arr[i] : *pmax;
        }
    }
    
    return 0;
}

extern int randomized_select_imax(Entity arr[], int p, int r, int i, Entity** pret){
    if (p == r){
      *pret = &arr[p];
      return 0;
    }

    // 随机挑选一个元素arr[q]将其分开左右两部分。左小，右大。
    // 查看一下q是不是第i个元素。于是有 q-p+1 == i;
    int q = randomized_partition(arr, p, r);
    int k = q - p + 1;

    // 若 q 是第 i 个元素。即是答案。
    // 若 q 不是第 i 个元素。然后就查一查，i 在前半，还是后半部分。
    // 若在前半部分，即递归调用randomized ( arr, p, q-1, i);
    // 否则调用递归，搜查后半部分。randomized(arr, q+1, r, i-k);
    // 这里为毛要 i-k呢？ 因为 i 在后半部分。前半部分的索引值要减去。 
    if (k == i){
    	*pret = &arr[q];
		return 0;
    }else if ( i < k)
    	return randomized_select_imax(arr, p, q-1, i, pret);
    else
    	return randomized_select_imax(arr, q+1, r, i - k, pret);
}


