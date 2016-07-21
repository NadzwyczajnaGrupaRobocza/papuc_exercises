#pragma once

namespace calc
{
class Token
{
public:
    Token(char);
    Token(char, double);

    char op;
    double value;
};
}
