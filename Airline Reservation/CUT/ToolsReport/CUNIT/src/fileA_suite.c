#include "CUnit/Basic.h"
#include "../include/fileA.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* The suite initialization function.
 * Returns zero on success, non-zero otherwise.
 */
int init_suite_fileA(void) {
/* 
 *   if (problem during initialisation)
 *     return -1; // this number can be used to explicit the problem
 */
  return 0;
}

/* The suite cleanup function.
 * Returns zero on success, non-zero otherwise.
 */
int clean_suite_fileA(void) {
/* 
 *   if (problem during cleaning)
 *     return -1; // this number can be used to explicit the problem
 */
  return 0;
}

/* A test
 */
void testNormalValuesA(void){  
    char str1[100]="CD001|Pravesh|22/10/2022|12";
    char str2[100]="CD002|Rahul|18/11/2022|18";
    char str3[100]="CD003|Imran|13/11/2022|10";
    char str4[100]="CD004|Prakash|16/12/2022|12";
    char str5[100]="CD005|Nikhil|16/12/2022|12";
    CU_ASSERT_EQUAL(read_customer(str1),1);  
    CU_ASSERT_EQUAL(read_customer(str2), 1);  
    CU_ASSERT_EQUAL(read_customer(str3), 1);  
    CU_ASSERT_EQUAL(read_customer(str4), 1);
    CU_ASSERT_EQUAL(read_customer(str5), 1);      
}
void testErrorValuesA(void){  
   char str6[100]= "CD101|Pravesh|22/10/2022";
   char str7[100]="CD102|Riddhi|18/10|18";
   char str8[100]="CD102|Riddhi|18/10|18";
   char str9[100]="CD104|18/10|18";
   char str10[100]="18/10|18";
    CU_ASSERT_EQUAL(read_customer(str6), 0);  
    CU_ASSERT_EQUAL(read_customer(str7), 0); 
    CU_ASSERT_EQUAL(read_customer(str8), 0); 
    CU_ASSERT_EQUAL(read_customer(str9), 0); 
    CU_ASSERT_EQUAL(read_customer(str10), 0); 
}
