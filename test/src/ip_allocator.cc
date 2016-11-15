
// Tests factorial of negative numbers.
TEST(ip_allocator, init) {
    
   INFO("==>sqlite_ip_allocate");
   sqlite3 *db = NULL;

   int ret = sqlite3_open(gobal_config.ip_allocator_file, &db);
   if(SQLITE_OK != ret)
   {
      ERROR("***sqlite3_open ERROR!!! %s(%d)***", sqlite3_errmsg(db), ret);
      goto ERROR;
   }

   //If doesn't exist create database table
   //MAC: mac which send discovery message
   //IP: ip address which shall be assigned to host
   //ACTIVE: the ip is already assign
   //MASK, GW, DNS: configuration client
   char *sql = "DROP TABLE IF EXISTS Network;" 
                "CREATE TABLE Network( MAC TEXT, IP TETXT, ACTIVE INT, MASK TEXT, GW TEXT, DNS);" 
                "ADD TABLE Network VALUES( 'AABBCCDDEEFF', '192.168.0.1', 1, '24', '192.169.1.1', '8.8.8.8');" 
                "ADD TABLE Network VALUES( 'AABBCCDDEEFF', '192.168.0.1', 1, '24', '192.169.1.1', '8.8.8.8');" 
                "ADD TABLE Network VALUES( 'AABBCCDDEEFF', '192.168.0.1', 1, '24', '192.169.1.1', '8.8.8.8');" 
                "ADD TABLE Network VALUES( 'AABBCCDDEEFF', '192.168.0.1', 0, '24', '192.169.1.1', '8.8.8.8');" 
                "ADD TABLE Network VALUES( 'AABBCCDDEEFF', '192.168.0.1', 1, '24', '192.169.1.1', '8.8.8.8');" 

   rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
   EXPECT_EQ(rc, SQLITE_OK );
   if (rc != SQLITE_OK ) {
        
      sqlite3_free(err_msg);        
      sqlite3_close(db);
        
      return 1;
   } 

   //Check the current ACTIVE flag 
   int ret = sqlite3_prepare(db, "SELECT COUNT(*) FROM Network WHERE ACTIVE=1",128, &statement, NULL);
   EXPECT_EQ(SQLITE_OK, ret);
   if(SQLITE_OK != ret){
      fprintf(stderr, "***sqlite3_prepare: get all entryes ERROR!!! %s(%d)***", err_msg);
      exit (1);
   }
   
   EXPECT_EQ(statement[0], 4);
        
   init_database();

   //Check the correct replace of the 'active' flag 
   sqlite3_stmt *statement = NULL;
   
   ret = sqlite3_prepare(db, "SELECT COUNT(*) FROM Network WHERE ACTIVE=1",128, &statement, NULL);
   EXPECT_EQ(SQLITE_OK, ret);
   if(SQLITE_OK != ret){
      fprintf(stderr, "***sqlite3_prepare: get all entryes ERROR!!! %s(%d)***", err_msg);
      exit (1);
   }
   EXPECT_EQ(statement[0], 0);
   
   sqlite3_finalize(statement);

   sqlite3_close(db);
}
