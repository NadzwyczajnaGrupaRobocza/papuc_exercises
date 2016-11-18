#pragma once
#include <deque>
#include <iosfwd>
#include <memory>

#include "LedToken.hpp"

namespace lz
{
class ILedSimulationFsm;
class LedSimulation
{
public:
    LedSimulation(std::unique_ptr<ILedSimulationFsm>);
    void readCommands(std::istream& input);
    void run();
    void printCommandTokens(std::ostream& output) const;

private:
    std::deque<LedToken> tokens;
    std::unique_ptr<ILedSimulationFsm> fsm;
};
}
