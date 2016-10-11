#include "TokenStream.hpp"
#include "gtest/gtest.h"
#include <sstream>

namespace
{
constexpr auto epsilon = 0.00000001;
}

TEST(TokenStreamTest, willReturnTokensForSimpleExpression)
{
    std::stringstream in{"12.1 + 17.3"};
    calc::TokenStream ts{in};
    std::vector<calc::Token> output{};
    // output.emplace_back(ts.get());
    // output.emplace_back(ts.get());
    // output.emplace_back(ts.get());
    std::generate_n(std::back_inserter(output), 4, [&] { return ts.get(); });

    ASSERT_EQ(output.size(), 4u);
    ASSERT_EQ(output[0].typeId, '8');
    ASSERT_NEAR(output[0].value, 12.1, epsilon);

    ASSERT_EQ(output[1].typeId, '+');

    ASSERT_EQ(output[2].typeId, '8');
    ASSERT_NEAR(output[2].value, 17.3, epsilon);

    ASSERT_EQ(output[3].typeId, 'E');
}
