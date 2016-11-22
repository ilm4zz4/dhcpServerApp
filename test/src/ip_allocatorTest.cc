#include <stdbool.h>

#include "dhcp_log.h"
#include "dhcp_server.h"
#include "gtest/gtest.h"
#include "ip_allocator.h"
#include "sqlite3.h"

// Tests factorial of negative numbers.
TEST(ip_allocator, init) {

   sqlite3 *db = NULL;
   char *err_msg = 0;
   sqlite3_stmt *statement = NULL;
	char fileName[]={"test.db"};

   //create database
   bool succ = create_database(fileName);
   EXPECT_EQ(succ, true);
	if(succ==false)
			  exit(1);

   //Fill databese
   int sql_ret = sqlite3_open(fileName, &db);
   if(SQLITE_OK != sql_ret)
   {
      ERROR("***sqlite3_open ERROR!!! %s(%d)***", sqlite3_errmsg(db), sql_ret);
      exit (1);
   }

   //If doesn't exist create database table
   //MAC: mac which send discovery message
   //IP: ip address which shall be assigned to host
   //ACTIVE: the ip is already assign
   //MASK, GW, DNS: configuration client

   char *sql ="";//"INSERT INTO Network VALUES( 'b8:27:eb:8b:33:e7', '192.168.0.1', '255.255.255.0', '192.169.75.1', '8.8.8.8', 0);"
              //"INSERT INTO Network VALUES( 'b8:27:eb:8b:33:e5', '192.168.0.1', '255.255.255.0', '192.169.75.1', '8.8.8.8', 0);";
   sql_ret = sqlite3_exec(db, sql, 0, 0, &err_msg);
   EXPECT_EQ(sql_ret, SQLITE_OK );
   if (sql_ret != SQLITE_OK ) {

      sqlite3_free(err_msg);
      sqlite3_close(db);
      exit (1);
   }

   //Check the current ACTIVE flag
   sql_ret = sqlite3_prepare(db, "SELECT COUNT(*) FROM Network WHERE ACTIVE=1",128, &statement, NULL);
   EXPECT_EQ(SQLITE_OK, sql_ret);
   if(SQLITE_OK != sql_ret){
      fprintf(stderr, "***sqlite3_prepare: get all entryes ERROR!!! %s(%d)***", err_msg,sql_ret);
      exit (1);
   }
   sqlite3_step(statement);
   int value = sqlite3_column_int(statement,0);
   sqlite3_finalize(statement);

	EXPECT_EQ(value, 4);

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
