#include "InstructionBuilderCombinator.hpp"
#include "gtest/gtest.h"

TEST(InstructionBuilderCombinatorTest, willParseLoadInstuction)
{
    std::stringstream in{" ld a,10"};
    ltm::InstructionBuilderCombinator lexer;
    const auto instructionVector = lexer.process(in);
    const auto expectedInstruction0 = Instruction{
        OperationType::load, Register::reg_a, u8_t{10}, Register::INVALID};
    ASSERT_EQ(instructionVector.size(), 1u);
    ASSERT_EQ(instructionVector[0], expectedInstruction0);
}

TEST(InstructionBuilderCombinatorTest, willParseOutputInstruction)
{
    std::stringstream in{" out (0),a"};
    ltm::InstructionBuilderCombinator lexer;
    const auto instructionVector = lexer.process(in);
    const auto expectedInstruction0 = Instruction{
        OperationType::output, Register::out_0, 0u, Register::reg_a};

    ASSERT_EQ(instructionVector.size(), 1u);
    ASSERT_EQ(instructionVector[0], expectedInstruction0);
}

TEST(InstructionBuilderCombinatorTest, willParseMultilineInputWithEmptyLines)
{
    std::stringstream in{" ld a,10\n ld a,255\n\n\n out (0),a\n"};
    ltm::InstructionBuilderCombinator lexer;
    const auto instructionVector = lexer.process(in);
    const auto expectedInstructionVector = std::vector<Instruction>{
        {OperationType::load, Register::reg_a, u8_t{10}, Register::INVALID},
        {OperationType::load, Register::reg_a, u8_t{255}, Register::INVALID},
        {OperationType::output, Register::out_0, u8_t{0u}, Register::reg_a}};
    ASSERT_EQ(instructionVector.size(), 3u);
    ASSERT_EQ(instructionVector, expectedInstructionVector);
}

TEST(InstructionBuilderCombinatorTest, willParseMultilineInputWithJump)
{
    std::stringstream in{"begin:\n"
            " ld a,10\n"
            " ld a,255\n\n\n"
            "middle:\n"
            " out (0),a\n"
            " djnz b middle:\n"
            ""};
    ltm::InstructionBuilderCombinator lexer;
    const auto instructionVector = lexer.process(in);
    const auto expectedInstructionVector = std::vector<Instruction>{
        {OperationType::load, Register::reg_a, u8_t{10}, Register::INVALID},
        {OperationType::load, Register::reg_a, u8_t{255}, Register::INVALID},
        {OperationType::output, Register::out_0, u8_t{0u}, Register::reg_a},
        {OperationType::decrementAndJump, Register::reg_b, u8_t{1}, Register::INVALID}};
    ASSERT_EQ(instructionVector.size(), 4u);
    ASSERT_EQ(instructionVector, expectedInstructionVector);
}

TEST(InstructionBuilderCombinatorTest, willParseMultilineInputAllExistingInstructions)
{
    std::stringstream in{"begin:\n"
            " ld a,10\n"
            " ld a,255\n\n\n"
            "middle:\n"
            " rlc a\n"
            " rrc b\n"
            " out (0),a\n"
            " djnz b middle:\n"
            ""};
    ltm::InstructionBuilderCombinator lexer;
    const auto instructionVector = lexer.process(in);
    const auto expectedInstructionVector = std::vector<Instruction>{
        {OperationType::load, Register::reg_a, u8_t{10}, Register::INVALID},
        {OperationType::load, Register::reg_a, u8_t{255}, Register::INVALID},
        {OperationType::rotateLeftCyclic, Register::reg_a, u8_t{0}, Register::INVALID},
        {OperationType::rotateRightCyclic, Register::reg_b, u8_t{0}, Register::INVALID},
        {OperationType::output, Register::out_0, u8_t{0u}, Register::reg_a},
        {OperationType::decrementAndJump, Register::reg_b, u8_t{1}, Register::INVALID}};
    ASSERT_EQ(instructionVector.size(), 6u);
    ASSERT_EQ(instructionVector, expectedInstructionVector);
}
