#ifndef FILEB_SUITE_H_
#define FILEB_SUITE_H_

#include "CUnit/Basic.h"

#include "fileB.h"

int init_suite_fileB(void);

int clean_suite_fileB(void);

void testNormalValuesB(void);

void testErrorValuesB(void);

#endif  /* FILEB_SUITE_H_ */
