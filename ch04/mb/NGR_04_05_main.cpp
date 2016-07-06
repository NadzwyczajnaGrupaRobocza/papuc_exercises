#include "NGR_04_05_01.hpp"
#include <iostream>

int main()
{
    std::cout << "=== Exercise 05 from Chapter 04 ===" << std::endl;

    Data data = {0.0, 0.0, ""};
    std::cout << "Type 'number' 'number' 'operation'" << std::endl;
    std::cin >> data.first >> data.second >> data.operation;

    Calculator calculator(data);
    try
    {
        calculator.runCalculator();
    }
    catch(const std::string& error)
    {
        std::cerr << "Error: " << error << "\n";
        return 1;
    }
    return 0;
}
