#ifndef __TEST_FUNCTION__
#define __TEST_FUNCTION__

#include "sqlite3.h"
#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C" {
#endif

int create_database(char* inFileName, sqlite3** outDb);

#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif


#endif
