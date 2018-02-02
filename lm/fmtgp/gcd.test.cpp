#include <gtest/gtest.h>
#include "gcd.hpp"

TEST(lm_fmtgp_gcd, willComputeGcd)
{
    //ASSERT_EQ(stein_GCD(11, 121), 11);
    ASSERT_EQ(euclid_GCD(11, 121), 11);
}

TEST(lm_fmtgp_gcd, willComputeExtendedGcdForPositiveIntegers)
{
    auto result = gcd::extended_gcd(7, 5);
    ASSERT_EQ(result, std::make_pair(-2, 1));

    auto result2 = gcd::extended_gcd(2 * 2 * 3 * 3, 2 * 2 * 2 * 3 * 7);
    ASSERT_EQ(result2, std::make_pair(5, 2 * 2 * 3));
}
