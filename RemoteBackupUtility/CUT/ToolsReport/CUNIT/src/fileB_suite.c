#include "CUnit/Basic.h"
#include "../include/fileB.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* The suite initialization function.
 * Returns zero on success, non-zero otherwise.
 */
int init_suite_fileB(void) {
/* 
 *   if (problem during initialisation)
 *     return -1; // this number can be used to explicit the problem
 */
  return 0;
}

/* The suite cleanup function.
 * Returns zero on success, non-zero otherwise.
 */
int clean_suite_fileB(void) {
/* 
 *   if (problem during cleaning)
 *     return -1; // this number can be used to explicit the problem
 */
  return 0;
}

/* A test
 */

void testNormalValuesB(void){ 
    char str1[100] =  "FL001|Indigo Airlines|02/10/2022|120";
    char str2[100] = "FL002|Jet Airlines|28/12/2022|120";
    char str3[100] = "FL003|Vistara Airlines|13/11/2022|150";
    char str4[100] = "FL004|Vistara Airlines|16/12/2022|120";
    char str5[100] = "FL005|Air Asia Airlines|16/12/2022|120";
    CU_ASSERT_EQUAL(flight_data(str1),1);  
    CU_ASSERT_EQUAL(flight_data(str2), 1);  
    CU_ASSERT_EQUAL(flight_data(str3), 1);  
    CU_ASSERT_EQUAL(flight_data(str4), 1);  
    CU_ASSERT_EQUAL(flight_data(str5), 1);  
 
    
}
/* Another test
 */
void testErrorValuesB(void){ 
    char str6[100] = "FL001|Indigo Airlines|22/10/2022";
    char str7[100] ="FL004|Vistara Airlines|18/10|180";
    char str8[100] ="FL005|18/10/2022|180";
    char str9[100] ="FL006|18/10/2022";
    char str10[100] ="18/10/2022|180";
    CU_ASSERT_EQUAL(flight_data(str6), 0);  
    CU_ASSERT_EQUAL(flight_data(str7), 0); 
    CU_ASSERT_EQUAL(flight_data(str8), 0); 
    CU_ASSERT_EQUAL(flight_data(str9), 0); 
    CU_ASSERT_EQUAL(flight_data(str10), 0); 
}
    
