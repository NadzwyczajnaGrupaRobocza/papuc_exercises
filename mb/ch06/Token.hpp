#pragma once

class Token
{
public:
    Token(char);
    Token(char, double);

    char kind;
    double value;
};
