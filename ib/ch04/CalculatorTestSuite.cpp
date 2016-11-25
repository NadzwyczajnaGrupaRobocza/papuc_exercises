#include "ch_04_05.hpp"
#include "gtest/gtest.h"

TEST(CalculatorTest, first)
{
    calculator cal('+');

    EXPECT_DOUBLE_EQ(cal.compute(2.8, 1.6), 4.4);
}
