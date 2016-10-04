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

    bool hasNext() override
    {
        return _hasNext();
    }

    MOCK_METHOD0(_get, Token());
    MOCK_METHOD1(_putback, void(Token));
    MOCK_METHOD0(_hasNext, bool());

private:
    std::stringstream s;
};
}
