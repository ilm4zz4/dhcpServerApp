#include <sqlite3.h>
#include <stdio.h>
#include<stdlib.h>
int main(void) {
    
    sqlite3 *db;
    char *err_msg = 0;
    
    int rc = sqlite3_open("test.db", &db);
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return 1;
    }
    
    char *sql = "DROP TABLE IF EXISTS Network;" 
                "CREATE TABLE Network(IP TETXT, MAC TEXT, MASK TEXT, GW TEXT, DNS);" 
                "INSERT INTO Network VALUES('192.168.22.12', '112233445566', '24', '255.255.255.0', '8.8.8.8');" 
                "INSERT INTO Network VALUES('192.168.22.13', '332233445566', '24', '255.255.255.0', '8.8.8.8');" 
                "INSERT INTO Network VALUES('192.168.22.14', 'BB2233445566', '24', '255.255.255.0', '8.8.8.8');" 
                "INSERT INTO Network VALUES('192.168.22.15', 'CC2233445566', '24', '255.255.255.0', '8.8.8.8');" 
                "INSERT INTO Network VALUES('192.168.22.16', 'DD2233445566', '24', '255.255.255.0', '8.8.8.8');"; 

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    
    if (rc != SQLITE_OK ) {
        
        fprintf(stderr, "SQL error: %s\n", err_msg);
        
        sqlite3_free(err_msg);        
        sqlite3_close(db);
        
        return 1;
    } 
   
   sqlite3_stmt *statement = NULL;
   int ret;
   ret = sqlite3_prepare(db, "SELECT * FROM Network WHERE MAC = 'CC2233445566'",128, &statement, NULL);
   if(SQLITE_OK != ret){
    printf("Error prepare");
    exit (1);
   }
   ret =sqlite3_step(statement);

   if(SQLITE_ROW == ret){
        printf("IP: %s\n", sqlite3_column_text(statement,0));
        printf("MACK: %s\n", sqlite3_column_text(statement,1));
        printf("MASK: %s\n", sqlite3_column_text(statement,2));
        printf("GW: %s\n", sqlite3_column_text(statement,3));
        printf("DNS: %s\n", sqlite3_column_text(statement,4));
   }

    ret = sqlite3_prepare(db, "INSERT INTO Network VALUES('192.168.22.16', 'DD22334455Ad', '24', '255.255.255.0', '8.8.8.8')",128, &statement, NULL);
   if(SQLITE_OK != ret){
    printf("Error prepare");
    exit (1);
   }

ret =sqlite3_step(statement);

 ret = sqlite3_prepare(db, "SELECT * FROM Network WHERE IP = '192.168.22.16'",128, &statement, NULL);
   if(SQLITE_OK != ret){
    printf("Error prepare");
    exit (1);
   }
   ret =sqlite3_step(statement);

   if(SQLITE_ROW == ret){
        printf("IP: %s\n", sqlite3_column_text(statement,0));
        printf("MACK: %s\n", sqlite3_column_text(statement,1));
        printf("MASK: %s\n", sqlite3_column_text(statement,2));
        printf("GW: %s\n", sqlite3_column_text(statement,3));
        printf("DNS: %s\n", sqlite3_column_text(statement,4));
   }

   ret =sqlite3_step(statement);

   if(SQLITE_ROW == ret){
        printf("IP: %s\n", sqlite3_column_text(statement,0));
        printf("MACK: %s\n", sqlite3_column_text(statement,1));
        printf("MASK: %s\n", sqlite3_column_text(statement,2));
        printf("GW: %s\n", sqlite3_column_text(statement,3));
        printf("DNS: %s\n", sqlite3_column_text(statement,4));
   }
   ret =sqlite3_step(statement);

   if(SQLITE_ROW == ret){
        printf("*IP: %s\n", sqlite3_column_text(statement,0));
        printf("MACK: %s\n", sqlite3_column_text(statement,1));
        printf("MASK: %s\n", sqlite3_column_text(statement,2));
        printf("GW: %s\n", sqlite3_column_text(statement,3));
        printf("DNS: %s\n", sqlite3_column_text(statement,4));
   }
    sqlite3_close(db);
    
    return 0;
}
