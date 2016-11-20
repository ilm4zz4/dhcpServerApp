#ifndef __IP_ALLOCATOR_H__
#define __IP_ALLOCATOR_H__
#include "sqlite3.h"
#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C" {
#endif

	#ifdef TEST
		int reset_database(sqlite3* db);
	#endif
	
	int create_database(char* fileName);

#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif



#endif
