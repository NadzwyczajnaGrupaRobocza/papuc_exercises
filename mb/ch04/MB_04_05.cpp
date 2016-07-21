#include "NGR_04_05_01.hpp"
#include <iostream>
#include <sstream>
#include <cmath>

Calculator::Calculator(const Data& data)
    : first(data.first),
      second(data.second),
      operation(data.operation),
      result(0.0)
{
}

std::string Calculator::runCalculator()
{
    validateData();
    result = calculate();
    return printResult();
}

void Calculator::validateData()
{
    if(operation == "")
    {
        std::string reason = "Wrong input data";
        throw reason;
    }
    if(operationIsNotAcceptable(operation))
    {
        std::string reason = "Operation '" + operation + "' not acceptable";
        throw reason;
    }
    if(operation == "/" && secondIsAlmostZero())
    {
        std::string reason = "Cannot divide by 0";
        throw reason;
    }
}

bool Calculator::operationIsNotAcceptable(const std::string& aOperation)
{
    bool operationNotAcceptable = false;
    if(aOperation != "+" and
       aOperation != "-" and
       aOperation != "*" and
       aOperation != "/")
    {
        operationNotAcceptable = true;
    }

    return operationNotAcceptable;
}

bool Calculator::secondIsAlmostZero()
{
    constexpr double ReallySmallNumber = 0.00000001;
    if (second < std::abs(ReallySmallNumber))
    {
        return true;
    }
    else
    {
        return false;
    }
}

double Calculator::calculate()
{
    double operationResult = 0.0;
    char cOperation = *(operation.c_str());
    switch(cOperation)
    {
        case '+':
            operationResult = first + second;
            break;
        case '-':
            operationResult = first - second;
            break;
        case '*':
            operationResult = first * second;
            break;
        case '/':
            operationResult = first / second;
            break;
        default:
            std::string error = "Unexpected error!";
            throw error;
            break;
    }
    return operationResult;
}

std::string Calculator::printResult()
{
    std::stringstream output;
    char cOperation = *(operation.c_str());
    switch(cOperation)
    {
        case '+':
            output << "Sum of " << first << " and " << second
                      << " is equal to " << result;
            break;
        case '-':
            output << "Difference of " << first << " and " << second
                      << " is equal to " << result;
            break;
        case '*':
            output << "Product of " << first << " and " << second
                      << " is equal to " << result;
            break;
        case '/':
            output << "Quotient of " << first << " and " << second
                      << " is equal to " << result;
            break;
        default:
            std::string error = "Unexpected error!";
            throw error;
            break;
    }

    return output.str();
}
