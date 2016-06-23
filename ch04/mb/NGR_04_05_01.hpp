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
    Calculator(const Data&);

    void runCalculator();

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

//    FRIEND_TEST(MBB_04_05, printResultTest);
    FRIEND_TEST(MBB_04_05, calculateTest);
//    FRIEND_TEST(MBB_04_05, operationIsNotAcceptable);

};
