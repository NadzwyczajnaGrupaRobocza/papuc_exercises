#include <vector>
#include "gtest/gtest.h"
#include "NGR_04_03_01.hpp"

std::vector<double> emptyData = {};
std::vector<double> someData = {12.0, 33.5, 11.5, 24.45};

TEST(MBB_04_03, getTotalDistanceFromEmptyVector)
{
    EXPECT_EQ(0.0, getTotalDistance(emptyData));
}

TEST(MBB_04_03, getTotalDistanceFromVector)
{
    EXPECT_EQ(81.45, getTotalDistance(someData));
}

TEST(MBB_04_03, getSmallestDistanceFromEmptyVector)
{
    EXPECT_EQ(0.0, getSmallestDistance(emptyData));
}

TEST(MBB_04_03, getSmallestDistanceFromVector)
{
    EXPECT_EQ(11.5, getSmallestDistance(someData));
}

TEST(MBB_04_03, getLargestDistanceFromEmptyVector)
{
    EXPECT_EQ(0.0, getLargestDistance(emptyData));
}

TEST(MBB_04_03, getLargestDistanceFromVector)
{
    EXPECT_EQ(33.5, getLargestDistance(someData));
}

TEST(MBB_04_03, getMeanDistanceFromEmptyVector)
{
    EXPECT_EQ(0.0, getMeanDistance(emptyData));
}

TEST(MBB_04_03, getMeanDistanceFromVector)
{
    EXPECT_EQ(20.3625, getMeanDistance(someData));
}
