#include <vector>
#include "gtest/gtest.h"
#include "NGR_04_02_01.hpp"
#include "NGR_04_03_01.hpp"
#include "NGR_04_05_01.hpp"

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
    EXPECT_EQ(13.1, getMediana(someData2));
}


TEST(MBB_04_02, getMedianaFromEvenVector)
{
    EXPECT_EQ(18.225, getMediana(someData1));
}

// Excercise 03
//==============
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
//==============

//~ class UtCalculator : public ::testing::Test
//~ {
//~ public:
    //~ bool testOperationIsNotAcceptable(Calculator& calc,
                                                //~ std::string operation)
    //~ {
        //~ return calc.operationIsNotAcceptable(operation);
    //~ }
//~
    //~ bool testSecondIsAlmostZero(Calculator* calc)
    //~ {
        //~ return calc-> secondIsAlmostZero();
    //~ }
//~
    //~ double testCalculate(Calculator* calc)
    //~ {
        //~ return calc-> calculate();
    //~ }
//~
    //~ std::string testGetResult(Calculator* calc)
    //~ {
        //~ return calc-> getResult();
    //~ }
//~ };

TEST(MBB_04_05, throwingErrorAfterGettingEmptyData)
{
    Data data = {0, 0, ""};
    Calculator calc = Calculator(data);
    EXPECT_THROW(calc.validateData(), std::string);
}

TEST(MBB_04_05, throwingErrorAfterGettingWrongOperator)
{
    Data data = {12.0, 3.0, "%"};
    Calculator calc = Calculator(data);
    EXPECT_THROW(calc.validateData(), std::string);
}

TEST(MBB_04_05, throwingErrorAfterDividingByZero)
{
    Data data = {12.0, 0, "/"};
    Calculator calc = Calculator(data);
    EXPECT_THROW(calc.validateData(), std::string);
}

TEST(MBB_04_05, acceptOperation)
{

    Data data = {0.0, 0.0, ""};
    Calculator calc = Calculator(data);
    EXPECT_FALSE(calc.operationIsNotAcceptable("+"));
}

TEST(MBB_04_05, rejectOperation)
{
    Data data = {0.0, 0.0, ""};
    Calculator calc = Calculator(data);
    EXPECT_TRUE(calc.operationIsNotAcceptable("%"));
}

TEST(MBB_04_05, secondIsAlmostZero)
{
    Data data = {0.0, 0.000000009, ""};
    Calculator calc = Calculator(data);
    EXPECT_TRUE(calc.secondIsAlmostZero());
}

TEST(MBB_04_05, secondIsNotAlmostZero)
{
    Data data = {0.0, 0.00000002, ""};
    Calculator calc = Calculator(data);
    EXPECT_FALSE(calc.secondIsAlmostZero());
}

TEST(MBB_04_05, calculateSum)
{
    Data data = {12.0, 2.3, "+"};
    Calculator calc = Calculator(data);
    EXPECT_EQ(14.3, calc.calculate());
}

TEST(MBB_04_05, calculateDifference)
{
    Data data = {12.0, 2.3, "-"};
    Calculator calc = Calculator(data);
    EXPECT_EQ(9.7, calc.calculate());
}

TEST(MBB_04_05, calculateProduct)
{
    Data data = {12.0, 2.3, "*"};
    Calculator calc = Calculator(data);
    EXPECT_EQ(12*2.3, calc.calculate());
}

TEST(MBB_04_05, calculateQuotient)
{
    Data data = {12.0, 2.3, "/"};
    Calculator calc = Calculator(data);
    EXPECT_EQ(12/2.3, calc.calculate());
}

TEST(MBB_04_05, printSum)
{
    Data data = {12.0, 2.3, "+"};
    Calculator calc = Calculator(data);
    calc.result = calc.calculate();
    EXPECT_EQ("Sum of 12 and 2.3 is equal to 14.3",
              calc.getResult());
}

TEST(MBB_04_05, printDifference)
{
    Data data = {12.0, 2.3, "-"};
    Calculator calc = Calculator(data);
    calc.result = calc.calculate();
    EXPECT_EQ("Difference of 12 and 2.3 is equal to 9.7",
              calc.getResult());
}

TEST(MBB_04_05, printProduct)
{
    Data data = {12.0, 2.3, "*"};
    Calculator calc = Calculator(data);
    calc.result = calc.calculate();
    EXPECT_EQ("Product of 12 and 2.3 is equal to 27.6",
              calc.getResult());
}

TEST(MBB_04_05, printQuotient)
{
    Data data = {12.0, 2.3, "/"};
    Calculator calc = Calculator(data);
    calc.result = calc.calculate();
    EXPECT_EQ("Quotient of 12 and 2.3 is equal to 5.21739",
              calc.getResult());
}

TEST(MBB_04_05, runCalculator)
{
    Data data = {12.0, 2.3, "+"};
    Calculator calc = Calculator(data);
    calc.runCalculator();
    EXPECT_TRUE(true);
}

//~ TEST(MBB_04_05, tempTest)
//~ {
    //~ Data data = {12.0, 0, "/"};
    //~ Calculator calc = Calculator(data);
    //~ UtCalculator temp;
    //~ EXPECT_TRUE(temp.testOperationIsNotAcceptable(calc, "+"));
//~ }
