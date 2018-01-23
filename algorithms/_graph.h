#ifndef _GRAPH_H_
#define _GRAPH_H_
#include <stdlib.h>
#include "_d_linked_list.h"

typedef struct _Graph 
{
    size_t v_count;
    size_t e_count;

    int (*match)(const void * key1, const void * key2);
    int (*destroy)(void * data);
    
    DLinkedList adjlists;

} Graph;

#endif