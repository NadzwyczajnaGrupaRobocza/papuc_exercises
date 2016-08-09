#include "gtest/gtest.h"
#include "Evaluator.hpp"
#include "TokenStream.hpp"

using namespace testing;

inline calc::TokenStream buildTs(const std::string& str)
{
    return calc::TokenStream{std::stringstream{str}};
}

TEST(EvaluatorTest, willAddTwoTokens)
{
    calc::Evaluator e{buildTs("12.3 + 2")};
    ASSERT_EQ(e.expression(), 14.3);
}

TEST(EvaluatorTest, willHandleMultiplication)
{
    calc::Evaluator e{buildTs("12.3 + 2 * 7 - 10 / 5")};
    ASSERT_EQ(e.expression(), 24.3);
}

TEST(EvaluatorTest, willHandleParenthesis)
{
    calc::Evaluator e{buildTs("2 * (3 + 4)")};
    ASSERT_EQ(e.expression(), 14.0);
}

TEST(EvaluatorTest, willHandleTwoTypesOfParenthesis)
{
    calc::Evaluator e{buildTs("{2 + 3} * (4 + 5)")};
    ASSERT_EQ(e.expression(), 45.0);
}

TEST(EvaluatorTest, willCalculateFactorial)
{
    calc::Evaluator e{buildTs("2 * 3!")};
    ASSERT_EQ(e.expression(), 12.0);
}

TEST(EvaluatorTest, willCalculateFactorialFromParenthesis)
{
    calc::Evaluator e{buildTs("(2 + 3)!")};
    ASSERT_EQ(e.expression(), 120.0);
}
