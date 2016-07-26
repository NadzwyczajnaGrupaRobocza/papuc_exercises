#pragma once
#include <vector>
#include "TokenStream.hpp"

namespace calc
{
class Evaluator
{
public:
    Evaluator(TokenStream&);

    double expression();
    double primary();
    double term();
private:
    TokenStream ts;
};
};
