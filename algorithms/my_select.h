#ifndef __SELECT_H__
#define __SELECT_H__

int select_max_min(kv_t arr[], size_t size, kv_t** pmax, kv_t** pmin);
int randomized_select_imax(kv_t arr[], int p, int r, int i, kv_t** pret);
#endif
