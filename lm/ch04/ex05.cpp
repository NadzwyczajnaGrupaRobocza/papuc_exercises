#include "Expression.hpp"
#include "gtest/gtest.h"

TEST(LMCh04Ex05, willAddNumbers)
{
    auto expression = lm::Expression("1.0 + 2.0");
    ASSERT_DOUBLE_EQ(3.0, expression.getResult());
}

TEST(LMCh04Ex05, willSubtractNumbers)
{
    auto expression = lm::Expression("3.1 - 5.3");
    ASSERT_DOUBLE_EQ(-2.2, expression.getResult());
}

TEST(LMCh04Ex05, willMultiplyNumbers)
{
    auto expression = lm::Expression("20.1 * -0.128");
    ASSERT_DOUBLE_EQ(-2.5728, expression.getResult());
}

TEST(LMCh04Ex05, willDivideNumbers)
{
    auto expression = lm::Expression("128.0 / 64.0");
    ASSERT_DOUBLE_EQ(2.0, expression.getResult());
}

TEST(LMCh04Ex05, willThrowExceptionOnUnknownOp)
{
    auto expression = lm::Expression("12.0 ^ 14.1");
    ASSERT_THROW(expression.getResult(), std::runtime_error);
}
