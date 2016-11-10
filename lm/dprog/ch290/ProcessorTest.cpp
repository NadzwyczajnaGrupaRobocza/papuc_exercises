#include "Processor.hpp"
#include "gtest/gtest.h"

TEST(ProcessorTest, willProcessTwoInstructions)
{
    const auto expected_value = u8_t{129};
    Processor::Program testProgram = {
        Instruction{OperationType::load, Register::reg_a, expected_value,
                    Register::INVALID},
        Instruction{OperationType::output, Register::out_0, u8_t{0},
                    Register::reg_a}};

    u8_t output = 0;
    auto output_listener = [&](const u8_t v) {
        output = v;
    };

    Processor p{{{Register::out_0, output_listener}}};

    p.runProgram(testProgram);
    ASSERT_EQ(output, expected_value);
}
