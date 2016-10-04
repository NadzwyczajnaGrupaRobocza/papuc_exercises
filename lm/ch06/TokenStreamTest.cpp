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

TEST(TokenStreamTest, willSplitSymbols)
{
    std::stringstream in{"ident2 + id_ent7"};
    calc::TokenStream ts{in};
    std::vector<calc::Token> output{};
    output.reserve(3u);
    std::generate_n(std::back_inserter(output), 3, [&] { return ts.get(); });

    ASSERT_EQ(output.size(), 3u);
    ASSERT_EQ(output[0].typeId, 'S');
    ASSERT_EQ(output[0].id, "ident2");

    ASSERT_EQ(output[1].typeId, '+');

    ASSERT_EQ(output[2].typeId, 'S');
    ASSERT_EQ(output[2].id, "id_ent7");
}

TEST(TokenStreamTest, willSplitSymbolsSeparatedByWhitespace)
{
    std::stringstream in{"id ent2 + id_ent7"};
    calc::TokenStream ts{in};
    std::vector<calc::Token> output{};
    output.reserve(4u);
    std::generate_n(std::back_inserter(output), 4, [&] { return ts.get(); });

    ASSERT_EQ(output.size(), 4u);
    ASSERT_EQ(output[0].typeId, 'S');
    ASSERT_EQ(output[0].id, "id");

    ASSERT_EQ(output[1].typeId, 'S');
    ASSERT_EQ(output[1].id, "ent2");

    ASSERT_EQ(output[2].typeId, '+');

    ASSERT_EQ(output[3].typeId, 'S');
    ASSERT_EQ(output[3].id, "id_ent7");
}
