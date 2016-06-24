#pragma once

#include <string>
#include "gtest/gtest_prod.h"

//class UtCalculator;

struct Data
{
    double first;
    double second;
    std::string operation;
};

class Calculator
{
public:
    Calculator(const Data&);

    void runCalculator();

//    friend class UtCalculator;

private:
    double first;
    double second;
    std::string operation;
    double result;

    void validateData();
    bool operationIsNotAcceptable(const std::string&);
    bool secondIsAlmostZero();
    double calculate();
    std::string getResult();

    FRIEND_TEST(MBB_04_05, throwingErrorAfterGettingEmptyData);
    FRIEND_TEST(MBB_04_05, throwingErrorAfterGettingWrongOperator);
    FRIEND_TEST(MBB_04_05, throwingErrorAfterDividingByZero);
    FRIEND_TEST(MBB_04_05, acceptOperation);
    FRIEND_TEST(MBB_04_05, rejectOperation);
    FRIEND_TEST(MBB_04_05, secondIsAlmostZero);
    FRIEND_TEST(MBB_04_05, secondIsNotAlmostZero);
    FRIEND_TEST(MBB_04_05, calculateSum);
    FRIEND_TEST(MBB_04_05, calculateDifference);
    FRIEND_TEST(MBB_04_05, calculateProduct);
    FRIEND_TEST(MBB_04_05, calculateQuotient);
    FRIEND_TEST(MBB_04_05, printSum);
    FRIEND_TEST(MBB_04_05, printDifference);
    FRIEND_TEST(MBB_04_05, printProduct);
    FRIEND_TEST(MBB_04_05, printQuotient);
};
