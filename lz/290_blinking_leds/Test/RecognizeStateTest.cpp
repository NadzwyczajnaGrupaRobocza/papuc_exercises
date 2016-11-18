#include <gtest/gtest.h>

#include "LedToken.hpp"
#include "RecognizeState.hpp"

namespace lz
{
TEST(RecognizeStateTest, parse)
{
    RecognizeState recognize{};
    EXPECT_EQ(LedTokenState::LedLdCommand, recognize.parse(LedToken{"ld"}));
    EXPECT_EQ(LedTokenState::LedOutCommand, recognize.parse(LedToken{"out"}));
}

TEST(RecognizeStateTest, invalid)
{
    RecognizeState recognize{};
    EXPECT_THROW(recognize.parse(LedToken{"buu"}), std::out_of_range);
    EXPECT_THROW(recognize.parse(LedToken{" ld"}), std::out_of_range);
    EXPECT_THROW(recognize.parse(LedToken{"ld "}), std::out_of_range);
}
}
