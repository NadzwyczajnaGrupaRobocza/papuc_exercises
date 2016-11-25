#pragma once
#include <memory>
#include <unordered_map>

#include "ILedSimulationFsm.hpp"
#include "LedTokenParser.hpp"
#include "LedTokenState.hpp"

namespace lz
{
class LedSimulationFsm : public ILedSimulationFsm
{
public:
    LedSimulationFsm(std::unique_ptr<LedTokenParser> recognizeState,
                     std::unique_ptr<LedTokenParser> ledLdState,
                     std::unique_ptr<LedTokenParser> ledOutState);
    void parse(const LedToken&) override;

private:
    std::unordered_map<LedTokenState, std::unique_ptr<LedTokenParser>> fsm;
    LedTokenParser* currentParser;
};
}
