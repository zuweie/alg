#ifndef  _SORT_H_
#define _SORT_H_

#include "_entity.h"

extern int insertion_sort(Entity kv_arr[], size_t size);
extern int merge_sort(Entity kv_arr[], size_t p, size_t r);
extern int quick_sort(Entity arr[], int p, int r, int (* partition_func)(Entity arr[], int p, int r));
extern int partition(Entity arr[], int p, int r);
extern int randomized_partition(Entity arr[], int p, int r);

#endif
