#include<stdio.h>
#include<string.h>
#include"sqlite3.h"

#include "dhcp_log.h"
#include "dhcp_server.h"
#include "ip_allocator.h"
extern struct server_config gobal_config;

int init_database(){
	
	INFO("==>sqlite_ip_allocate");
	sqlite3 *db = NULL;
	char* err_msg = 0;
			

	int ret = sqlite3_open(gobal_config.ip_allocator_file, &db);
	if(SQLITE_OK != ret)
        {
                ERROR("***sqlite3_open ERROR!!! %s(%d)***", sqlite3_errmsg(db), ret);
                exit (1);
        }

	//If doesn't exist create database table
	//MAC: mac which send discovery message
	//IP: ip address which shall be assigned to host
	//ACTIVE: the ip is already assign
	//MASK, GW, DNS: configuration client
    char *sql = "DROP TABLE IF EXISTS Network;" 
                "CREATE TABLE Network( MAC TEXT, IP TETXT, ACTIVE INT, MASK TEXT, GW TEXT, DNS);"; 

    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK ) {
        
        fprintf(stderr, "***sqlite3_exec ERROR!!! %s(%d)***", err_msg);
        
        sqlite3_free(err_msg);        
        sqlite3_close(db);
        
        return 1;
    } 

	//Deactivation all ip address
	
   sqlite3_stmt *statement = NULL;
   
   ret = sqlite3_prepare(db, "UPDATE Network SET ACTIVE=0 WHERE ACTIVE=1;",128, &statement, NULL);
   if(SQLITE_OK != ret){
        fprintf(stderr, "***sqlite3_prepare: get all entryes ERROR!!! %s(%d)***", err_msg);
    	exit (1);
   }

	sqlite3_finalize(statement);

    sqlite3_close(db);

	return 0;
}

int sqlite_ip_allocator(struct network_config *config)
{
	INFO("==>IP_allocate");

	char asc_gateway[16] = {0};
	char asc_netmask[16] = {0};	
        char asc_dns1[16] = {0};
	char asc_dns2[16] = {0};
	char asc_ip_address[16] = {0};

	char value1[16] = {"192.168.75.1"};
	strncpy(asc_gateway, value1, 16);

        char value2[16] = {"255.255.255.0"};
        strncpy(asc_netmask, value2, 16);

	char value3[16] = {"8.8.8.8"};
	strncpy(asc_dns1, value3, 16);

	char value4[16] = {"4.4.4.4"};
        strncpy(asc_dns2, value4, 16);

	char value[16] = {"192.168.75.10"};
        strncpy(asc_ip_address, value, 16);


  
	INFO("gateway=%s, netmask=%s, dns1=%s, dns2=%s, ip=%s", asc_gateway, asc_netmask, asc_dns1, asc_dns2, asc_ip_address);
	
	//convert mac address to 64-bit int.
	//the first 6 bytes of network_config.hardware_address
	//should be mac address. 
	uint64_t mac = 0x0000000000000000;
	int i = 0;
	for(i = 0; i < 6; i++)
	{
		mac *= 0x100;
//		DEBUG("mac=%lx", mac);
		mac += (uint8_t)config->hardware_address[i];
//		DEBUG("mac=%lx", mac);
	}

	DEBUG("mac address=%02x:%02x:%02x:%02x:%02x:%02x, \
	       integer value=%ld", \
	       (uint8_t)config->hardware_address[0], \
               (uint8_t)config->hardware_address[1], \
               (uint8_t)config->hardware_address[2], \
               (uint8_t)config->hardware_address[3], \
               (uint8_t)config->hardware_address[4], 
               (uint8_t)config->hardware_address[5], mac);
	
	ip_asc2bytes(config->router, asc_gateway);
	ip_asc2bytes(config->netmask, asc_netmask);
	ip_asc2bytes(config->dns1, asc_dns1);
	ip_asc2bytes(config->dns2, asc_dns2);
	ip_asc2bytes(config->ip_address, asc_ip_address); 

	return 0;
}

ip_allocator ip_allocator_handler = &sqlite_ip_allocator;
