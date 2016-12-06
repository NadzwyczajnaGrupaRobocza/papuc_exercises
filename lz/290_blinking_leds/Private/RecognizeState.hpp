#pragma once
#include <unordered_map>

#include "LedTokenParser.hpp"

namespace lz
{
class RecognizeState : public LedTokenParser
{
public:
    RecognizeState();
    LedTokenState parse(const LedToken& token) override;

private:
    const std::unordered_map<std::string, LedTokenState> commands;
};
}
