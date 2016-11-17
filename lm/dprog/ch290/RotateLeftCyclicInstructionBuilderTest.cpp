#include "RotateLeftCyclicInstructionBuilder.hpp"
#include "gtest/gtest.h"

namespace ltm
{
TEST(RotateLeftCyclicInstructionBuilderTest, handleCorrectData)
{
    RotateLeftCyclicInstructionBuilder ib;
    bool opSuccess;
    Instruction received_instruction;
    std::tie(opSuccess, received_instruction) = ib.process(" rlc a");
    const auto expected_instruction =
        Instruction{OperationType::rotateLeftCyclic, Register::reg_a,
                    u8_t{0}, Register::INVALID};
    ASSERT_TRUE(opSuccess);
    ASSERT_EQ(received_instruction, expected_instruction);
}
}
