#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <CUnit/Basic.h>

#include "kv.h"
#include "sort.h"
#include "heap.h"
#include "my_tool.h"

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
   
   int i;
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
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}


