#include "Evaluator.hpp"
#include "ExpressionSplitter.hpp"
#include "TokenStream.hpp"
#include <algorithm>
#include <boost/range/algorithm.hpp>
#include <iostream>
#include <sstream>

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

        auto inputExpressions = es.split(line);

        auto evaluateSingleExpression = [](const auto& expr) {
            std::stringstream ss{expr};
            calc::TokenStream ts{ss};
            calc::Evaluator ev{ts};
            std::cout << "= " << ev.calculate() << '\n';
        };

        boost::for_each(inputExpressions, evaluateSingleExpression);

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
