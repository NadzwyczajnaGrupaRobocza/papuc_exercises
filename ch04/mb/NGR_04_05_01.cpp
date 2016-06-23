#include "NGR_04_05_01.hpp"
#include <iostream>

Calculator::Calculator() : first(0.0),
                           second(0.0),
                           operation(""),
                           result(0.0)
{
}

Calculator::Calculator(const double& aFirst,
                       const double& aSecond,
                       const std::string& aOperation)
    : first(aFirst),
    second(aSecond),
    operation(aOperation),
    result(0.0)
{
}

void Calculator::runCalculator(const Data& data)
{
    gatherData(data);
    result = calculate();
    printResult();
}

void Calculator::gatherData(const Data& data)
{
    first = data.first;
    second = data.second;
    operation = data.operation;
    if(operationIsNotAcceptable(operation))
    {
        std::string reason = "Operation '" + operation + "' not acceptable ";
        throw reason;
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
            if(second == 0.0)
            {
                std::string reason = "Cannot divide by 0";
                throw reason;
            }
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
