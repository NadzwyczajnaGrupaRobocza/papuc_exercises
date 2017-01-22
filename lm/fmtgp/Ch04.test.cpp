#include <gtest/gtest.h>
#include "Ch04.hpp"

using namespace testing;


namespace fmtgp
{

namespace
{
constexpr auto epsilon = 2.0 * std::numeric_limits<line_segment>::epsilon();
}

TEST(lm_fmtgp_ch04, willComputeRemainder)
{
    ASSERT_NEAR(remainder(5.3, 1.5), 0.8, epsilon);
    ASSERT_NEAR(remainder(2.0, 5.0), 2.0, epsilon);
}

TEST(lm_fmtgp_ch04, willComputeQuotient)
{
    ASSERT_EQ(quotient(5.3, 2.0), 2);
}

TEST(lm_fmtgp_ch04, willComputeRemainderQuotientPair)
{
    const auto res = quotient_remainder(9.1, 3.0);
    ASSERT_EQ(std::get<0>(res), 3);
    ASSERT_NEAR(std::get<1>(res), 0.1, epsilon);
}

TEST(lm_fmtgp_ch04, willComputeRemainerUsingFibonacciMethod)
{
    ASSERT_NEAR(remainder_fibonacci(17.0, 3.0), 2.0, epsilon);
}

TEST(lm_fmtgp_ch04, willComputeQuotientUsingFibonacciMethod)
{
    ASSERT_EQ(quotient_fibonacci(45.0, 6.0), 7);
}

TEST(lm_fmtgp_ch04, willComputeQuotientUsingFibonacciMethod2)
{
    ASSERT_EQ(quotient_fibonacci(17.0, 3.0), 5);
}

TEST(lm_fmtgp_ch04, willComputeQuotientUsingFibonacciMethod3)
{
    ASSERT_EQ(quotient_fibonacci(43.0, 6.0), 7);
}

TEST(lm_fmtgp_ch04, willComputeQuotientUsingFibonacciMethod4)
{
    ASSERT_EQ(quotient_fibonacci(41.0, 6.0), 6);
}

TEST(lm_fmtgp_ch04, will_compute_line_segment_gcm)
{
    ASSERT_NEAR(gcm_remainder(25.0, 15.0), 5.0, epsilon);
}

TEST(lm_fmtgp_ch04, will_compute_integer_gcd)
{
    ASSERT_EQ(gcd(42, 35), 7);
}
}
