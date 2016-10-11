#include "gtest/gtest.h"
#include "ExpressionSplitter.hpp"
#include <sstream>
#include <vector>
#include <string>

TEST(ExpressionSplitterTest, willReturnTwoExpressions)
{
    std::string input{"12; 13;"};
    calc::ExpressionSplitter es;
    auto res = es.split(input);

    ASSERT_EQ(res.size(), 2u);
    ASSERT_EQ(res[0], "12");
    ASSERT_EQ(res[1], "13");
}

TEST(ExpressionSplitterTest, willAppendIncompleLine)
{
    std::string input1{"12 + 13; 13"};
    std::string input2{"+ 7;"};

    calc::ExpressionSplitter es;

    auto res1 = es.split(input1);
    auto res2 = es.split(input2);

    ASSERT_EQ(res1.size(), 1u);
    ASSERT_EQ(res1[0], "12 + 13");

    ASSERT_EQ(res2.size(), 1u);
    ASSERT_EQ(res2[0], "13 + 7");
}
