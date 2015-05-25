#ifndef __HEAD_H__
#define __HEAD_H__

#include "kv.h"

#define PARENT(i) ((i-1)>>1))
#define LEFT(i) ((i<<1) + 0x1)
#define RIGHT(i) ((i<<1) + 0x2)

int max_heapify(kv_t arr[], int i, size_t heap_sz);
int build_max_heap(kv_t arr[], size_t size);
int heap_sort(kv_t arr[], size_t size);

#endif
