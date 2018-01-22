#ifndef __HEAD_H__
#define __HEAD_H__

#include "_entity.h"

#define PARENT(i) ((i-1)>>1))
#define LEFT(i) ((i<<1) + 0x1)
#define RIGHT(i) ((i<<1) + 0x2)

extern int max_heapify(Entity arr[], int i, size_t heap_sz);
extern int build_max_heap(Entity arr[], size_t size);
extern int heap_sort(Entity arr[], size_t size);

#endif
