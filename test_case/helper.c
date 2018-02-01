#include <stdio.h>
#include "_entity.h"
#include "helper.h"


char* g_strings[20] = {
        "hello;",
        "who i am;",
        "what the fuck you;",
        "what the hell are you doing;",
        "I don`t know what the hell you are;", 
        "iiiiii;",
        "abceddd;",
        "sefhigkd;",
        "kkkkkwwww;",
        "what the fckekck;",
        "uuuussskkk;",
        "eeeeeeee;",
        "jjjjbbbb;",
        "suck my dick;",
        "nice come on;",
        "cao;",
        "***()***;",
        "&&&)()();",
        "!!!uuuiii;",
        "bbbbby;"
    };

/*
char* g_strings[20] = {

        "t;",
        "e;", 
        "s;",
        "l;",
        "f;",
        "m;",
        "n;",
        "o;",
        "p;",
        "q;",
        "r;",
        "g;",
        "h;",
        "i;",
        "j;",
        "k;",
        "a;",
        "b;",
        "c;",
        "d;"
    };
    */
extern void init_ie_arr(Entity _arr[], size_t size) 
{
    int i=0;
    for (;i<size; ++i) {
        _arr[i]._data.ie = rand() % 100000;
        _arr[i]._vtype = EINT;
    }
};

extern void init_fe_arr (Entity _arr[], size_t size) {
    int i=0;
    for (; i<size; ++i) {
        _arr[i]._data.fe =  (float)(rand() % 100000) / 0.7;
        _arr[i]._vtype = EFLOAT;
    }
}

extern void init_strings_arr(Entity _arr[], size_t size) {
    int i=0;
    char** strings = g_strings;
    for (; i<size; ++i) {
        int string_index =  rand() % 20;
        _arr[i]._data.string =  strings[string_index];
        _arr[i]._vtype = ESTRING;
    }
}

extern void print_entity(Entity* e) 
{
    switch (e->_vtype) {
        case EINT:
            printf("%d", e->_data.ie);
        break;
        case EFLOAT:
            printf("%f", e->_data.fe);
        break;
        case ESTRING:
            printf("%s", e->_data.string);
        break;
        case EPOINTER:
            printf("%p", e->_data.pointer);
        break;
    }
}

extern void print_entity_arr(Entity kv_arr[], size_t size){
   int i;
   printf("\nentity: ");
   for (i=0; i<size; ++i){
      print_entity(&kv_arr[i]);
      printf(" ");
   }
   printf("\n");
}

extern void print_heap(Entity kv_arr[], size_t heap_sz)
{

    int h = log2(heap_sz);
    int hi, lb, li, lsz;
    printf("\n");
    for (hi = 0; hi < h; ++hi)
    {
        lb = pow(2, hi) - 1;
        lsz = pow(2, hi);
        for (li = 0; li < lsz; ++li)
        {
            int i = li + lb;
            if (i < heap_sz)
            {
                print_entity(&kv_arr[i]);
                printf(" ");
            }
        }
        printf("\n");
    }
}

extern void fill_linked_list_random(DLinkedList* plist, Entity _arr[], int arr_size){
    int i;
    for (i=0; i<arr_size; ++i){
	    dlist_push(plist, _arr[i]);
   }
}

extern void print_linked_list(DLinkedList *plist, BOOLEAN reverse){

    ListNode *pf;
    printf("\n");
    if(reverse){
	    printf("print reverse : \n");
     	for (pf = LIST_LAST(plist); pf != LIST_HEAD(plist); pf = pf->prev){
            print_entity(&(pf->_entity));
        }
    }else{
	    for (pf = LIST_FIRST(plist); pf != LIST_TAIL(plist); pf = pf->next){
            print_entity(&(pf->_entity));

        }
    }
}

extern int cleanup_listnode(Entity* e){
    printf("clean up node ");
    print_entity(e);
    printf("\n");
}
