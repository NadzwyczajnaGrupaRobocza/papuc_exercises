#include "gmock/gmock.h"

#include "LedController.hpp"

static constexpr Instruction
createInstructionWithZeroValue(InstructionType type)
{
    return {type, 0};
}

using namespace ::testing;

class LedControllerTest : public Test
{
public:
    std::stringstream stream;
    LedController controller{stream};
};

TEST_F(LedControllerTest, OutInstructionShouldPrintLedState)
{
    controller.runProgram(
        Instructions{createInstructionWithZeroValue(InstructionType::OutA)});

    EXPECT_THAT(stream.str(), Eq("........\n"));
}

TEST_F(LedControllerTest, LdInstructionShouldNotPrintLedState)
{
    controller.runProgram(
        Instructions{createInstructionWithZeroValue(InstructionType::LdA)});

    EXPECT_THAT(stream.str(), Eq(""));
}

TEST_F(LedControllerTest, ShouldAcceptNoInstructions)
{
    controller.runProgram(Instructions{});

    EXPECT_THAT(stream.str(), Eq(""));
}

TEST_F(LedControllerTest, OutInstructionShouldPrintLedStateAfterChangeByLd)
{
    controller.runProgram(
        Instructions{{InstructionType::LdA, 255},
                     createInstructionWithZeroValue(InstructionType::OutA)});

    EXPECT_THAT(stream.str(), Eq("********\n"));
}

TEST_F(LedControllerTest,
       OutInstructionShouldPrintLedStateAfterChangeByLdToSomeValue)
{
    controller.runProgram(
        Instructions{{InstructionType::LdA, 42},
                     createInstructionWithZeroValue(InstructionType::OutA)});

    EXPECT_THAT(stream.str(), Eq("..*.*.*.\n"));
}