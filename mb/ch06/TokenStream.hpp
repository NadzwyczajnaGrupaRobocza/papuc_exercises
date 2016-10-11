#pragma once

#include <sstream>
#include "ITokenStream.hpp"
#include "Token.hpp"

class TokenStream : public ITokenStream
{
public:
    TokenStream();
    TokenStream(const std::string);
    
    Token get() override;
    void putback(Token) override;
    void ignore(char) override;

private:
    bool full;
    Token buffer;
    std::stringstream stream;
};
