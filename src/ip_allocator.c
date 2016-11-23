#include<stdio.h>
#include <stdbool.h>
#include<string.h>
#include<stdint.h>

#include"sqlite3.h"
#include "dhcp_log.h"
#include "dhcp_server.h"
#include "ip_allocator.h"
extern struct server_config gobal_config;

sqlite3* open_database(char* fileName){

   sqlite3 *db = NULL;
   char *err_msg = 0;

   int ret = sqlite3_open(fileName, &db);
   if(SQLITE_OK != ret)
   {
      ERROR("***sqlite3_open ERROR!!! %s(%d)***", sqlite3_errmsg(db), ret);
     return NULL;
   }
   return db;
}

bool close_database(sqlite3* db){

   int rc = sqlite3_close(db);

   if (rc != SQLITE_OK ) {
      return false;
   }
	return true;
}
int reset_database(sqlite3 *db){

	char* err_msg = 0;
	int ret = 0;

	//Deactivation all ip address
   sqlite3_stmt *statement = NULL;

   ret = sqlite3_prepare(db, "UPDATE Network SET ACTIVE=0 WHERE ACTIVE=1 ;",128, &statement, NULL);
   if(SQLITE_OK != ret){
        fprintf(stderr, "***sqlite3_prepare: error database !!! %s(%d)***", err_msg, ret);
    	return false;
   }
	sqlite3_step(statement);
	sqlite3_finalize(statement);

	return true;

}

int create_database(char* fileName){

   char *err_msg = 0;
   sqlite3_stmt *statement = NULL;


   sqlite3 *db = open_database(fileName);
	if(db == NULL){
			  return false;
	}
   //If doesn't exist create database table
   //MAC: mac which send discovery message
   //IP: ip address which shall be assigned to host
   //ACTIVE: the ip is already assign
   //MASK, GW, DNS: configuration client
   char *sql = "DROP TABLE IF EXISTS Network;"
                "CREATE TABLE Network( MAC TEXT, IP TETXT,  MASK TEXT, GW TEXT, DNS, ACTIVE INT);"
                "INSERT INTO Network VALUES('b8:27:eb:8b:33:e0','192.168.75.12', '255.255.255.0', '192.168.75.1', '8.8.8.8', 0);"
                "INSERT INTO Network VALUES('b8:27:eb:8b:33:e1','192.168.75.12', '255.255.255.0', '192.168.75.1', '8.8.8.8', 0);";

   int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
   sqlite3_free(err_msg);

	if(reset_database(db) != true){
    ERROR("*** reset_database ERROR!!!");
		return false;
	}
	if (close_database(db) != true ){
    ERROR("*** reset_database ERROR!!!");
		return false;
  }

	return true;
}

int sqlite_ip_allocator(char* dbName, struct network_config *config)
{

if(dbName == NULL || config == NULL){
  ERROR("db: %#010x, config: %#010x", dbName, config);
  return -1;
}

	sqlite3* db = open_database(dbName);
  fprintf(stderr,"\nDB name: %s\n",dbName);
   sqlite3_stmt* statement = NULL;
	char query[128];
	memset(query,0,sizeof(query));

	sprintf(query,"SELECT * FROM Network WHERE MAC = '%02x:%02x:%02x:%02x:%02x:%02x'" ,
              ((config->hardware_address[0])&(0xFF)),
              ((config->hardware_address[1])&(0xFF)),
              ((config->hardware_address[2])&(0xFF)),
              ((config->hardware_address[3])&(0xFF)),
              ((config->hardware_address[4])&(0xFF)),
              ((config->hardware_address[5])&(0xFF)));
	fprintf(stderr,"\n%s\n",query);
   int ret = sqlite3_prepare(db, query, 128, &statement, NULL);
   if(SQLITE_OK != ret){
    printf("Error prepare\n");
    return -1;
   }
   ret =sqlite3_step(statement);
   if(ret != SQLITE_ROW){
     return -1;
   }

	 char asc_gateway[16] = {0};
	char asc_netmask[16] = {0};
   char asc_dns1[16] = {0};
	char asc_dns2[16] = {0};
	char asc_ip_address[16] = {0};


   strncpy(asc_ip_address, sqlite3_column_text(statement,1), 16);
   strncpy(asc_netmask, sqlite3_column_text(statement,2), 16);
	strncpy(asc_gateway, sqlite3_column_text(statement,3), 16);
	strncpy(asc_dns1, sqlite3_column_text(statement,4), 16);
   strncpy(asc_dns2, sqlite3_column_text(statement,4), 16);

   sqlite3_finalize(statement);
	close_database(db);

	INFO("gateway=%s, netmask=%s, dns1=%s, dns2=%s, ip=%s", asc_gateway, asc_netmask, asc_dns1, asc_dns2, asc_ip_address);

	DEBUG("mac address=%02x:%02x:%02x:%02x:%02x:%02x, \
	       integer value=%ld", \
	       (uint8_t)config->hardware_address[0], \
               (uint8_t)config->hardware_address[1], \
               (uint8_t)config->hardware_address[2], \
               (uint8_t)config->hardware_address[3], \
               (uint8_t)config->hardware_address[4],
               (uint8_t)config->hardware_address[5]);

	ip_asc2bytes(config->router, asc_gateway);
	ip_asc2bytes(config->netmask, asc_netmask);
	ip_asc2bytes(config->dns1, asc_dns1);
	ip_asc2bytes(config->dns2, asc_dns2);
	ip_asc2bytes(config->ip_address, asc_ip_address);

	return 0;
}

ip_allocator ip_allocator_handler = &sqlite_ip_allocator;
