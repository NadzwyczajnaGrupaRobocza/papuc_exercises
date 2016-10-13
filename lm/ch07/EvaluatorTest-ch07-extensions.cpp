#include "Evaluator.hpp"
#include "TokenStream.hpp"
#include "gtest/gtest.h"
#include <sstream>
#include <string>

using namespace testing;

inline calc::TokenStream buildTs(const std::string& str)
{
    return calc::TokenStream{std::stringstream{str}};
}

TEST(EvaluatorTest_Ch07_Ext, willHandleUnaryMinus)
{
    calc::Evaluator e{buildTs("-1")};
    ASSERT_EQ(e.expression(), -1);
}

TEST(EvaluatorTest_Ch07_Ext, willHandleUnaryPlus)
{
  calc::Evaluator e{buildTs("+1")};
    ASSERT_EQ(e.expression(), 1);
}

TEST(EvaluatorTest_Ch07_Ext, willHandleModuloDivision)
{
    calc::Evaluator e{buildTs("4 % 3")};
    ASSERT_EQ(e.expression(), 1);
}
