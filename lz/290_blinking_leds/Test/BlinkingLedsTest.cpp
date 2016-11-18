#include <gtest/gtest.h>

#include "LedSimulation.hpp"
#include "LedSimulationFsm.hpp"
#include "LedTokenParserFactory.hpp"
#include "Memory.hpp"

namespace lz
{
TEST(BlinkingLedsTest, part_one)
{
    ::testing::internal::CaptureStdout();
    std::stringstream input{"out (0),a\n"
                            "ld a,12\n"
                            "ld a,6\n"
                            "out (0),a\n"
                            "out (0),a\n"
                            "ld a,77\n" 
                            "out (0),a\n"};

    LedSimulation led{std::make_unique<LedSimulationFsm>(
        LedTokenParserFactory{}, std::make_shared<Memory>())};
    led.readCommands(input);
    led.run();
    EXPECT_EQ("........\n"
              ".....**.\n"
              ".....**.\n"
              ".*..**.*\n",
              ::testing::internal::GetCapturedStdout());
}
}
