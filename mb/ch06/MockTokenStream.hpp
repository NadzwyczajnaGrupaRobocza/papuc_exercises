#pragma once

#include "gmock/gmock.h"
#include "ITokenStream.hpp"
#include "Token.hpp"

class MockTokenStream : public ITokenStream
{
public:
    MOCK_METHOD0(get, Token());
    MOCK_METHOD1(putback, void(Token));
    MOCK_METHOD1(ignore, void(char));
};
