#include "test_function.h"
#include "sqlite3.h"
#include <stddef.h> //NULL
#include "ip_allocator.h"

int create_database(char* inFileName, sqlite3** outDb){

   char *err_msg = 0;
   sqlite3_stmt *statement = NULL;


    (*outDb) = open_database(inFileName);
	if(outDb == NULL){
			  return false;
	}
   //If doesn't exist create database table
   //MAC: mac which send discovery message
   //IP: ip address which shall be assigned to host
   //ACTIVE: the ip is already assign
   //MASK, GW, DNS: configuration client
   char *sql = "DROP TABLE IF EXISTS Network;"
                "CREATE TABLE Network( MAC TEXT, IP TETXT,  MASK TEXT, GW TEXT, DNS1, DNS2, ACTIVE INT);"
                "INSERT INTO Network VALUES('b8:27:eb:8b:33:e0','192.168.25.10', '255.255.255.0', '192.168.75.1', '8.8.8.8', '4.4.4.4', 0);"
                "INSERT INTO Network VALUES('b8:27:eb:8b:33:e1','192.168.75.11', '255.255.255.0', '192.168.75.1', '8.8.8.8', '4.4.4.4', 1);"
                "INSERT INTO Network VALUES('b8:27:eb:8b:33:e2','192.168.75.12', '255.255.255.0', '192.168.75.1', '8.8.8.8', '4.4.4.4', 0);"
                "INSERT INTO Network VALUES('b8:27:eb:8b:33:e3','192.168.75.13', '255.255.255.0', '192.168.75.1', '8.8.8.8', '4.4.4.4', 1);";

   sqlite3_exec(*outDb, sql, 0, 0, &err_msg);
   sqlite3_free(err_msg);

	return true;
}
