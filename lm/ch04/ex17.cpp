#include "gtest/gtest.h"
#include "MinMaxMode.hpp"
#include <string>

TEST(LMCh04Ex17, willReturnMinForSmallData)
{
    const auto props = MMM::Properties<std::string>({"bbb", "zzz", "aaa", "frg"});
    ASSERT_EQ(std::string{"aaa"}, props.getMin());
}

TEST(LMCh04Ex17, willReturnMaxForSmallData)
{
    const auto props = MMM::Properties<std::string>({"bbb", "zzz", "aaa", "frg"});
    ASSERT_EQ(std::string{"zzz"}, props.getMax());
}

TEST(LMCh04Ex17, willReturnSingleMode)
{
    const auto props = MMM::Properties<std::string>({"bbb", "zzz", "aaa", "bbb", "frg"});
    ASSERT_EQ(std::set<std::string>{"bbb"}, props.getMode());
}

TEST(LMCh04Ex17, willReturnTwoModes)
{
    const auto props = MMM::Properties<std::string>({"bbb", "zzz", "aaa", "bbb", "frg", "zzz"});
    const auto expectedReturnValue = std::set<std::string>{"bbb", "zzz"};
    ASSERT_EQ(expectedReturnValue, props.getMode());
}
