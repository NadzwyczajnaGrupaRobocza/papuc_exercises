#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "InputParser.hpp"
#include "LedBlinker.hpp"
#include "InstructionPreparer.hpp"
//#include "LedCommon.hpp"

using testing::InSequence;
using testing::AtLeast;
using testing::Return;

using namespace mb_led;

TEST(MBB_Led_Converter, convertingSingleInstruction)
{
    const std::vector<std::string> input{
        "ld a,10",
        "out (0),a"};

    const std::vector<uint> expectedOut{ 10 };
    InputParser parser{};
    parser.getSetOfValuesFromInstructions(input);
    EXPECT_EQ( parser.getValues(), expectedOut);
}

TEST(MBB_Led_Converter, oneRegisterIsTakenTwoTimes)
{
    const std::vector<std::string> input{
        "ld a,10",
        "out (0),a",
        "out (0),a"};

    const std::vector<uint> expectedOut{ 10, 10 };
    InputParser parser{};
    parser.getSetOfValuesFromInstructions(input);
    EXPECT_EQ( parser.getValues(), expectedOut);
}

TEST(MBB_Led_Converter, movingBitsToRight)
{
    const std::vector<std::string> input{
        "ld a,10",
        "rrca",
        "out (0),a"};

    const std::vector<uint> expectedOut{ 5 };
    InputParser parser{};
    parser.getSetOfValuesFromInstructions(input);
    EXPECT_EQ( parser.getValues(), expectedOut);

}

TEST(MBB_Led_Converter, movingMostRightBitToRight)
{
    const std::vector<std::string> input{
        "ld a,1",
        "rrca",
        "out (0),a"};

    const std::vector<uint> expectedOut{ 128 };
    InputParser parser{};
    parser.getSetOfValuesFromInstructions(input);
    EXPECT_EQ( parser.getValues(), expectedOut);

}

TEST(MBB_Led_Converter, movingBitsToLeft)
{
    const std::vector<std::string> input{
        "ld a,200",
        "rlca",
        "out (0),a"};
    const std::vector<uint> expectedOut{ 145 };
    InputParser parser{};
    parser.getSetOfValuesFromInstructions(input);
    EXPECT_EQ( parser.getValues(), expectedOut);
}

TEST(MBB_Led_Converter, allBitsOnAreMovedToLeft)
{
    const std::vector<std::string> input{
        "ld a,255",
        "rlca",
        "out (0),a"};
    const std::vector<uint> expectedOut{ 255 };
    InputParser parser{};
    parser.getSetOfValuesFromInstructions(input);
    EXPECT_EQ( parser.getValues(), expectedOut);
}

TEST(MBB_Led_Converter, returnigLastSettedValue)
{
    const std::vector<std::string> input{
        "ld a,10",
        "ld a,12",
        "out (0),a"};

    const std::vector<uint> expectedOut{ 12 };
    InputParser parser{};
    parser.getSetOfValuesFromInstructions(input);
    EXPECT_EQ( parser.getValues(), expectedOut);
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

    const std::vector<uint> expectedOut{ 10, 12, 24 };
    InputParser parser{};
    parser.getSetOfValuesFromInstructions(input);
    EXPECT_EQ( parser.getValues(), expectedOut);
}

TEST(MBB_Led_Converter, test_01)
{
    InstructionPreparer ip{};
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
    ip.prepare(input);
    EXPECT_EQ(ip.getPreparedInstructions(), expectedOut);
}
/*
TEST(MBB_Led_Converter, test_02)
{
    InstructionPreparer ip{};
    const std::vector<std::string> input{
        " ld a,10",
        " ld b,3"};
    const std::vector<std::string> expectedOut{
        "ld a,10"};
    ip.prepare(input);
    EXPECT_EQ(ip.getPreparedInstructions(), expectedOut);
}

TEST(MBB_Led_Converter, test_03)
{
    InstructionPreparer ip{};
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
    ip.prepare(input);
    EXPECT_EQ(ip.getPreparedInstructions(), expectedOut);
}

TEST(MBB_Led_Converter, test_04)
{
    InstructionPreparer ip{};
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
    ip.prepare(input);
    EXPECT_EQ(ip.getPreparedInstructions(), expectedOut);
}

*/
