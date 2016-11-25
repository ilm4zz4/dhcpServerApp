#include <sqlite3.h>
#include <stdio.h>
#include<stdlib.h>
int main(void) {

    sqlite3 *db;
    char *err_msg = 0;

    int rc = sqlite3_open("dataBase.db", &db);

    if (rc != SQLITE_OK) {

        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);

        return 1;
    }

    char *sql = "DROP TABLE IF EXISTS Network;"
                 "CREATE TABLE Network( MAC TEXT, IP TETXT,  MASK TEXT, GW TEXT, DNS, ACTIVE INT);";

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK ) {

        fprintf(stderr, "SQL error: %s\n", err_msg);

        sqlite3_free(err_msg);
        sqlite3_close(db);

        return 1;
    }

   sqlite3_stmt *statement = NULL;
   int ret;
   ret = sqlite3_prepare(db, "SELECT * FROM Network WHERE MAC = 'b8:27:eb:8b:33:e0'",128, &statement, NULL);
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


    sqlite3_close(db);

    return 0;
}
