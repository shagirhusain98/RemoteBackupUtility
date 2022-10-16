/*
 *  Simple example of a CUnit unit test.
 *  
 *  Install CUnit library with :
 *  sudo apt-get install libcunit1-dev
 * 
 *  compile with -lcunit :
 *  gcc -o fileA.tests cunit_fileA.c fileA_suite.c fileA.c -lcunit
 *
 *  the complete list of the CU_* can be found at
 *  http://cunit.sourceforge.net/doc/writing_tests.html#assertions
 */

/* use the basic interface */
#include "CUnit/Basic.h"

/* the file to test */
#include "../include/fileA.h"
/* the suite to test */
#include "../include/fileA_suite.h"
#include "../include/fileB.h"
#include "../include/fileB_suite.h"
#include "../include/fileC.h"
#include "../include/fileC_suite.h"

/* The main() function for setting up and running the tests.
 * Returns a CUE_SUCCESS on successful running, another
 * CUnit error code on failure.
 */
int main() {
  CU_pSuite pSuite1 = NULL;
 

  /* initialize the CUnit test registry */
  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  /* add a suite to the registry */
  pSuite1 = CU_add_suite("Suite fileA", init_suite_fileA, clean_suite_fileA);
  if (NULL == pSuite1) {
    CU_cleanup_registry();
    return CU_get_error();
  }
  CU_pSuite pSuite2 = NULL;

  /* add a suite to the registry */
  pSuite2 = CU_add_suite("Suite fileB", init_suite_fileB, clean_suite_fileB);
  if (NULL == pSuite2) {
    CU_cleanup_registry();
    return CU_get_error();
  }
  CU_pSuite pSuite3 = NULL;

  /* add a suite to the registry */
  pSuite3 = CU_add_suite("Suite fileC", init_suite_fileC, clean_suite_fileC);
  if (NULL == pSuite3) {
    CU_cleanup_registry();
    return CU_get_error();
  }
  /* add the tests to the suite */
  /* all the functions in fileB_suite.h must be added */
  if ((NULL == CU_add_test(pSuite1,
          "test of read_customer() in classic cases", testNormalValuesA)) ||
     (NULL == CU_add_test(pSuite1,
          "test of read_customer() in pathologic cases", testErrorValuesA))) {
    CU_cleanup_registry();
    return CU_get_error();
  }
  if ((NULL == CU_add_test(pSuite2,
          "test of flight_data() in classic cases", testNormalValuesB)) ||
     (NULL == CU_add_test(pSuite2,
          "test of flight_data() in pathologic cases", testErrorValuesB))) {
    CU_cleanup_registry();
    return CU_get_error();
  }
  if ((NULL == CU_add_test(pSuite3,
          "test of allocate_tickets() in classic cases", testNormalValuesC)) ||
     (NULL == CU_add_test(pSuite3,
          "test of allocate_tickets() in pathologic cases", testErrorValuesC))) {
    CU_cleanup_registry();
    return CU_get_error();
  }
  /* Run all tests using the CUnit Basic interface */
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}

