#include "DecrementAndJumpIfNonZeroInstructionBuilder.hpp"
#include "gtest/gtest.h"

namespace ltm
{
TEST(DecrementAndJumpInstructionBuilderTest, handleCorrectData)
{
    DecrementAndJumpInstructionBuilder ib;
    bool opSuccess;
    Instruction received_instruction;
    std::tie(opSuccess, received_instruction) = ib.process(" djnz b 1");
    const auto expected_instruction =
        Instruction{OperationType::decrementAndJump, Register::reg_b,
                    u8_t{1}, Register::INVALID};
    ASSERT_TRUE(opSuccess);
    ASSERT_EQ(received_instruction, expected_instruction);
}
}
