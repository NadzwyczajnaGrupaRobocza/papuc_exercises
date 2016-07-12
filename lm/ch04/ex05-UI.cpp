#include "Expression.hpp"
#include <iostream>

int main()
{
    std::cout << "Please input expression of the form \"double op double\"\n";

    try
    {
        while (true)
        {
            std::string line;
            std::getline(std::cin, line);
            std::cout << "Result is: " << lm::Expression(line).getResult()
                      << "\n";
            std::cout
                << "Please input expression of the form \"double op double\"\n";
        }
    }
    catch (...)
    {
        std::cout << "Caught some exception, exiting.\n";
    }
    return 0;
}
