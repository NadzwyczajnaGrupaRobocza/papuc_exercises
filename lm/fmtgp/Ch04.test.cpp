#include <gtest/gtest.h>
#include "Ch04.hpp"

using namespace testing;

TEST(lm_fmtgp_ch04, willComputeRemainder)
{
    ASSERT_EQ(quotient(5.3, 2.0), 2);
}
