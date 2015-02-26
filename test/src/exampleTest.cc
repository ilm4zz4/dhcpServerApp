#include "gtest/gtest.h"

TEST(firstTest, abs)
{
  EXPECT_EQ(1, abs( -1 ));
  EXPECT_EQ(1, abs( 1 ));
}
