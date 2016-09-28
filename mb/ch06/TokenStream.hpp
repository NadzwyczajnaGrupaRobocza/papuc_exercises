#pragma once

#include <sstream>

const char QUIT = 'k';
const char END_OF_EXPR = ';';
const char NUMBER = 'd';

class ITokenStream
{
public:
    virtual ~ITokenStream() {};
    
    virtual Token get() = 0;
    virtual void putback(Token) = 0;
    virtual void ignore(char) = 0;
};

class TokenStream : public ITokenStream
{
public:
    TokenStream();
    TokenStream(const std::string);
    
    Token get();
    void putback(Token);
    void ignore(char);

private:
    bool full;
    Token buffer;
    std::stringstream stream;
};
