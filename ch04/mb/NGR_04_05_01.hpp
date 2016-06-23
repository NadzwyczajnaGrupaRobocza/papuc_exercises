#pragma once

#include <string>
#include "gtest/gtest_prod.h"

struct Data
{
    double first;
    double second;
    std::string operation;
};

class Calculator
{
public:
    Calculator();
    Calculator(const double& aFirst,
               const double& aSecond,
               const std::string& aOperation);

    void runCalculator(const Data&);

private:
    double first;
    double second;
    std::string operation;
    double result;

    void gatherData(const Data&);
    void printResult();
    double calculate();
    bool operationIsNotAcceptable(const std::string&);

//    FRIEND_TEST(MBB_04_05, printResultTest);
    FRIEND_TEST(MBB_04_05, calculateTest);
//    FRIEND_TEST(MBB_04_05, operationIsNotAcceptable);

};
