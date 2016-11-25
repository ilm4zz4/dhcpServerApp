
#include <limits.h>
#include "dhcp_log.h"
#include "dhcp_server.h"
#include "gtest/gtest.h"
#include "test_function.h"
#include "ip_allocator.h"
#include "sqlite3.h"

extern uint8_t discover_tmp[300];
extern uint8_t offer_tmp[300];
extern uint8_t request_tmp[300];
extern uint8_t ack_tmp[300];
extern uint8_t release_tmp[300];
extern uint8_t inform_tmp[247];
extern uint8_t decline_tmp[247];


extern struct server_config gobal_config;

// Tests factorial of negative numbers.
TEST(dhcp_server, read_configFile) {
    // This test is named "Negative", and belongs to the "FactorialTest"
    // test case.
    int ret = read_configFile("test/cfg/dhcp_server.conf");
    if( ret < 0){
      EXPECT_NE(ret, -1);
    }
}

TEST(dhcp_server, ip_asc2byte) {
    // This test is named "Negative", and belongs to the "FactorialTest"
    // test case.
    EXPECT_EQ(0, ip_asc2bytes(NULL, NULL));
    char ipString[]={"192.168.0.1"};
    EXPECT_EQ(0, ip_asc2bytes(NULL, ipString));

    char array[4];
    EXPECT_EQ(4, ip_asc2bytes(array, ipString));
    EXPECT_EQ('\xC0', array[0]);
    EXPECT_EQ('\xA8', array[1]);
    EXPECT_EQ('\x00', array[2]);
    EXPECT_EQ('\x01', array[3]);
}



TEST(dhcp_server, marshall) {

    EXPECT_EQ(NULL,marshall(NULL,0,0));

}

TEST(dhcp_server, dispach) {

  int ret = read_configFile("./cfg/dhcp_server.conf");
  if( ret < 0){
    EXPECT_NE(ret, -1);
  }
  char* fileName = gobal_config.ip_allocator_file;
  sqlite3* db = NULL;
  //create database
  bool succ = create_database(fileName, &db);
  EXPECT_EQ(succ, true);
 if(succ==false)
       exit(1);


    struct raw_msg *msg = (raw_msg*)new uint8_t[sizeof(struct raw_msg)];
    memset(msg->buff, 0, sizeof(discover_tmp));
    memcpy(msg->buff, discover_tmp, sizeof(discover_tmp));
    msg->length=sizeof(discover_tmp);

    //Test with malformed packed raw
    EXPECT_EQ((struct dhcp_packet*)marshall(msg->buff, 0, 0),(struct dhcp_packet*)NULL);
    EXPECT_EQ((struct dhcp_packet*)marshall(msg->buff, 0, BOOTP_ABSOLUTE_MIN_LEN-1),(struct dhcp_packet*)NULL);
    EXPECT_EQ((struct dhcp_packet*)marshall(msg->buff, 0, DHCP_MAX_MTU+1),(struct dhcp_packet*)NULL);

    //Discovery & Offer
    struct dhcp_packet* discovery = marshall(msg->buff, 0, msg->length);
    EXPECT_NE((struct dhcp_packet*)discovery,(struct dhcp_packet*)NULL);

    struct dhcp_packet* offer = dispatch(discovery);
    EXPECT_NE((struct dhcp_packet*)offer,(struct dhcp_packet*)NULL);
    if(offer != NULL){
    //Test all packet without last magic number, 2 data pointer
        for ( unsigned int i = 0; i < (sizeof(struct dhcp_packet)-sizeof(struct dhcp_option)); i++){
            uint8_t expected = (int)(((uint8_t*)offer_tmp)[i]);
            uint8_t actual = (int)(((uint8_t*)offer)[i]);
            EXPECT_EQ(actual,expected);

        }
    }

    //Request & ACK
    memset(msg->buff, 0, sizeof(request_tmp));
    memcpy(msg->buff,request_tmp, sizeof(request_tmp));
    msg->length=sizeof(request_tmp);


    struct dhcp_packet* request = marshall(msg->buff, 0, msg->length);
    EXPECT_NE((struct dhcp_packet*)request,(struct dhcp_packet*)NULL);

    struct dhcp_packet* ack = dispatch(request);
    EXPECT_NE((struct dhcp_packet*)ack,(struct dhcp_packet*)NULL);
    if(offer != NULL){
    //Test all packet without last magic number, 2 data pointer
        for ( unsigned int i = 0; i < (sizeof(struct dhcp_packet)-sizeof(struct dhcp_option)); i++){
            uint8_t expected = (int)(((uint8_t*)ack_tmp)[i]);
            uint8_t actual = (int)(((uint8_t*)ack)[i]);
            EXPECT_EQ(actual,expected);

        }
    }

    //Release
    memset(msg->buff, 0, sizeof(release_tmp));
    memcpy(msg->buff,release_tmp, sizeof(release_tmp));
    msg->length=sizeof(release_tmp);


    struct dhcp_packet* release_msg = marshall(msg->buff, 0, msg->length);
    EXPECT_NE((struct dhcp_packet*)release_msg,(struct dhcp_packet*)NULL);
    struct dhcp_packet* rsp = dispatch(release_msg);
    EXPECT_EQ((struct dhcp_packet*)rsp,(struct dhcp_packet*)NULL);

    //Inform
    memset(msg->buff, 0, sizeof(msg->buff));
    memcpy(msg->buff,inform_tmp, sizeof(inform_tmp));
    msg->length=sizeof(inform_tmp);


    struct dhcp_packet* inform_msg = marshall(msg->buff, 0, msg->length);
    EXPECT_NE((struct dhcp_packet*)inform_msg,(struct dhcp_packet*)NULL);
    struct dhcp_packet* rspInform = dispatch(inform_msg);
    EXPECT_NE((struct dhcp_packet*)rspInform,(struct dhcp_packet*)NULL);

    //Decline
    memset(msg->buff, 0, sizeof(msg->buff));
    memcpy(msg->buff,decline_tmp, sizeof(decline_tmp));
    msg->length=sizeof(decline_tmp);


    struct dhcp_packet* decline_msg = marshall(msg->buff, 0, msg->length);
    EXPECT_NE((struct dhcp_packet*)decline_msg,(struct dhcp_packet*)NULL);
    struct dhcp_packet* rspDecline = dispatch(decline_msg);
    EXPECT_EQ((struct dhcp_packet*)rspDecline,(struct dhcp_packet*)NULL);

  close_database(db);

	delete msg;

}

