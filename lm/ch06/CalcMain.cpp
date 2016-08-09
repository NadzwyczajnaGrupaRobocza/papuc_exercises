#include <iostream>
#include "Evaluator.hpp"
#include "TokenStream.hpp"

int main(int /*argv*/, char** /*argc*/)
{
    std::cout << "Please input expression:\n";
    calc::TokenStream tokenStream{std::cin};
    calc::Evaluator ev{tokenStream};
    auto result = ev.expression();
    std::cout << "result: " << result << '\n';

    return 0;
}
