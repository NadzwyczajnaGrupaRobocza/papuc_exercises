#include "gtest/gtest.h"

#include "LoadInstructionBuilder.hpp"
namespace ltm
{
TEST(LoadInstructionBuilder, willBuildLoadInstruction)
{
    std::string instruction{" ld a,10"};
    ltm::LoadInstructionBuilder ib;
    bool result;
    Instruction received_instruction;
    Instruction expected_instruction{OperationType::load, Register::reg_a,
                                     u8_t{10}, Register::INVALID};
    std::tie(result, received_instruction) = ib.process(instruction);
    ASSERT_TRUE(result);
    ASSERT_EQ(received_instruction, expected_instruction);
}
}
