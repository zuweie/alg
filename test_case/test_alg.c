#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <CUnit/Basic.h>

#include "kv.h"
#include "sort.h"
#include "heap.h"
#include "my_tool.h"
#include "my_select.h"
#include "my_list.h"
#include "my_hash.h"

kv_t* pkv_arr;
size_t arr_size;

void test_insertion_sort(void){
   // TODO : make a kv array
   int i;
   const size_t SIZE = 10;
   kv_t kv_arr[SIZE];
   fill_kv_array_random(kv_arr, SIZE);
   
   printf("sort before:\n");
   print_kv_key(kv_arr, SIZE);

   // TODO : sort the array
   insertion_sort(kv_arr, SIZE);

   for(i=1; i<SIZE; ++i){
      CU_ASSERT(kv_arr[i].key > kv_arr[i-1].key);
   }
   
   printf("sort after:\n");
   print_kv_key(kv_arr, SIZE);
}

void test_merge_sort(void){
  int i;
  const size_t SIZE = 6;
  kv_t kv_arr[SIZE];
  fill_kv_array_random(kv_arr, SIZE);
  print_kv_key(kv_arr, SIZE);
  merge_sort(kv_arr, 0, SIZE-1);
  for(i=1; i<SIZE; ++i){
     CU_ASSERT(kv_arr[i].key > kv_arr[i-1].key);
  }
  print_kv_key(kv_arr, SIZE);
}

void test_build_heap(void) {
   int i;
   const size_t SIZE = 100;
   kv_t kv_arr[SIZE];
   fill_kv_array_random(kv_arr, SIZE);
   //print_kv_key(kv_arr, SIZE);
   print_heap(kv_arr, SIZE);
   build_max_heap(kv_arr, SIZE);
   //print_kv_key(kv_arr, SIZE);
   print_heap(kv_arr, SIZE);
}

void test_heap_sort(void) {
   const size_t SIZE = 50;
   kv_t kv_arr[SIZE];
   
   fill_kv_array_random(kv_arr, SIZE);
   print_kv_key(kv_arr, SIZE);
   heap_sort(kv_arr, SIZE);
   int i;
   for(i=1; i<SIZE; ++i){
	CU_ASSERT(kv_arr[i].key >= kv_arr[i-1].key);
   } 
   print_kv_key(kv_arr, SIZE);
}

void test_quick_sort(void){

   //const size_t SIZE = 10;
   //kv_t kv_arr[SIZE];
 
   //fill_kv_array_random(kv_arr, SIZE);
   print_kv_key(pkv_arr, arr_size);
   quick_sort(pkv_arr, 0, arr_size-1, partition);
   print_kv_key(pkv_arr, arr_size);
   
   // ASSERT 
   int i;
   for (i=1; i<arr_size; ++i){
	CU_ASSERT(pkv_arr[i].key >= pkv_arr[i-1].key);
   }
}

void test_random_quick_sort(void){
 
  print_kv_key(pkv_arr, arr_size);
  quick_sort(pkv_arr, 0, arr_size-1, randomized_partition);
  print_kv_key(pkv_arr, arr_size);  
 
}

void test_select_max_min(void){
  print_kv_key(pkv_arr, arr_size);
  quick_sort(pkv_arr, 0, arr_size-1, randomized_partition);
  print_kv_key(pkv_arr, arr_size);
  kv_t *pmax, *pmin;
  select_max_min(pkv_arr, arr_size, &pmax, &pmin);
  printf("max : %d, min : %d \n", pmax->key, pmin->key);
}

void test_randomized_select_imax(void){
  
   print_kv_key(pkv_arr, arr_size);
  
   kv_t *p;
   randomized_select_imax(pkv_arr, 0, arr_size-1, 4, &p);

   printf("imax : %d\n", p->key);

   quick_sort(pkv_arr, 0, arr_size-1, randomized_partition);
   print_kv_key(pkv_arr, arr_size);

}

