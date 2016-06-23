#include "NGR_04_05_01.hpp"
#include <iostream>
#include <sstream>

Calculator::Calculator(const Data& data)
    : first(data.first),
      second(data.second),
      operation(data.operation),
      result(0.0)
{
}

void Calculator::runCalculator()
{
    validateData();
    result = calculate();
    std::cout << getResult() << std::endl;
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
    const double ReallySmallNumber = 0.00000001;
    if (second < ReallySmallNumber and second > -ReallySmallNumber)
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
        default: // ????
            std::cout << "There isn't any data to calculate!" << std::endl;
    }
    return operationResult;
}

std::string Calculator::getResult()
{
    std::stringstream result;
    char cOperation = *(operation.c_str());
    switch(cOperation)
    {
        case '+':
            result << "Sum of "<< first << " and " << second
                      << " is equal to " << result;
            break;
        case '-':
            result << "Difference of "<< first << " and " << second
                      << " is equal to " << result;
            break;
        case '*':
            result << "Product of "<< first << " and " << second
                      << " is equal to " << result;
            break;
        case '/':
            result << "Quotient of "<< first << " and " << second
                      << " is equal to " << result;
            break;
        default: // ????
            result << "There isn't any data to calculate!";
    }

    return result.str();
}
