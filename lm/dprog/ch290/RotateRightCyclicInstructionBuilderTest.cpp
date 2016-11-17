#include "RotateRightCyclicInstructionBuilder.hpp"
#include "gtest/gtest.h"

namespace ltm
{
TEST(RotateRightCyclicInstructionBuilderTest, handleCorrectData)
{
    RotateRightCyclicInstructionBuilder ib;
    bool opSuccess;
    Instruction received_instruction;
    std::tie(opSuccess, received_instruction) = ib.process(" rrc b");
    const auto expected_instruction =
        Instruction{OperationType::rotateRightCyclic, Register::reg_b,
                    u8_t{0}, Register::INVALID};
    ASSERT_TRUE(opSuccess);
    ASSERT_EQ(received_instruction, expected_instruction);
}
}
