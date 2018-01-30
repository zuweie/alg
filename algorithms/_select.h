#ifndef _SELECT_H_
#define _SELECT_H_

extern int select_max_min(Entity arr[], size_t size, Entity** pmax, Entity** pmin, ecompare compare);
extern int randomized_select_imax(Entity arr[], int p, int r, int i, Entity** pret, ecompare compare);

#endif
