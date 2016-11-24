#pragma once
#include <memory>
#include <unordered_map>

#include "EnumClassHash.hpp"
#include "ILedSimulationFsm.hpp"
#include "LedTokenParser.hpp"
#include "LedTokenState.hpp"

namespace lz
{
class IMemory;
class LedTokenParserFactory;
class LedSimulationFsm : public ILedSimulationFsm
{
public:
    LedSimulationFsm(const LedTokenParserFactory&, std::shared_ptr<IMemory>);
    void parse(const LedToken&) override;

private:
    std::shared_ptr<IMemory> memory;
    std::unordered_map<LedTokenState, std::unique_ptr<LedTokenParser>,
                       utils::EnumClassHash>
        fsm;
    LedTokenParser* currentParser;
};
}
