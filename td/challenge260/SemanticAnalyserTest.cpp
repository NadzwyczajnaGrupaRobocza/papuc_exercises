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

TEST_F(SemanticAnalyserTest, ShouldNotAcceptInvalidInstructionSet)
{
    Tokens tokens{createTokenWithZeroValue(TokenType::Ld)};
    ASSERT_THROW(analyser.analyse(tokens), SemanticAnalyser::InvalidSemantic);
}

TEST_F(SemanticAnalyserTest, ShouldAcceptLdInstruction)
{
    Tokens tokens{createTokenWithZeroValue(TokenType::Ld),
                  createTokenWithZeroValue(TokenType::A)};
    Instructions instructions{
        createInstructionWithZeroValue(InstructionType::LdA)};
    ASSERT_EQ(instructions, analyser.analyse(tokens));
}

TEST_F(SemanticAnalyserTest, ShouldAcceptOutInstruction)
{
    Tokens tokens{createTokenWithZeroValue(TokenType::Out),
                  createTokenWithZeroValue(TokenType::ZeroWithBracketsA)};
    Instructions instructions{
        createInstructionWithZeroValue(InstructionType::OutA)};
    ASSERT_EQ(instructions, analyser.analyse(tokens));
}

TEST_F(SemanticAnalyserTest, ShouldNotAcceptInvalidInstruction)
{
    Tokens tokens{createTokenWithZeroValue(TokenType::Out),
                  createTokenWithZeroValue(TokenType::Ld)};
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
                  createTokenWithZeroValue(TokenType::ZeroWithBracketsA),
                  createTokenWithZeroValue(TokenType::Ld),
                  createTokenWithZeroValue(TokenType::A)};
    Instructions instructions{
        createInstructionWithZeroValue(InstructionType::OutA),
        createInstructionWithZeroValue(InstructionType::LdA)};
    ASSERT_EQ(instructions, analyser.analyse(tokens));
}

TEST_F(SemanticAnalyserTest, ShouldAcceptLdInstructionWithValue)
{
    constexpr auto number = 42u;
    Tokens tokens{createTokenWithZeroValue(TokenType::Ld),
                  {TokenType::A, number}};
    Instructions instructions{{InstructionType::LdA, number}};
    ASSERT_EQ(instructions, analyser.analyse(tokens));
}

TEST_F(SemanticAnalyserTest, ShouldAcceptOutInstructionFollowedByLdWithValue)
{
    constexpr auto number = 42u;
    Tokens tokens{createTokenWithZeroValue(TokenType::Out),
                  createTokenWithZeroValue(TokenType::ZeroWithBracketsA),
                  createTokenWithZeroValue(TokenType::Ld),
                  {TokenType::A, number}};
    Instructions instructions{
        createInstructionWithZeroValue(InstructionType::OutA),
        {InstructionType::LdA, number}};
    ASSERT_EQ(instructions, analyser.analyse(tokens));
}

TEST_F(SemanticAnalyserTest, ShouldAccepRlcaInsruction)
{
    Tokens tokens{createTokenWithZeroValue(TokenType::Rlca)};
    Instructions instructions{
        createInstructionWithZeroValue(InstructionType::Rlca)};

    ASSERT_EQ(instructions, analyser.analyse(tokens));
}

TEST_F(SemanticAnalyserTest, ShouldAcceptLdBInstructionWithValue)
{
    constexpr auto number = 42u;
    Tokens tokens{createTokenWithZeroValue(TokenType::Ld),
                  {TokenType::B, number}};
    Instructions instructions{{InstructionType::LdB, number}};
    ASSERT_EQ(instructions, analyser.analyse(tokens));
}

TEST_F(SemanticAnalyserTest, ShouldAccepRrcaInsruction)
{
    Tokens tokens{createTokenWithZeroValue(TokenType::Rrca)};
    Instructions instructions{
        createInstructionWithZeroValue(InstructionType::Rrca)};

    ASSERT_EQ(instructions, analyser.analyse(tokens));
}

TEST_F(SemanticAnalyserTest, ShouldAccepDjnzInsruction)
{
    Tokens tokens{
        createTokenWithZeroValue(TokenType::Djnz),
        createTokenWithZeroValue(TokenType::LabelRef),
    };
    Instructions instructions{
        createInstructionWithZeroValue(InstructionType::Djnz)};

    ASSERT_EQ(instructions, analyser.analyse(tokens));
}

TEST_F(SemanticAnalyserTest, ShouldAccepLabelInsruction)
{
    Tokens tokens{createTokenWithZeroValue(TokenType::Label)};
    Instructions instructions{
        createInstructionWithZeroValue(InstructionType::Label)};

    ASSERT_EQ(instructions, analyser.analyse(tokens));
}

TEST_F(SemanticAnalyserTest, ShouldAccepLabelInsructionWithNonZeroValue)
{
    constexpr auto number = 42u;
    Tokens tokens{{TokenType::Label, number}};
    Instructions instructions{{InstructionType::Label, number}};

    ASSERT_EQ(instructions, analyser.analyse(tokens));
}

TEST_F(SemanticAnalyserTest, ShouldAccepDjnzInsructionWIthNonZeroValue)
{
    constexpr auto number = 42u;
    Tokens tokens{
        createTokenWithZeroValue(TokenType::Djnz),
        {TokenType::LabelRef, number},
    };
    Instructions instructions{{InstructionType::Djnz, number}};

    ASSERT_EQ(instructions, analyser.analyse(tokens));
}
