#include <gtest/gtest.h>
#include <sstream>

#include "LedSimulation.hpp"
#include "LedSimulationFsmMock.hpp"
#include "UniqueMock.hpp"

using namespace ::testing;

namespace lz
{
class LedSimulationTest : public ::Test
{
public:
    std::stringstream input{"   ld  a,23\n  out  (0),a \ncommand  val,34"};
    ut::unique_mock<LedSimulationFsmMock> fsm{};
    LedSimulation simulation{fsm.unique()};
};

TEST_F(LedSimulationTest, readAndPrint)
{
    std::stringstream expected{"ld\na,23\nout\n(0),a\ncommand\nval,34\n"};
    std::stringstream output{};
    simulation.readCommands(input);
    simulation.printCommandTokens(output);

    EXPECT_EQ(expected.str(), output.str());
}

TEST_F(LedSimulationTest, run)
{
    simulation.readCommands(input);
    EXPECT_CALL(*fsm, parse(LedToken{"ld"}));
    EXPECT_CALL(*fsm, parse(LedToken{"a,23"}));
    EXPECT_CALL(*fsm, parse(LedToken{"out"}));
    EXPECT_CALL(*fsm, parse(LedToken{"(0),a"}));
    EXPECT_CALL(*fsm, parse(LedToken{"command"}));
    EXPECT_CALL(*fsm, parse(LedToken{"val,34"}));
    simulation.run();
}
}
