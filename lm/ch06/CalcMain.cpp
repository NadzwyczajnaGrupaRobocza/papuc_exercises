#include "Evaluator.hpp"
#include "ExpressionSplitter.hpp"
#include "TokenStream.hpp"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <boost/range/algorithm.hpp>

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

        auto processSingleExpression = [](const auto& expr) {
            std::stringstream ss{expr};
            calc::TokenStream ts{ss};
            calc::Evaluator ev{ts};
            std::cout << "= " << ev.calculate() << '\n';
        };

        boost::for_each(inputExpressions, processSingleExpression);

        waitingForInput = es.hasIncompleteInput();
    }

    return 0;
}
