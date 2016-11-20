#include "ch_04_05.hpp"
#include <cmath>
#include <iostream>
#include <limits>

double calculator::compute(double arg1, double arg2)
{

    switch (action)
    {
    case '+': return arg1 + arg2; break;
    case '-': return arg1 - arg2; break;
    case '*': return arg1 * arg2; break;
    case ':':
        if (std::fabs(arg2) < std::numeric_limits<double>::epsilon())
        {
            cout << "Bad arguments!!!!";
            break;
        }
        else
            return arg1 / arg2;
        break;
    default: return 0.0;
    }
    return 0.0;
}
