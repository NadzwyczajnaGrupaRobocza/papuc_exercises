#include "Evaluator.hpp"

namespace calc
{
Evaluator::Evaluator(TokenStream& tsInit)
    : ts{tsInit}
{
}

double Evaluator::expression()
{
    double left = term();
    Token t = ts.get();

    while (true)
    {
        switch (t.typeId)
        {
        case '+':
            left += term();
            t = ts.get();
            break;
        case '-':
            left -= term();
            t = ts.get();
            break;
        default:
            ts.putback(t);
            return left;
        }
    }
}


}
