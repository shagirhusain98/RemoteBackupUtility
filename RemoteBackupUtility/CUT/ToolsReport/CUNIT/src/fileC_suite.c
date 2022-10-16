#include "CUnit/Basic.h"
#include "../include/fileC.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* The suite initialization function.
 * Returns zero on success, non-zero otherwise.
 */
int init_suite_fileC(void) {
/* 
 *   if (problem during initialisation)
 *     return -1; // this number can be used to explicit the problem
 */
  return 0;
}

/* The suite cleanup function.
 * Returns zero on success, non-zero otherwise.
 */
int clean_suite_fileC(void) {
/* 
 *   if (problem during cleaning)
 *     return -1; // this number can be used to explicit the problem
 */
  return 0;
}

/* A test
 */

void testNormalValuesC(void){ 
    char str1[100] = "Indigo Airlines";
    char str2[100] = "Jet Airlines";
    char str3[100] = "Vistara Airlines";
    char str4[100] = "Vistara Airlines";
    char str5[100] = "American Airlines";
    CU_ASSERT_EQUAL(allocate_tickets(str1,50),1);  
    CU_ASSERT_EQUAL(allocate_tickets(str2,120), 1);  
    CU_ASSERT_EQUAL(allocate_tickets(str3,10), 1);  
    CU_ASSERT_EQUAL(allocate_tickets(str4,70), 1);  
    CU_ASSERT_EQUAL(allocate_tickets(str5,40), 1);  
}
/* Another test
 */
void testErrorValuesC(void){ 
    char str6[100] = "Indigo Airlines";
    char str7[100] = "Jot Flights";
    char str8[100] = "Vistara Airlines";
    char str9[100] = "Vasista Airlines";
    char str10[100] = "American Airlines";
    CU_ASSERT_EQUAL(allocate_tickets(str6,150), 0);  
    CU_ASSERT_EQUAL(allocate_tickets(str7,10), 0); 
    CU_ASSERT_EQUAL(allocate_tickets(str8,-1), 0); 
    CU_ASSERT_EQUAL(allocate_tickets(str9,150), 0); 
    CU_ASSERT_EQUAL(allocate_tickets(str10,-3), 0); 
}
    
