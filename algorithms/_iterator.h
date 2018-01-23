#ifndef _ITERATOR_H_
#define _ITERATOR_H_

typedef struct _Iterator {
    struct _Iterator (*next)();
    int (*has_next)();
    
} Iterator;

#endif