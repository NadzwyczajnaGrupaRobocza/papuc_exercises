#pragma once

#include "gmock/gmock.h"
#include "TokenStream.hpp"
#include <sstream>

namespace calc
{
class MockTokenStream : public TokenStream
{
public:
    MockTokenStream()
        : TokenStream(s)
    {
    }

    Token get() override
    {
        return _get();
    }

    void putback(Token t) override
    {
        _putback(t);
    }

    MOCK_METHOD0(_get, Token());
    MOCK_METHOD1(_putback, void(Token));

private:
    std::stringstream s;
};
}
