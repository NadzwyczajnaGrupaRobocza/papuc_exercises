#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "InstructionConverter.hpp"
#include "LedBlinker.hpp"
#include "InstructionParser.hpp"
//#include "LedCommon.hpp"

using testing::InSequence;
using testing::AtLeast;
using testing::Return;

using namespace mb_led;

TEST(MBB_Led_Converter, parseSimpleInstructions)
{
    InstructionParser ip{};
    const std::vector<std::string> input{
        " ld a,10  ",
        "    ",
        "   out (0),a ",
        " rlca",
        " aaaaaa",
        " rrca"};
    const std::vector<std::string> expectedOut{
        "ld a,10",
        "out (0),a",
        "rlca",
        "rrca"};

    EXPECT_EQ(ip.getFlatInstructions(input), expectedOut);
}

TEST(MBB_Led_Converter, parseInstructionsWithoutLabel)
{
    InstructionParser ip{};
    const std::vector<std::string> input{
        " ld a,10",
        " ld b,3"};
    const std::vector<std::string> expectedOut{
        "ld a,10"};

    EXPECT_EQ(ip.getFlatInstructions(input), expectedOut);
}

TEST(MBB_Led_Converter, parseInstructionWithSimpleLabel)
{
    InstructionParser ip{};
    const std::vector<std::string> input{
        " ld a,10",
        " ld b,2",
        " label:",
        "   rlca",
        " djnz label"};
    const std::vector<std::string> expectedOut{
        "ld a,10",
        "rlca",
        "rlca"};

    EXPECT_EQ(ip.getFlatInstructions(input), expectedOut);
}

TEST(MBB_Led_Converter, parseComplicatedInstructions)
{
    InstructionParser ip{};
    const std::vector<std::string> input{
        " ld a,10",
        " out (0),a",
        " ld b,3",
        " ld a,101",
        " out (0),a",
        " label:",
        "   rlca",
        "   out (0),a",
        "   ld a,20",
        "   out (0),a",
        " djnz label",
        " ld a,111",
        " out (0),a"};
    const std::vector<std::string> expectedOut{
        "ld a,10",
        "out (0),a",
        "rlca",
        "out (0),a",
        "ld a,20",
        "out (0),a",
        "rlca",
        "out (0),a",
        "ld a,20",
        "out (0),a",
        "rlca",
        "out (0),a",
        "ld a,20",
        "out (0),a",
        "ld a,101",
        "out (0),a",
        "ld a,111",
        "out (0),a"};

    EXPECT_EQ(ip.getFlatInstructions(input), expectedOut);
}

TEST(MBB_Led_Converter, convertingSingleInstruction)
{
    const std::vector<std::string> input{
        "ld a,10",
        "out (0),a"};

    const std::vector<unsigned> expectedOut{ 10 };
    InstructionConverter converter{};
    converter.instructionsToLedsValues(input);
    EXPECT_EQ( converter.getLedsValues(), expectedOut);
}

TEST(MBB_Led_Converter, oneRegisterIsTakenTwoTimes)
{
    const std::vector<std::string> input{
        "ld a,10",
        "out (0),a",
        "out (0),a"};

    const std::vector<unsigned> expectedOut{ 10, 10 };
    InstructionConverter converter{};
    converter.instructionsToLedsValues(input);
    EXPECT_EQ( converter.getLedsValues(), expectedOut);
}

TEST(MBB_Led_Converter, movingBitsToRight)
{
    const std::vector<std::string> input{
        "ld a,10",
        "rrca",
        "out (0),a"};

    const std::vector<unsigned> expectedOut{ 5 };
    InstructionConverter converter{};
    converter.instructionsToLedsValues(input);
    EXPECT_EQ( converter.getLedsValues(), expectedOut);

}

TEST(MBB_Led_Converter, movingMostRightBitToRight)
{
    const std::vector<std::string> input{
        "ld a,1",
        "rrca",
        "out (0),a"};

    const std::vector<unsigned> expectedOut{ 128 };
    InstructionConverter converter{};
    converter.instructionsToLedsValues(input);
    EXPECT_EQ( converter.getLedsValues(), expectedOut);

}

TEST(MBB_Led_Converter, movingBitsToLeft)
{
    const std::vector<std::string> input{
        "ld a,200",
        "rlca",
        "out (0),a"};
    const std::vector<unsigned> expectedOut{ 145 };
    InstructionConverter converter{};
    converter.instructionsToLedsValues(input);
    EXPECT_EQ( converter.getLedsValues(), expectedOut);
}

TEST(MBB_Led_Converter, allBitsOnAreMovedToLeft)
{
    const std::vector<std::string> input{
        "ld a,255",
        "rlca",
        "out (0),a"};
    const std::vector<unsigned> expectedOut{ 255 };
    InstructionConverter converter{};
    converter.instructionsToLedsValues(input);
    EXPECT_EQ( converter.getLedsValues(), expectedOut);
}

TEST(MBB_Led_Converter, returnigLastSettedValue)
{
    const std::vector<std::string> input{
        "ld a,10",
        "ld a,12",
        "out (0),a"};

    const std::vector<unsigned> expectedOut{ 12 };
    InstructionConverter converter{};
    converter.instructionsToLedsValues(input);
    EXPECT_EQ( converter.getLedsValues(), expectedOut);
}

TEST(MBB_Led_Converter, convertingSetOfInstructions)
{
    const std::vector<std::string> input{
        "ld a,10",
        "out (0),a",
        "ld a,12",
        "out (0),a",
        "ld a,24",
        "eeee",
        "out (0),a"};

    const std::vector<unsigned> expectedOut{ 10, 12, 24 };
    InstructionConverter converter{};
    converter.instructionsToLedsValues(input);
    EXPECT_EQ( converter.getLedsValues(), expectedOut);
}
