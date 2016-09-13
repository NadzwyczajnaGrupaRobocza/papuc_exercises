<<<<<<< HEAD
#include <gtest/gtest.h>
=======
>>>>>>> [LM][Ch07] adding unary plus/minus and modulo ops
#include "Evaluator.hpp"
#include "TokenStream.hpp"
#include "gtest/gtest.h"
#include <sstream>
#include <string>
#include <vector>

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

TEST(stringstream, howSplitWorks)
{
    std::vector<std::string> tokens;
    std::string input{"12; 13; 14;"};
    std::stringstream ss{input};
    std::string token;
    while (std::getline(ss, token, ';'))
    {
        tokens.push_back(token);
    }
    auto num_sep = std::count(input.begin(), input.end(), ';');
    ASSERT_EQ(num_sep, 3);
    ASSERT_EQ(tokens.size(), 3u);
}
