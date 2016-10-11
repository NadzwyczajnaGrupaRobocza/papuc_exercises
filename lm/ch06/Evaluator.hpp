#pragma once
#include <vector>
#include "TokenStream.hpp"
#include <memory>

namespace calc
{
class Evaluator
{
public:
    Evaluator(TokenStream&);
    Evaluator(TokenStream&& tsInitVal);

    double calculate();
    double expression();
    double primary();
    double term();
private:
    std::unique_ptr<TokenStream> tsVal;
    TokenStream& ts;
};
};
