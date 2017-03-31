#include "BlinkingLeds.hpp"

#include <iostream>

#include "LedLdState.hpp"
#include "LedOutState.hpp"
#include "LedSimulation.hpp"
#include "LedSimulationFsm.hpp"
#include "Memory.hpp"
#include "RecognizeState.hpp"

namespace lz
{
int BlinkingLeds::run() try
{
    auto memory = std::make_shared<Memory>();

    auto fsm = std::make_unique<lz::LedSimulationFsm>(
        std::make_unique<RecognizeState>(),
        std::make_unique<LedLdState>(memory),
        std::make_unique<LedOutState>(memory));

    lz::LedSimulation led{std::move(fsm)};
    led.readCommands(std::cin);
    led.run();
    return 0;
}
catch (std::exception& ex)
{
    std::cerr << "Ups... Something went wrong.(" << ex.what() << ")\n";
    return -1;
}
}
