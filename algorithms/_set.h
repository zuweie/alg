#ifndef _SET_H_
#define _SET_H_

#include "_entity.h"
#include "_d_linked_list.h"

typedef DLinkedList Set;
typedef ListNode SetNode;

extern int set_init(Set* );
extern int set_insert(Set* , SetNode*);
extern int set_remove(Set* , SetNode*);
extern int set_union(Set* , const Set*, const Set*);
extern int set_intersection(Set* , const Set* , const Set*);
extern int set_difference(Set* , const Set*, const Set*);
extern int set_is_member(const Set*, int key);
extern int set_is_subset(const Set*, const Set*);
extern int set_is_equal(const Set*, const Set*);

#define set_size(set) ((set)->size)

#endif