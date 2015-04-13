
#include <limits.h>
#include "dhcp_server.h"
#include "gtest/gtest.h"


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
