#include <stdbool.h>

#include "dhcp_log.h"
#include "dhcp_server.h"
#include "gtest/gtest.h"
#include "ip_allocator.h"
#include "sqlite3.h"
#include "test_function.h"

// Tests factorial of negative numbers.
TEST(ip_allocator, init) {

   sqlite3 *db = NULL;
   char *err_msg = 0;
   sqlite3_stmt *statement = NULL;
	char fileName[]={"test.db"};

   //create database
   bool succ = create_database(fileName, &db);
   EXPECT_EQ(succ, true);
	if(succ==false)
			  exit(1);

   //Check the current ACTIVE flag
   int sql_ret = sqlite3_prepare(db, "SELECT COUNT(*) FROM Network WHERE ACTIVE=1",128, &statement, NULL);
   EXPECT_EQ(SQLITE_OK, sql_ret);
   if(SQLITE_OK != sql_ret){
      fprintf(stderr, "***sqlite3_prepare: get all entryes ERROR!!! %s(%d)***", err_msg,sql_ret);
      exit (1);
   }
   sqlite3_step(statement);
   int value = sqlite3_column_int(statement,0);
   sqlite3_finalize(statement);

	EXPECT_EQ(value, 2);

 	reset_database(db);

   //Check the correct replace of the 'active' flag
   sql_ret = sqlite3_prepare(db, "SELECT COUNT(*) FROM Network WHERE ACTIVE=1",128, &statement, NULL);
   EXPECT_EQ(SQLITE_OK, sql_ret);
   if(SQLITE_OK != sql_ret){
      fprintf(stderr, "***sqlite3_prepare: get all entryes ERROR!!! %s(%d)***", err_msg, sql_ret);
      exit (1);
   }
   sqlite3_step(statement);
   value = sqlite3_column_int(statement,0);
   sqlite3_finalize(statement);
   EXPECT_EQ(value, 0);

   sqlite3_close(db);
}
