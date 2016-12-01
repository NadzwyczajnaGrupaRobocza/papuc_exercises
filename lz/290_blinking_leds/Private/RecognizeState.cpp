#include "RecognizeState.hpp"
#include "LedToken.hpp"
#include <iostream>

namespace lz
{
RecognizeState::RecognizeState()
    : commands{{"ld", LedTokenState::LedLdCommand},
               {"out", LedTokenState::LedOutCommand}}
{
}

LedTokenState RecognizeState::parse(const LedToken& token)
{
    try
    {
        return commands.at(token.str());
    }
    catch (std::out_of_range&)
    {
        std::cerr << "Command is not recognized: " << token.str() << ".\n";
        throw;
    }
}
}
