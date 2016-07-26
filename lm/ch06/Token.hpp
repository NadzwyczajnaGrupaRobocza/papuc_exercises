#pragma once

namespace calc
{
class Token
{
public:
    Token();
    Token(char);
    Token(char, double);

    char typeId;
    double value;
};
}
