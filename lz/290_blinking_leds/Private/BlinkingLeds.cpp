#include "BlinkingLeds.hpp"

#include <iostream>

#include "LedSimulation.hpp"
#include "LedSimulationFsm.hpp"
#include "LedTokenParserFactory.hpp"
#include "Memory.hpp"

namespace lz
{
int BlinkingLeds::run() try
{
    lz::LedSimulation led{std::make_unique<lz::LedSimulationFsm>(
        lz::LedTokenParserFactory{}, std::make_shared<lz::Memory>())};
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