void test_linked_list(void) {
   list_t list;
   init_list(&list);
   
   fill_linked_list_random(&list, arr_size);

   print_linked_list(&list, FALSE);
   print_linked_list(&list, TRUE);

   node_t* pn;
   get_node(&list, 4, &pn);
   printf("\nwe get 4th node : %d \n", pn->kv.key);
 
   get_node(&list, 6, &pn);
   printf("we get 6th node : %d \n", pn->kv.key);

   int k = pn->kv.key;

   delete_list(&list, k, &pn);

   printf("delete 6th node : %d \n", pn->kv.key);
   print_linked_list(&list, FALSE);
   free(pn);
   cleanup_linked_list(&list);
}

void test_hash_key(void){
    int key = hash_key(123456);
    printf("key is : %d \n", key);
}

int suite_success_init(void){
    return 0;
}

int suite_success_clean(void){
   return 0;
}

BOOLEAN grep_case(int argc, char* argv[], char* _case){
   int i;
   for(i=0; i<argc; ++i){
	if (strcmp(argv[i], _case) ==0)
	   return TRUE;
   }
   return FALSE;
} 

int main( int argc, char* argv[] ){

   arr_size = atoi(argv[2]);
   if (arr_size <= 0){
	return -1;
   }   

   //弄些实验数据
   pkv_arr = malloc(sizeof(kv_t) * arr_size);
   fill_kv_array_random(pkv_arr, arr_size);
    
   CU_pSuite pSuite = NULL;
  
   if (CUE_SUCCESS != CU_initialize_registry()){
	return CU_get_error();
   }

   pSuite = CU_add_suite("test_alg_suite", suite_success_init, suite_success_clean);

   if (NULL == pSuite){
      CU_cleanup_registry();
      return CU_get_error();
   }

   if (grep_case(argc, argv, "insertion_sort") 
   && (NULL == CU_add_test(pSuite, "test_insertion_sort", test_insertion_sort))){
      CU_cleanup_registry();
      return CU_get_error();
   }

   if (grep_case(argc, argv, "merge_sort")
   && (NULL == CU_add_test(pSuite, "test_merge_sort", test_merge_sort))){
       CU_cleanup_registry();
       return CU_get_error();
   }

   if (grep_case(argc, argv, "build_heap")
   && (NULL == CU_add_test(pSuite, "test_build_heap", test_build_heap))){
	CU_cleanup_registry();
        return CU_get_error();
   }

   if (grep_case(argc, argv, "heap_sort")
   && (NULL == CU_add_test(pSuite, "heap_sort", test_heap_sort))){
	CU_cleanup_registry();
	return CU_get_error();
   }

   if (grep_case(argc, argv, "quick_sort")
   && (NULL == CU_add_test(pSuite, "test_quick_sort", test_quick_sort))){
	CU_cleanup_registry();
        return CU_get_error();
   }

   if (grep_case(argc, argv, "random_quick_sort")
   && (NULL == CU_add_test(pSuite, "test_randowm_quick_sort", test_random_quick_sort))){
	CU_cleanup_registry();
        return CU_get_error();
   }

   if (grep_case(argc, argv, "select_max_min")
   && (NULL == CU_add_test(pSuite, "test_max_min", test_select_max_min))){
	CU_cleanup_registry();
	return CU_get_error();
   }

   if (grep_case(argc, argv, "select_imax")
   && (NULL == CU_add_test(pSuite, "test_select_imax", test_randomized_select_imax))){
	CU_cleanup_registry();
	return CU_get_error();
   }

   if (grep_case(argc, argv, "linked_list")
   && (NULL == CU_add_test(pSuite, "test_linked_list", test_linked_list))){
	CU_cleanup_registry();
        return CU_get_error();
   }

   if (grep_case(argc, argv, "hash_key")
   && (NULL == CU_add_test(pSuite, "test_hash_key", test_hash_key))){
	CU_cleanup_registry();
	return CU_get_error();
   }

  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  free(pkv_arr);
  return CU_get_error();
}


