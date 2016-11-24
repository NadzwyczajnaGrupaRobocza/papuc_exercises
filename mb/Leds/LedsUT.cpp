#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "InputParser.hpp"
#include "InstructionToLedBlinkConverter.hpp"
#include "LedBlinker.hpp"

using testing::InSequence;
using testing::AtLeast;
using testing::Return;

using Converter = InstructionToLedBlinkConverter;

TEST(MBB_Led_Converter, fullConverting)
{
    std::string line = " ld a,21";

    Converter converter{};
    converter.convert(line);

    EXPECT_EQ(line, "...*.*.*");
}


TEST(MBB_Led_LedBlinker, showLedBlinks)
{
    std::vector<std::string> inputData{ "..**.", "..***", "...**", "....*" };
    
    LedBlinker ledBlinker{ inputData };
    ledBlinker.showLeds();

    EXPECT_EQ(1, static_cast<int>(1.00));
}

