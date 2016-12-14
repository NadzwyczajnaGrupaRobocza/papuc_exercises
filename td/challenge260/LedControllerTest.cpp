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

TEST_F(LedControllerTest, RlcaShouldRotateRegisterALeft)
{
    controller.runProgram(
        Instructions{{InstructionType::LdA, 136},
                     createInstructionWithZeroValue(InstructionType::Rlca),
                     createInstructionWithZeroValue(InstructionType::OutA)});

    EXPECT_THAT(stream.str(), Eq("...*...*\n"));
}

TEST_F(LedControllerTest, RlcaShouldRotateRegisterARight)
{
    controller.runProgram(
        Instructions{{InstructionType::LdA, 9},
                     createInstructionWithZeroValue(InstructionType::Rrca),
                     createInstructionWithZeroValue(InstructionType::OutA)});

    EXPECT_THAT(stream.str(), Eq("*....*..\n"));
}

TEST_F(LedControllerTest, ShouldJumpBackwardsUntilReach0From0)
{
    controller.runProgram(Instructions{{InstructionType::Label, 0},
                                       {InstructionType::OutA, 0},
                                       {InstructionType::Djnz, 0}});

    std::string expectedString;
    for (int i = 0; i < 256; ++i)
    {
        expectedString += "........\n";
    }
    EXPECT_THAT(stream.str(), Eq(expectedString));
}

TEST_F(LedControllerTest, ShouldJumpBackwardsUntilReach0From1)
{
    controller.runProgram(Instructions{{InstructionType::LdB, 1},
                                       {InstructionType::Label, 0},
                                       {InstructionType::OutA, 0},
                                       {InstructionType::Djnz, 0}});

    std::string expectedString{"........\n"};
    EXPECT_THAT(stream.str(), Eq(expectedString));
}

TEST_F(LedControllerTest, DjnzShouldJumpToSecondLabel)
{
    controller.runProgram(Instructions{{InstructionType::LdB, 2},
                                       {InstructionType::Label, 0},
                                       {InstructionType::OutA, 0},
                                       {InstructionType::Label, 1},
                                       {InstructionType::OutA, 0},
                                       {InstructionType::Djnz, 1}});

    std::string expectedString;
    for (int i = 0; i < 3; ++i)
    {
        expectedString += "........\n";
    }
    EXPECT_THAT(stream.str(), Eq(expectedString));
}

TEST_F(LedControllerTest, DjnzShouldJumpToFirstLabel)
{
    controller.runProgram(Instructions{{InstructionType::LdB, 2},
                                       {InstructionType::Label, 0},
                                       {InstructionType::OutA, 0},
                                       {InstructionType::Label, 1},
                                       {InstructionType::OutA, 0},
                                       {InstructionType::Djnz, 0}});

    std::string expectedString;
    for (int i = 0; i < 4; ++i)
    {
        expectedString += "........\n";
    }
    EXPECT_THAT(stream.str(), Eq(expectedString));
}
