#pragma once

#include "gtest/gtest_prod.h"
#include <string>

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

    std::string runCalculator();

private:
    double first;
    double second;
    std::string operation;
    double result;

    void validateData();
    bool operationIsNotAcceptable(const std::string&);
    bool secondIsAlmostZero();
    double calculate();
    std::string printResult();
};
