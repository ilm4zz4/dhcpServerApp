
#include <limits.h>
#include "dhcp_server.h"
#include "gtest/gtest.h"
#include "global.h"


// Tests factorial of negative numbers.
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


TEST(dhcp_server, start_server) {
EXPECT_EQ(-1,start_server(NULL));

}

TEST(dhcp_server, marshall) {



	EXPECT_EQ(NULL,marshall(NULL,0,0));


}

TEST(dhcp_server, dispach) {

uint8_t discover_tmp[] = {
0x01, 0x01, 0x06, 0x00, 0xcb, 0xa3, 0xf0, 0x1c, 
0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0xb8, 0x27, 0xeb, 0x8b, 
0x33, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x63, 0x82, 0x53, 0x63, 
0x35, 0x01, 0x01, 0x32, 0x04, 0xc0, 0xa8, 0x19, 
0x0a, 0x0c, 0x0b, 0x72, 0x61, 0x73, 0x70, 0x62, 
0x65, 0x72, 0x72, 0x79, 0x70, 0x69, 0x37, 0x0d, 
0x01, 0x1c, 0x02, 0x03, 0x0f, 0x06, 0x77, 0x0c, 
0x2c, 0x2f, 0x1a, 0x79, 0x2a, 0xff, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00 };



uint8_t  response_tmp[] = {
0x02, 0x01, 0x06, 0x01, 0xcb, 0xa3, 0xf0, 0x1c, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0xc0, 0xa8, 0x19, 0x0a, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0xb8, 0x27, 0xeb, 0x8b, 
0x33, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x63, 0x82, 0x53, 0x63, 
0x35, 0x01, 0x02, 0x36, 0x04, 0xc0, 0xa8, 0x19, 
0x01, 0x33, 0x04, 0x80, 0x51, 0x01, 0x00, 0x3a, 
0x04, 0x30, 0x0b, 0x01, 0x00, 0x03, 0x04, 0xc0, 
0xa8, 0x19, 0x01, 0x01, 0x04, 0xff, 0xff, 0xff, 
0x00, 0x06, 0x08, 0x08, 0x08, 0x08, 0x08, 0x04, 
0x04, 0x04, 0x04, 0xff, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00 };

   struct raw_msg *msg = (raw_msg*)new uint8_t[sizeof(struct raw_msg)]; 
   memset(msg->buff, 0, DHCP_MAX_MTU);
   memcpy(msg->buff, discover_tmp, sizeof(discover_tmp));
   msg->length=sizeof(discover_tmp);
   
   struct dhcp_packet *request = marshall(msg->buff, 0, msg->length); 
   
   struct dhcp_packet *response = dispatch(request);
   		
	for ( unsigned int i = 0; i < (sizeof(struct dhcp_packet)-2*sizeof(int*)-4); i++){
   	    uint8_t expected = (int)(((uint8_t*)response_tmp)[i]);
   	    uint8_t actual = (int)(((uint8_t*)response)[i]);
   		EXPECT_EQ(actual,expected);  
   
   	}
}
