#include "NGR_04_05_01.hpp"
#include <iostream>

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
    printResult();
}

void Calculator::validateData()
{
    if(operationIsNotAcceptable(operation))
    {
        std::string reason = "Operation '" + operation + "' not acceptable ";
        throw reason;
    }
    if(operation == "/" && secondIsAlmostZero())
    {
        std::string reason = "Cannot divide by 0";
        throw reason;
    }
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

void Calculator::printResult()
{
    char cOperation = *(operation.c_str());
    switch(cOperation)
    {
        case '+':
            std::cout << "Sum of "<< first << " and " << second
                      << " is equal to " << result << std::endl;
            break;
        case '-':
            std::cout << "Difference of "<< first << " and " << second
                      << " is equal to " << result << std::endl;
            break;
        case '*':
            std::cout << "Product of "<< first << " and " << second
                      << " is equal to " << result << std::endl;
            break;
        case '/':
            std::cout << "Quotient of "<< first << " and " << second
                      << " is equal to " << result << std::endl;
            break;
        default: // ????
            std::cout << "There isn't any data to calculate!" << std::endl;
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
