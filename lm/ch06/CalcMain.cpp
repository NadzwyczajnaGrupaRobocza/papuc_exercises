#include <iostream>
#include <sstream>
#include <algorithm>
#include "Evaluator.hpp"
#include "TokenStream.hpp"
#include "ExpressionSplitter.hpp"

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

    bool continueProgram{true};
    bool waitingForInput{false};
    calc::ExpressionSplitter es;
    while (continueProgram)
    {
        if (waitingForInput)
        {
            std::cout << "> ";
        }
        else
        {
            std::cout << ">>> ";
        }

        std::string line;
        std::getline(std::cin, line);


        auto inVec = es.split(line);

        std::for_each(inVec.begin(), inVec.end(),
                      [](const auto& expr)
                      {
                          std::stringstream ss{expr};
                          calc::TokenStream ts{ss};
                          calc::Evaluator ev{ts};
                          std::cout << "= " << ev.calculate() << '\n';
                       });

        if (es.hasIncompleteInput())
        {
            waitingForInput = true;
        }
        else
        {
            waitingForInput = false;
        }

    }

    return 0;
}
