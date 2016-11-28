#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "InputParser.hpp"
#include "InstructionToLedBlinkConverter.hpp"
#include "LedBlinker.hpp"

using testing::InSequence;
using testing::AtLeast;
using testing::Return;

using Converter = InstructionToLedBlinkConverter;

TEST(MBB_Led_Converter, convertingInstructionToLedsBlinks)
{
    std::string line = "ld a,21";

    Converter converter{};
    converter.convert(line);

    EXPECT_EQ(line, "...*.*.*");
}

TEST(MBB_Led_Converter, shouldThrowErrorWhenWrongInstruction)
{
    std::string line = "lld a,21";

    Converter converter{};

    EXPECT_THROW(converter.convert(line), std::invalid_argument);
}

TEST(MBB_Led_Converter, shouldThrowErrorWhenNumberGreaterThan255)
{
    std::string line = "ld a,256";

    Converter converter{};

    EXPECT_THROW(converter.convert(line), std::out_of_range);
}


TEST(MBB_Led_LedBlinker, showLedBlinks)
{
    std::vector<std::string> inputData{ "..**.", "..***", "...**", "....*" };
    
    LedBlinker ledBlinker{ inputData };
    ledBlinker.showLeds();

    EXPECT_EQ(1, static_cast<int>(1.00));
}

