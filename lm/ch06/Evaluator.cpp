#include "Evaluator.hpp"

#include <cmath>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <utility>

namespace
{

long long factorial_impl(long long n)
{
    if (n < 2)
        return 1;
    return n * factorial_impl(n - 1);
}

double factorial(double n)
{
    auto N = static_cast<long long>(n);
    return static_cast<double>(factorial_impl(N));
}
}

namespace calc
{

Evaluator::Evaluator(TokenStream& tsInit) : tsVal{nullptr}, ts{tsInit}
{
}

Evaluator::Evaluator(TokenStream&& tsInitVal)
    : tsVal{std::make_unique<TokenStream>(std::move(tsInitVal))}, ts{*tsVal}
{
}

double Evaluator::calculate()
{
    return expression();
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
        case '%':
        {
            double d = primary();
            if (d == 0.0)
            {
                throw std::runtime_error("division by zero");
            }
            left = std::fmod(left, d);
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
    double retVal;
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
        retVal = d;
        break;
    }
    case '{':
    {
        double d = expression();
        t = ts.get();
        if (t.typeId != '}')
        {
            throw std::runtime_error("expected '}' missing");
        }
        retVal = d;
        break;
    }
    case '-':
    {
        double d = expression();
        retVal = -d;
        break;
    }
    case '+':
    {
        double d = expression();
        retVal = +d;
        break;
    }
    case '8':
    {
        retVal = t.value;
        break;
    }
    default: { throw std::runtime_error("expected primary expression");
    }
    }

    t = ts.get();
    if (t.typeId == '!')
    {
        return factorial(retVal);
    }
    else
    {
        ts.putback(t);
        return retVal;
    }
}
}
