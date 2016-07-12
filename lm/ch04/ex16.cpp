#include "MinMaxMode.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

TEST(LMCh04Ex16, willReturnMinForSmallData)
{
    const auto props = MMM::Properties<int>({2, 666, -3, 42});
    ASSERT_EQ(-3, props.getMin());
}

TEST(LMCh04Ex16, willReturnMaxForSmallData)
{
    const auto props = MMM::Properties<int>({2, 666, -3, 42});
    ASSERT_EQ(666, props.getMax());
}

TEST(LMCh04Ex16, willReturnSingleMode)
{
    const auto props = MMM::Properties<int>({2, 666, -3, 2, 42});
    const std::set<int> expectedReturnValue = {2};
    ASSERT_EQ(expectedReturnValue, props.getMode());
}

TEST(LMCh04Ex16, willReturnTwoModes)
{
    const auto props = MMM::Properties<int>({2, 666, -3, 2, 42, 666});
    const std::set<int> expectedReturnValue = {2, 666};
    ASSERT_EQ(expectedReturnValue, props.getMode());
}
