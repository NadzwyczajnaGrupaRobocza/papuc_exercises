#pragma once

#include <sstream>

int factorial(const unsigned&);

class Token
{
public:
    Token(char);
    Token(char, double);
    
    char kind;
    double value;
};

class TokenStream
{
public:
    TokenStream();
    TokenStream(const std::string);
    
    Token get();
    void putback(Token token);

private:
    bool full;
    Token buffer;
    std::stringstream stream;
};

class Parser
{
public:
    Parser(TokenStream&);

    double expression();
    double term();
    double primary();

private:
    TokenStream& tokenStream;
    
    double calculteValue(const double& value);
};
