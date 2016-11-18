#include "Expression.hpp"

#include <sstream>
#include <cmath>

namespace lm
{
Expression::Expression(const std::string& inputInit) : input{inputInit}
{
}

double Expression::getResult()
{
    std::istringstream istr(input);

    double val1 = 0.0;
    double val2 = 0.0;
    char op = '\0';
    istr >> val1;
    istr >> op;
    istr >> val2;

    switch (op)
    {
    case '+': return val1 + val2;
    case '-': return val1 - val2;
    case '*': return val1 * val2;
    case '/':
        if (std::fabs(val2) < epsilon)
            throw std::runtime_error("division by zero");

        return val1 / val2;
    default: throw std::runtime_error("unknown operation");
    }
}
}
