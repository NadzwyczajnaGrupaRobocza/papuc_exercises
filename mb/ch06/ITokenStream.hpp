#pragma once

const char QUIT = 'k';
const char END_OF_EXPR = ';';
const char NUMBER = 'd';

class Token;

class ITokenStream
{
public:
    virtual ~ITokenStream() {}

    virtual Token get() = 0;
    virtual void putback(Token) = 0;
    virtual void ignore(char) = 0;
};
