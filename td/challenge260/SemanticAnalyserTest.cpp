#include "gtest/gtest.h"

#include <stdexcept>

#include "SemanticAnalyser.hpp"

using namespace ::testing;

struct SemanticAnalyserTest : public Test
{
    SemanticAnalyser analyser;

    static constexpr Token createTokenWithZeroValue(TokenType type)
    {
        return {type, 0};
    }

    static constexpr Instruction
    createInstructionWithZeroValue(InstructionType type)
    {
        return {type, 0};
    }
};

TEST_F(SemanticAnalyserTest, ShouldAcceptEmptyTokens)
{
    Tokens tokens{};
    Instructions instructions;
    ASSERT_EQ(instructions, analyser.analyse(tokens));
}

TEST_F(SemanticAnalyserTest, DISABLED_ShouldNotAcceptInvalidInstructionSet)
{
    Tokens tokens{createTokenWithZeroValue(TokenType::Ld)};
    ASSERT_THROW(analyser.analyse(tokens), SemanticAnalyser::InvalidSemantic);
}

TEST_F(SemanticAnalyserTest, ShouldAcceptLdInstruction)
{
    Tokens tokens{createTokenWithZeroValue(TokenType::Ld),
                  createTokenWithZeroValue(TokenType::A),
                  createTokenWithZeroValue(TokenType::Number8Bit)};
    Instructions instructions{
        createInstructionWithZeroValue(InstructionType::LdA)};
    ASSERT_EQ(instructions, analyser.analyse(tokens));
}

TEST_F(SemanticAnalyserTest, ShouldAcceptOutInstruction)
{
    Tokens tokens{createTokenWithZeroValue(TokenType::Out),
                  createTokenWithZeroValue(TokenType::ZeroWithBrackets),
                  createTokenWithZeroValue(TokenType::A)};
    Instructions instructions{
        createInstructionWithZeroValue(InstructionType::OutA)};
    ASSERT_EQ(instructions, analyser.analyse(tokens));
}

TEST_F(SemanticAnalyserTest, ShouldNotAcceptInvalidInstruction)
{
    Tokens tokens{createTokenWithZeroValue(TokenType::Out),
                  createTokenWithZeroValue(TokenType::Number8Bit),
                  createTokenWithZeroValue(TokenType::A)};
    ASSERT_THROW(analyser.analyse(tokens), SemanticAnalyser::InvalidSemantic);
}

TEST_F(SemanticAnalyserTest, ShouldRejectInvalidLdInstruction)
{
    Tokens tokens{createTokenWithZeroValue(TokenType::Ld),
                  createTokenWithZeroValue(TokenType::A),
                  createTokenWithZeroValue(TokenType::Out)};
    ASSERT_THROW(analyser.analyse(tokens), SemanticAnalyser::InvalidSemantic);
}

TEST_F(SemanticAnalyserTest, ShouldAcceptOutInstructionFollowedByLd)
{
    Tokens tokens{createTokenWithZeroValue(TokenType::Out),
                  createTokenWithZeroValue(TokenType::ZeroWithBrackets),
                  createTokenWithZeroValue(TokenType::A),
                  createTokenWithZeroValue(TokenType::Ld),
                  createTokenWithZeroValue(TokenType::A),
                  createTokenWithZeroValue(TokenType::Number8Bit)};
    Instructions instructions{
        createInstructionWithZeroValue(InstructionType::OutA),
        createInstructionWithZeroValue(InstructionType::LdA)};
    ASSERT_EQ(instructions, analyser.analyse(tokens));
}

TEST_F(SemanticAnalyserTest, ShouldAcceptLdInstructionWithValue)
{
    constexpr auto number = 42u;
    Tokens tokens{createTokenWithZeroValue(TokenType::Ld),
                  createTokenWithZeroValue(TokenType::A),
                  {TokenType::Number8Bit, number}};
    Instructions instructions{{InstructionType::LdA, number}};
    ASSERT_EQ(instructions, analyser.analyse(tokens));
}

TEST_F(SemanticAnalyserTest, ShouldAcceptOutInstructionFollowedByLdWithValue)
{
    constexpr auto number = 42u;
    Tokens tokens{createTokenWithZeroValue(TokenType::Out),
                  createTokenWithZeroValue(TokenType::ZeroWithBrackets),
                  createTokenWithZeroValue(TokenType::A),
                  createTokenWithZeroValue(TokenType::Ld),
                  createTokenWithZeroValue(TokenType::A),
                  {TokenType::Number8Bit, number}};
    Instructions instructions{
        createInstructionWithZeroValue(InstructionType::OutA),
        {InstructionType::LdA, number}};
    ASSERT_EQ(instructions, analyser.analyse(tokens));
}
