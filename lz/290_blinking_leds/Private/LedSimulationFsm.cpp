#include "LedSimulationFsm.hpp"

#include <iostream>

#include "LedLdState.hpp"
#include "LedTokenParserFactory.hpp"
#include "IMemory.hpp"
#include "RecognizeState.hpp"

namespace lz
{
LedSimulationFsm::LedSimulationFsm(const LedTokenParserFactory& factory,
                                   std::shared_ptr<IMemory> mem)
    : memory{mem}
{
    fsm.emplace(LedTokenState::Recognize, factory.createRecognizeState());
    fsm.emplace(LedTokenState::LedLdCommand, factory.createLedLdState(memory));
    fsm.emplace(LedTokenState::LedOutCommand,
                factory.createLedOutState(memory));
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
