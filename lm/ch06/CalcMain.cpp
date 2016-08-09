#include <iostream>
#include <sstream>
#include "Evaluator.hpp"
#include "TokenStream.hpp"

int main(int argc, char** argv)
{
    if (argc > 1)
    {
        for (auto i = 1; i < argc; i++)
        {
            std::stringstream input(argv[i]);
            calc::TokenStream ts{input};

            std::cout << i << ": " << calc::Evaluator{ts}.expression() << '\n';
        }
        return 0;
    }

    calc::TokenStream ts{std::cin};
    do
    {
        std::cout << "> ";
        calc::Evaluator ev{ts};
        auto result = ev.expression();
        std::cout << "result: " << result << '\n';
    } while (true);

    return 0;
}
