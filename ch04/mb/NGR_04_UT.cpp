#include <vector>
#include "gtest/gtest.h"
#include "NGR_04_02_01.hpp"
#include "NGR_04_03_01.hpp"
#include "NGR_04_05_01.hpp"

std::vector<double> emptyData = {};
std::vector<double> someData1 = {12.0, 33.5, 11.5, 24.45};
std::vector<double> someData2 = {100.3, -23.2, -12.0, 23.6, 13.1};

// Excercise 02
TEST(MBB_04_02, showVector)
{
    EXPECT_EQ("[12, 33.5, 11.5, 24.45]", showVector(someData1));
}

TEST(MBB_04_02, getMedianaFromOddVector)
{
    EXPECT_EQ(13.1, getMediana(someData2));
}


TEST(MBB_04_02, getMedianaFromEvenVector)
{
    EXPECT_EQ(18.225, getMediana(someData1));
}

// Excercise 03
TEST(MBB_04_03, getTotalDistanceFromEmptyVector)
{
    EXPECT_EQ(0.0, getTotalDistance(emptyData));
}

TEST(MBB_04_03, getTotalDistanceFromVector)
{
    EXPECT_EQ(81.45, getTotalDistance(someData1));
}

TEST(MBB_04_03, getSmallestDistanceFromEmptyVector)
{
    EXPECT_EQ(0.0, getSmallestDistance(emptyData));
}

TEST(MBB_04_03, getSmallestDistanceFromVector)
{
    EXPECT_EQ(11.5, getSmallestDistance(someData1));
}

TEST(MBB_04_03, getLargestDistanceFromEmptyVector)
{
    EXPECT_EQ(0.0, getLargestDistance(emptyData));
}

TEST(MBB_04_03, getLargestDistanceFromVector)
{
    EXPECT_EQ(33.5, getLargestDistance(someData1));
}

TEST(MBB_04_03, getMeanDistanceFromEmptyVector)
{
    EXPECT_EQ(0.0, getMeanDistance(emptyData));
}

TEST(MBB_04_03, getMeanDistanceFromVector)
{
    EXPECT_EQ(20.3625, getMeanDistance(someData1));
}

// Excercise 05
TEST(MBB_04_05, simpleTest)
{
    Calculator calc = Calculator(12.0, 2.3, "+");
    EXPECT_EQ(0.0, 0.0);
}

TEST(MBB_04_05, calculateTest)
{
    Calculator calc = Calculator(12.0, 2.3, "+");
    EXPECT_EQ(14.3, calc.calculate());
}
