#pragma once
#include <iostream>

class calculator
{
public:
    calculator(const char& act)
    {
        action = act;
    }

    double compute(double arg1, double arg2);

private:
    char action;
};
