#include "Grains.hpp"
#include "gtest/gtest.h"

TEST(LMCh04Ex08, willCalculateCorrectlyForSmallValues)
{
    ASSERT_EQ(10, squaresForGrains(1000));
    ASSERT_EQ(11, squaresForGrains(2000));
}

TEST(LMCh04Ex08, willCalculateCorrectlyForSomewhatLargerValues)
{
    ASSERT_EQ(20, squaresForGrains(1000000));
}

TEST(LMCh04Ex08, willCalculateCorrectlyForEnormousValues)
{
    ASSERT_EQ(30, squaresForGrains(1000000000));
}
