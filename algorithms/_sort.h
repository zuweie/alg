#ifndef _SORT_H_
#define _SORT_H_

#include "_entity.h"

extern int insertion_sort(Entity kv_arr[], size_t size, ecompare compare);
extern int merge_sort(Entity kv_arr[], size_t p, size_t r, ecompare compare);
extern int quick_sort(Entity arr[], int p, int r, ecompare compare, int (* partition_func)(Entity[], int, int, ecompare));
extern int partition(Entity arr[], int p, int r);
extern int randomized_partition(Entity arr[], int p, int r, ecompare);

#endif