TEST(dhcp_server, free_packet) {
	//Packet NULL
	free_packet(NULL);

	struct raw_msg *msg = (raw_msg*)new uint8_t[sizeof(struct raw_msg)];
	//padding NULL
	memset(msg->buff, 0, sizeof(msg->buff));
	memcpy(msg->buff,decline_tmp, sizeof(decline_tmp));
	msg->length=sizeof(decline_tmp);


	struct dhcp_packet* decline_msg = marshall(msg->buff, 0, msg->length);
	EXPECT_NE((struct dhcp_packet*)decline_msg,(struct dhcp_packet*)NULL);
	free_packet(decline_msg);

	delete msg;

}

TEST(dhcp_server, handle_msg){

	struct raw_msg *msg = (raw_msg*)new uint8_t[sizeof(struct raw_msg)];

	memset(msg->buff, 0, sizeof(request_tmp));
    memcpy(msg->buff,request_tmp, sizeof(request_tmp));
    msg->length=sizeof(request_tmp);

	handle_msg(msg);

	//delete msg; /*Already deleted*/

}

TEST(dhcp_server, start_server) {

   EXPECT_EQ(-1, start_server(NULL));

   char cfg [] = {"test/cfg/dhcp_server.conf"};
   EXPECT_EQ(-1, start_server(cfg));

}

TEST(dhcp_server, log_init) {

   EXPECT_EQ(-1, log_init(NULL));

   char cfg [] = {"dhcp_log.conf"};
   EXPECT_EQ(-1, log_init(cfg));

}

TEST(dhcp_server,dhcp_log) {

   char cfg [] = {"./test/cfg/dhcp_log.conf"};
   EXPECT_NE(-1, log_init(cfg));

   FATAL("***Test log %s(%d)*** do_discover==>", "fatal", 1);
   ERROR("***Test log %s(%d)*** do_discover==>", "error", 1);
   WARN("***Test log %s(%d)*** do_discover==>", "warning", 1);
   DEBUG("***Test log %s(%d)*** do_discover==>", "debug", 1);
   INFO("***Test log %s(%d)*** do_discover==>", "info", 1);
}
