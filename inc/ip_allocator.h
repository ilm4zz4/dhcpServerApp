#ifndef __IP_ALLOCATOR_H__
#define __IP_ALLOCATOR_H__
#include "sqlite3.h"

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C" {
#endif

  int reset_database(sqlite3 *db);
  sqlite3* open_database(char* fileName);
  bool close_database(sqlite3* db);
  int read_configFile(char *config_file);

#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif



#endif
