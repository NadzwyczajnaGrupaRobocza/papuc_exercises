#pragma once

#include "LedTokenState.hpp"

namespace lz
{
class LedToken;
class LedTokenParser
{
public:
    virtual ~LedTokenParser() = default;
    virtual LedTokenState parse(const LedToken&) = 0;
};
}
