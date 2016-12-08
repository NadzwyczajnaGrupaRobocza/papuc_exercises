#pragma once
#include <gmock/gmock.h>
#include "ILedSimulationFsm.hpp"

namespace lz
{
class LedToken;
class LedSimulationFsmMock : public ILedSimulationFsm
{
public:
    MOCK_METHOD1(parse, void(const LedToken& token));
};
}
