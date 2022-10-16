#ifndef FILEC_SUITE_H_
#define FILEC_SUITE_H_

#include "CUnit/Basic.h"

#include "fileC.h"

int init_suite_fileC(void);

int clean_suite_fileC(void);

void testNormalValuesC(void);

void testErrorValuesC(void);

#endif  /* FILEC_SUITE_H_ */
