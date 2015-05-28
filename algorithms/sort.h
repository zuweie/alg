#ifndef __SORT_H__
#define __SORT_H__

#include "kv.h"

int insertion_sort(kv_t kv_arr[], size_t size);
int merge_sort(kv_t kv_arr[], size_t p, size_t r);
int quick_sort(kv_t arr[], int p, int r, int (* partition_func)(kv_t arr[], int p, int r));
int partition(kv_t arr[], int p, int r);
int randomized_partition(kv_t arr[], int p, int r);

#endif
