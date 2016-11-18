#pragma once
#include "LedTokenParser.hpp"
#include <unordered_map>

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
