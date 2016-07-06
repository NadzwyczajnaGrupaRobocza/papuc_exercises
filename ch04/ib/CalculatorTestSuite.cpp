#include "gtest/gtest.h"
#include "ch_04_05.hpp"


class CalculatorTest: public ::testing::Test
{
public:


void SetUp()
{
}

};

TEST_F(CalculatorTest, first)
{
calculator cal('+');

EXPECT_EQ(cal.compute(2.8, 1.6), 4.4);
}
