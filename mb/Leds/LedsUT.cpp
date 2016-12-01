#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "InputParser.hpp"
#include "InstructionToLedBlinkConverter.hpp"
#include "LedBlinker.hpp"

using testing::InSequence;
using testing::AtLeast;
using testing::Return;

using Converter = InstructionToLedBlinkConverter;

TEST(MBB_Led_Converter, convertingSingleInstruction)
{
    const std::vector<std::string> input{
        "     ld a,10      ",
        "  out (0),a  "};

    const std::vector<uint> expectedOut{ 10 };
    InputParser parser{};
    parser.changeInputIntoSetOfInstructions(input);
    EXPECT_EQ( parser.returnParsedFileAsValues(), expectedOut);
}

TEST(MBB_Led_Converter, movingBitsToRight)
{
    const std::vector<std::string> input{
        "     ld a,10      ",
        " rrca ",
        "  out (0),a  "};

    const std::vector<uint> expectedOut{ 5 };
    InputParser parser{};
    parser.changeInputIntoSetOfInstructions(input);
    EXPECT_EQ( parser.returnParsedFileAsValues(), expectedOut);

}

TEST(MBB_Led_Converter, movingMostRightBitToRight)
{
    const std::vector<std::string> input{
        "     ld a,1      ",
        " rrca ",
        "  out (0),a  "};

    const std::vector<uint> expectedOut{ 128 };
    InputParser parser{};
    parser.changeInputIntoSetOfInstructions(input);
    EXPECT_EQ( parser.returnParsedFileAsValues(), expectedOut);

}

TEST(MBB_Led_Converter, movingBitsToLeft)
{
    const std::vector<std::string> input{
        "     ld a,200      ",
        " rlca ",
        "  out (0),a  "};
    const std::vector<uint> expectedOut{ 145 };
    InputParser parser{};
    parser.changeInputIntoSetOfInstructions(input);
    EXPECT_EQ( parser.returnParsedFileAsValues(), expectedOut);
}

TEST(MBB_Led_Converter, allBitsOnAreMovedToLeft)
{
    const std::vector<std::string> input{
        "     ld a,255      ",
        " rlca ",
        "  out (0),a  "};
    const std::vector<uint> expectedOut{ 255 };
    InputParser parser{};
    parser.changeInputIntoSetOfInstructions(input);
    EXPECT_EQ( parser.returnParsedFileAsValues(), expectedOut);
}

TEST(MBB_Led_Converter, returnigLastSettedValue)
{
    const std::vector<std::string> input{
        " ld a,10",
        " ld a,12",
        " out (0),a"};

    const std::vector<uint> expectedOut{ 12 };
    InputParser parser{};
    parser.changeInputIntoSetOfInstructions(input);
    EXPECT_EQ( parser.returnParsedFileAsValues(), expectedOut);
}

TEST(MBB_Led_Converter, convertingSetOfInstructions)
{
    const std::vector<std::string> input{
        " ld a,10",
        "    ",
        " out (0),a",
        " ld a,12",
        " out (0),a",
        " ld a,24",
        "eeee",
        " out (0),a"};

    const std::vector<uint> expectedOut{ 10, 12, 24 };
    InputParser parser{};
    parser.changeInputIntoSetOfInstructions(input);
    EXPECT_EQ( parser.returnParsedFileAsValues(), expectedOut);
}

TEST(MBB_Led_LedBlinker, showLedBlinks)
{
    std::vector<uint> inputData{ 14, 7, 3, 1 };
    
    LedBlinker ledBlinker{};
    ledBlinker.showLedsBlinks( inputData );

    EXPECT_EQ(1, static_cast<int>(1.00));
}

TEST(MBB_Led_LedBlinker, SCT)
{
    const std::vector<std::string> input{
        " ld a,10",
        "    ",
        " out (0),a",
        " ld a,12",
        " out (0),a",
        " ld a,15",
        "eeee",
        " out (0),a",
        " rrca",
        " out (0),a",
        " rrca",
        " out (0),a",
        " rrca",
        " out (0),a",
        " rrca",
        " out (0),a",
        " rrca",
        " out (0),a",
        " rrca",
        " out (0),a",
        " rrca",
        " out (0),a"};

    //const std::vector<uint> expectedOut{ 10, 12, 24 };
    InputParser parser{};
    parser.changeInputIntoSetOfInstructions(input);
    const std::vector<uint> expectedOut = parser.returnParsedFileAsValues();

    LedBlinker ledBlinker{};
    ledBlinker.showLedsBlinks( expectedOut );

    EXPECT_EQ(1, static_cast<int>(1.00));
}
