#include "NGR_04_05_01.hpp"
#include <iostream>

int main()
{
    std::cout << "=== Exercise 05 from Chapter 04 ===" << std::endl;

    Calculator calculator = Calculator();
    try
    {
        calculator.runCalculator();
    }
    catch(std::string error)
    {
        std::cerr << "Error: " << error << "\n";
        return 1;
    }
    return 0;
}
