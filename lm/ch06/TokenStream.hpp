#pragma once

#include "Token.hpp"
#include <iosfwd>

namespace calc
{
class TokenStream
{
public:
    TokenStream(std::istream&);
    virtual ~TokenStream() = default;

    virtual Token get();
    virtual void putback(Token);

private:
    Token getTokenFromStream();
    std::istream& input;
    Token buffer;
    bool bufferFull;
};
}
