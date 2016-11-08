#include "InstructionLexer.hpp"
#include "gtest/gtest.h"

TEST(InstructionLexerTest, willParseLoadInstuction)
{
    std::stringstream in{" ld a,10"};
    InstructionLexer lexer;
    const auto instructionVector = lexer.lex(in);
    const auto expectedInstruction0 = Instruction{
        OperationType::load, Register::reg_a, u8_t{10}, Register::INVALID};
    ASSERT_EQ(instructionVector.size(), 1u);
    ASSERT_EQ(instructionVector[0], expectedInstruction0);
}

TEST(InstructionLexerTest, willParseOutputInstruction)
{
    std::stringstream in{" out (0),a"};
    InstructionLexer lexer;
    const auto instructionVector = lexer.lex(in);
    const auto expectedInstruction0 = Instruction{
        OperationType::output, Register::out_0, 0u, Register::reg_a};

    ASSERT_EQ(instructionVector.size(), 1u);
    ASSERT_EQ(instructionVector[0], expectedInstruction0);
}

TEST(InstructionLexerTest, willParseMultilineInputWithEmptyLines)
{
    std::stringstream in{" ld a,10\n ld a,255\n\n\n out (0),a\n"};
    InstructionLexer lexer;
    const auto instructionVector = lexer.lex(in);
    const auto expectedInstructionVector = std::vector<Instruction>{
        {OperationType::load, Register::reg_a, u8_t{10}, Register::INVALID},
        {OperationType::load, Register::reg_a, u8_t{255}, Register::INVALID},
        {OperationType::output, Register::out_0, u8_t{0u}, Register::reg_a}};
    ASSERT_EQ(instructionVector.size(), 3u);
    ASSERT_EQ(instructionVector, expectedInstructionVector);
}
