#include <stdio.h>
#include "_entity.h"
#include "_sort.h"

// 选最大最小的函数
extern int select_max_min(Entity arr[], size_t size, Entity** pmax, Entity** pmin, ecompare compare){

    int i,j;
    if ((size % 2) == 0){
       // 偶数
       if (compare(&arr[0], &arr[1]) >= 0){
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
        if (compare(&arr[i], &arr[i+1]) == -1){
            *pmin = (compare(&arr[i], *pmin) == -1) ? &arr[i] : *pmin;
            *pmax = (compare(&arr[i+1], *pmax) == 1) ? &arr[i+1] : *pmax;
        }else{
            *pmin = (compare(&arr[i+1], *pmin) == -1) ? &arr[i+1] : *pmin;
            *pmax = (compare(&arr[i], *pmax) ==1 ) ? &arr[i] : *pmax;
        }
    }
    
    return 0;
}

// 选择第i个大的数。
extern int randomized_select_imax(Entity arr[], int p, int r, int i, Entity** pret, ecompare compare){
    if (p == r){
      *pret = &arr[p];
      return 0;
    }

    // 随机挑选一个元素arr[q]将其分开左右两部分。左小，右大。
    // 查看一下q是不是第i个元素。于是有 q-p+1 == i;
    int q = randomized_partition(arr, p, r, compare);
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
    	return randomized_select_imax(arr, p, q-1, i, pret, compare);
    else
    	return randomized_select_imax(arr, q+1, r, i - k, pret, compare);
}


