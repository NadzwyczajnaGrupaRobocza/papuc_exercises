#include "Expression.hpp"

#include <cmath>
#include <sstream>

#include <iostream>

namespace lm
{
Expression::Expression(const std::string& inputInit) : input{inputInit}
{
    std::cout << "contructor" << std::endl;
}

double Expression::getResult()
{        std::cout << "get result " << input << std::endl;
    std::istringstream istr(input);
    std::cout << "after istr" << std::endl;

            std::cout << "val init" << std::endl;
    double val1 = 0.0;
    double val2 = 0.0;
    char op = '\0';
    std::cout << "before >> " << istr.str() << std::endl;
    istr >> val1;
    std::cout << "after val1 >> " << val1 << std::endl;
    istr >> op;
    std::cout << "after op >> " << op << std::endl;
    istr >> val2;
    std::cout << "after val2 >> " << val2 << std::endl;
    switch (op)
    {
    case '+': std::cout << "1" << std::endl; return val1 + val2;
    case '-': std::cout << "2" << std::endl; return val1 - val2;
    case '*': std::cout << "3" << std::endl; return val1 * val2;
    case '/':

        std::cout << "4" << std::endl;
        if (std::fabs(val2) < epsilon)
        {
            std::cout << "5" << std::endl;
            throw std::runtime_error("division by zero");
        }

        std::cout << "6" << std::endl;
        return val1 / val2;
    default:
        std::cout << "7" << std::endl;
        throw std::runtime_error("unknown operation");
    }
}
}
