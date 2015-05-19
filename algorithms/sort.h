#ifndef __SORT_H__
#define __SORT_H__

#include "kv.h"

int insertion_sort(KV kv_arr[], size_t size);
int merge_sort(KV kv_arr[], size_t p, size_t r);
#endif
