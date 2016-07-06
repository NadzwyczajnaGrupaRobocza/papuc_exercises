#pragma once
#include <iostream>

using namespace std;

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


