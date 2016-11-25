#include "LedSimulationFsm.hpp"

#include <iostream>

#include "LedLdState.hpp"
#include "RecognizeState.hpp"

namespace lz
{
LedSimulationFsm::LedSimulationFsm(
    std::unique_ptr<LedTokenParser> recognizeState,
    std::unique_ptr<LedTokenParser> ledLdState,
    std::unique_ptr<LedTokenParser> ledOutState)
{
    fsm.emplace(LedTokenState::Recognize, std::move(recognizeState));
    fsm.emplace(LedTokenState::LedLdCommand, std::move(ledLdState));
    fsm.emplace(LedTokenState::LedOutCommand, std::move(ledOutState));
    currentParser = fsm.at(LedTokenState::Recognize).get();
}

void LedSimulationFsm::parse(const LedToken& token)
{
    auto newState = currentParser->parse(token);
    try
    {
        currentParser = fsm.at(newState).get();
    }
    catch (std::out_of_range&)
    {
        std::cerr << "New state: " << newState << " not found!\n";
        throw;
    }
}
}
