#pragma once

namespace lz
{
class LedToken;
class ILedSimulationFsm
{
public:
    virtual ~ILedSimulationFsm() = default;
    virtual void parse(const LedToken&) = 0;
};
}
