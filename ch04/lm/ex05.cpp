#include "Expression.hpp"
#include "gtest/gtest.h"

TEST(LMCh04Ex05, willAddNumbers)
{
    auto calculator = lm::Expression("1.0 + 2.0");
    ASSERT_DOUBLE_EQ(3.0, calculator.getResult());
}

TEST(LMCh04Ex05, willSubtractNumbers)
{
    auto calculator = lm::Expression("3.1 - 5.3");
    ASSERT_DOUBLE_EQ(-2.2 , calculator.getResult());
}

TEST(LMCh04Ex05, willMultiplyNumbers)
{
    auto calculator = lm::Expression("20.1 * -0.128");
    ASSERT_DOUBLE_EQ(-2.5728, calculator.getResult());
}

TEST(LMCh04Ex05, willDivideNumbers)
{
    auto calculator = lm::Expression("128.0 / 64.0");
    ASSERT_DOUBLE_EQ(2.0, calculator.getResult());
}
