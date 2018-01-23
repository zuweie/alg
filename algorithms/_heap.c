#include <stdio.h>
#include "_entity.h"
#include "_heap.h"


//这里要紧记一个原则。就是保证头头是最大的，其他的一切都无所谓。即使有叶子，比上一级的另一族的头大，都无所谓。
// 这里的过程是自上而下的。
// 在i个元素开始检查。若有子比其则换。

extern int max_heapify(Entity arr[], int i, size_t heap_sz){

    int l = LEFT(i);
    int r = RIGHT(i);
    int largest = -1;

    // 不管左或右，那个子大，就跟那个子换。保证坐在头头的是最大的。
    if (l < heap_sz && arr[l].key > arr[i].key)
       largest = l;
    else
       largest = i;
   
    if (r < heap_sz && arr[r].key > arr[largest].key)
	largest = r;
    
    if (largest >=0 && largest != i){
    	Entity tmp =  arr[i];
        arr[i] = arr[largest];
	arr[largest] = tmp;
        max_heapify(arr, largest, heap_sz);
    }
 
    return 0;
}

extern int build_max_heap(Entity arr[], size_t size){
   int i = size/2 -1;
   for (;i>=0; --i){
	max_heapify(arr, i, size);
   }
   return 0;
}
 
extern int heap_sort(Entity arr[], size_t size){
    build_max_heap(arr, size);
    int i;
    Entity tmp;
    size_t heap_sz = size;
    for(i=size-1; i>=1; --i){
        // 这里交换第一个和最后一个，即将最大的那个放在最后面。
        // 然后将heap的size 减一，再调用max_heapify,重新将最大的调到一个的位置。但不包括最后的那个。（因为headSZ 减一了）.
    	tmp = arr[0];
        arr[0] = arr[i];
        arr[i] = tmp;
	    max_heapify(arr, 0, --heap_sz);
    }
    return 0;
}


