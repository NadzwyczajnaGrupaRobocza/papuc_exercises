#include "Common.hpp"
#include "gtest/gtest.h"

#include <stdexcept>

TEST(Common, compareToEqualDoubles)
{
    const double epsilon = 0.0000001;
    const double first = 12.123456789;
    const double second = first + epsilon / 2;
    EXPECT_TRUE(mbcommon::doublesAreEqual(first, second, epsilon));
}

TEST(Common, compareToNonEqualDoubles)
{
    const double epsilon = 0.0000001;
    const double first = 12.123456789;
    const double second = first + 2 * epsilon;
    EXPECT_FALSE(mbcommon::doublesAreEqual(first, second, epsilon));
}

TEST(Common, factorialFrom6)
{
    EXPECT_EQ(mbcommon::factorial(6), 720);
}

TEST(Common, factorialFrom0)
{
    EXPECT_EQ(mbcommon::factorial(0), 1);
}
