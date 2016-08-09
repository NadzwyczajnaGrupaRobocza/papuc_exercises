#include "Evaluator.hpp"

#include <stdexcept>

namespace calc
{
Evaluator::Evaluator(TokenStream& tsInit) : ts{tsInit}
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
        case ';':
            return left;
        default: ts.putback(t); return left;
        }
    }
}

double Evaluator::term()
{
    double left = primary();
    Token t = ts.get();

    while (true)
    {
        switch (t.typeId)
        {
        case '*':
            left *= primary();
            t = ts.get();
            break;
        case '/':
        {
            double d = primary();
            if (d == 0.0)
            {
                throw std::runtime_error("division by zero");
            }
            left /= d;
            t = ts.get();
            break;
        }
        default: ts.putback(t); return left;
        }
    }
}

double Evaluator::primary()
{
    Token t = ts.get();
    switch (t.typeId)
    {
    case '(':
    {
        double d = expression();
        t = ts.get();
        if (t.typeId != ')')
        {
            throw std::runtime_error("expected ')' missing");
        }
        return d;
    }
    case '8': return t.value;
    default: throw std::runtime_error("expected primary expression");
    }
}
}
