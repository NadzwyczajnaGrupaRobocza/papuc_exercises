#pragma once
#include <memory>

#include "LedTokenParser.hpp"

namespace lz
{
class IMemory;
class LedOutState : public LedTokenParser
{
public:
    LedOutState(std::shared_ptr<const IMemory>);
    LedTokenState parse(const LedToken&) override;

private:
    std::shared_ptr<const IMemory> memory;
};
}
