#pragma once

#include "gmock/gmock.h"
#include "TokenStream.hpp"

class Token;

class MockTokenStream : public ITokenStream
{
public:
    MOCK_METHOD0(get, Token());
    MOCK_METHOD1(putback, void(Token));
    MOCK_METHOD1(ignore, void(char));
};
