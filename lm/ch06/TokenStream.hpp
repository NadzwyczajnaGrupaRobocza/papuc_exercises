#pragma once

#include "Token.hpp"
#include <iosfwd>
#include <memory>
#include <sstream>

namespace calc
{
class TokenStream
{
public:
    TokenStream(std::istream&);
    TokenStream(std::stringstream&&);

    TokenStream(TokenStream&& ) = default;
    virtual ~TokenStream() = default;

    virtual Token get();
    virtual void putback(Token);
    virtual bool hasNext();

private:
    Token getTokenFromStream();
    std::unique_ptr<std::istream> inputVal;
    std::istream& input;
    Token buffer;
    bool bufferFull;
};
}
