#include "MB_04_02.hpp"
#include "MB_04_03.hpp"
#include "MB_04_05.hpp"
#include "MB_04_08.hpp"
#include "MB_04_10.hpp"
#include "gtest/gtest.h"
#include <stdexcept>
#include <vector>

std::vector<double> emptyData = {};
std::vector<double> someData1 = {12.0, 33.5, 11.5, 24.45};
std::vector<double> someData2 = {100.3, -23.2, -12.0, 23.6, 13.1};

// Excercise 02
//==============
TEST(MBB_04_02, showVector)
{
    EXPECT_EQ("[12, 33.5, 11.5, 24.45]", showVector(someData1));
}

TEST(MBB_04_02, getMedianaFromOddVector)
{
    EXPECT_DOUBLE_EQ(13.1, getMedian(someData2));
}

TEST(MBB_04_02, getMedianaFromEvenVector)
{
    EXPECT_DOUBLE_EQ(18.225, getMedian(someData1));
}

// Excercise 03
//==============
TEST(MBB_04_03, getTotalDistanceFromEmptyVector)
{
    EXPECT_DOUBLE_EQ(0.0, getTotalDistance(emptyData));
}

TEST(MBB_04_03, getTotalDistanceFromVector)
{
    EXPECT_DOUBLE_EQ(81.45, getTotalDistance(someData1));
}

TEST(MBB_04_03, getSmallestDistanceFromEmptyVector)
{
    EXPECT_DOUBLE_EQ(0.0, getSmallestDistance(emptyData));
}

TEST(MBB_04_03, getSmallestDistanceFromVector)
{
    EXPECT_DOUBLE_EQ(11.5, getSmallestDistance(someData1));
}

TEST(MBB_04_03, getLargestDistanceFromEmptyVector)
{
    EXPECT_DOUBLE_EQ(0.0, getLargestDistance(emptyData));
}

TEST(MBB_04_03, getLargestDistanceFromVector)
{
    EXPECT_DOUBLE_EQ(33.5, getLargestDistance(someData1));
}

TEST(MBB_04_03, getMeanDistanceFromEmptyVector)
{
    EXPECT_DOUBLE_EQ(0.0, getMeanDistance(emptyData));
}

TEST(MBB_04_03, getMeanDistanceFromVector)
{
    EXPECT_DOUBLE_EQ(20.3625, getMeanDistance(someData1));
}

// Excercise 05
//==============
TEST(MBB_04_05, throwingErrorAfterGettingEmptyData)
{
    Data data = {0, 0, ""};
    Calculator calc = Calculator(data);
    EXPECT_THROW(calc.runCalculator(), std::string);
}

TEST(MBB_04_05, throwingErrorAfterGettingWrongOperator)
{
    Data data = {12.0, 3.0, "%"};
    Calculator calc = Calculator(data);
    EXPECT_THROW(calc.runCalculator(), std::string);
}

TEST(MBB_04_05, throwingErrorAfterDividingByZero)
{
    Data data = {12.0, 0, "/"};
    Calculator calc = Calculator(data);
    EXPECT_THROW(calc.runCalculator(), std::string);
}

TEST(MBB_04_05, printSum)
{
    Data data = {12.0, 2.3, "+"};
    Calculator calc = Calculator(data);
    EXPECT_EQ("Sum of 12 and 2.3 is equal to 14.3", calc.runCalculator());
}

TEST(MBB_04_05, printDifference)
{
    Data data = {12.0, 2.3, "-"};
    Calculator calc = Calculator(data);
    EXPECT_EQ("Difference of 12 and 2.3 is equal to 9.7", calc.runCalculator());
}

TEST(MBB_04_05, printProduct)
{
    Data data = {12.0, 2.3, "*"};
    Calculator calc = Calculator(data);
    EXPECT_EQ("Product of 12 and 2.3 is equal to 27.6", calc.runCalculator());
}

TEST(MBB_04_05, printQuotient)
{
    Data data = {12.0, 2.3, "/"};
    Calculator calc = Calculator(data);
    EXPECT_EQ("Quotient of 12 and 2.3 is equal to 5.21739",
              calc.runCalculator());
}

// Excercise 08
//==============

TEST(MBB_04_08, throwingError)
{
    RiceFromChessboard riceCalculator = RiceFromChessboard();
    EXPECT_THROW(riceCalculator.getNumberOfSquares(-10), std::out_of_range);
}

TEST(MBB_04_08, squaresFor0RiceGrains)
{
    RiceFromChessboard riceCalculator = RiceFromChessboard();
    EXPECT_EQ(0, riceCalculator.getNumberOfSquares(0));
}

TEST(MBB_04_08, squaresFor15RiceGrains)
{
    RiceFromChessboard riceCalculator = RiceFromChessboard();
    EXPECT_EQ(4, riceCalculator.getNumberOfSquares(15));
}

TEST(MBB_04_08, squaresFor1000RiceGrains)
{
    RiceFromChessboard riceCalculator = RiceFromChessboard();
    EXPECT_EQ(9, riceCalculator.getNumberOfSquares(1000));
}

TEST(MBB_04_08, squaresFor1000000RiceGrains)
{
    RiceFromChessboard riceCalculator = RiceFromChessboard();
    EXPECT_EQ(19, riceCalculator.getNumberOfSquares(1000000));
}

TEST(MBB_04_08, squaresFor1000000000RiceGrains)
{
    RiceFromChessboard riceCalculator = RiceFromChessboard();
    EXPECT_EQ(29, riceCalculator.getNumberOfSquares(1000000000));
}

TEST(MB_04_10, test)
{
}
