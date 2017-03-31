#pragma once
#include "LedTokenParser.hpp"
#include <gmock/gmock.h>

namespace lz
{
class LedTokenParserMock : public LedTokenParser
{
public:
    MOCK_METHOD1(parse, LedTokenState(const LedToken&));
};
}
