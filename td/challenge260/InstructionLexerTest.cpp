#include "InstructionLexer.hpp"

#include "gtest/gtest.h"

using namespace ::testing;

struct InstructionLexerTest : public Test
{
    InstructionLexer parser;

    Token createTokenWithZeroValue(TokenType type)
    {
        return {type, 0};
    }
};

TEST_F(InstructionLexerTest, ParserShouldDeclineUnknownInstruction)
{
    EXPECT_THROW(parser.parseInstructions("Instructions"),
                 InstructionLexer::UnknownInstruction);
}

TEST_F(InstructionLexerTest, ParserShouldNotRejectNotFullInstuctionLd)
{
    const Tokens expectedTokens{createTokenWithZeroValue(TokenType::Ld),
                                createTokenWithZeroValue(TokenType::A)};
    EXPECT_EQ(expectedTokens, parser.parseInstructions(" ld a,"));
}

TEST_F(InstructionLexerTest, ParserShouldDeclineUnknownWithoutWhitespaceOnFront)
{
    EXPECT_THROW(parser.parseInstructions("out (0),a"),
                 InstructionLexer::UnknownInstruction);
}

TEST_F(InstructionLexerTest, ParserShouldAcceptInstructionOut)
{
    const Tokens expectedTokens{
        createTokenWithZeroValue(TokenType::Out),
        createTokenWithZeroValue(TokenType::ZeroWithBrackets),
        createTokenWithZeroValue(TokenType::A)};
    EXPECT_EQ(expectedTokens, parser.parseInstructions(" out (0),a"));
}

TEST_F(InstructionLexerTest, ParserShouldAcceptEmptyLine)
{
    const Tokens expectedTokens{};
    EXPECT_EQ(expectedTokens, parser.parseInstructions(""));
}

TEST_F(InstructionLexerTest, ParserShouldAcceptInstructionOutWithWhitespaces)
{
    const Tokens expectedTokens{
        createTokenWithZeroValue(TokenType::Out),
        createTokenWithZeroValue(TokenType::ZeroWithBrackets),
        createTokenWithZeroValue(TokenType::A)};
    EXPECT_EQ(expectedTokens, parser.parseInstructions(" \t    out (0),a"));
}

TEST_F(InstructionLexerTest, ParserShouldAcceptTwoInstructions)
{
    const Tokens expectedTokens{
        createTokenWithZeroValue(TokenType::Out),
        createTokenWithZeroValue(TokenType::ZeroWithBrackets),
        createTokenWithZeroValue(TokenType::A),
        createTokenWithZeroValue(TokenType::Out),
        createTokenWithZeroValue(TokenType::ZeroWithBrackets),
        createTokenWithZeroValue(TokenType::A)};
    EXPECT_EQ(expectedTokens,
              parser.parseInstructions(" out (0),a\n out (0),a"));
}

TEST_F(InstructionLexerTest, ParserShouldThrowIfSecondInstructionIsInvalid)
{
    EXPECT_THROW(parser.parseInstructions(" out (0),a\ninvalid"),
                 InstructionLexer::UnknownInstruction);
}

TEST_F(InstructionLexerTest, ParserShouldAcceptTwoInstructionsWithEmptyLine)
{
    const Tokens expectedTokens{
        createTokenWithZeroValue(TokenType::Out),
        createTokenWithZeroValue(TokenType::ZeroWithBrackets),
        createTokenWithZeroValue(TokenType::A),
        createTokenWithZeroValue(TokenType::Out),
        createTokenWithZeroValue(TokenType::ZeroWithBrackets),
        createTokenWithZeroValue(TokenType::A)};
    EXPECT_EQ(expectedTokens,
              parser.parseInstructions(" out (0),a\n \n out (0),a"));
}

TEST_F(InstructionLexerTest, ParserShouldAbleToGet0AsToken)
{
    const Tokens expectedTokens{{TokenType::Number8Bit, 0}};
    EXPECT_EQ(expectedTokens, parser.parseInstructions(" 0"));
}

TEST_F(InstructionLexerTest, ParserShouldAbleToGet255AsToken)
{
    const Tokens expectedTokens{{TokenType::Number8Bit, 255}};
    parser.parseInstructions(" 255");
}

TEST_F(InstructionLexerTest, ParserShouldAbleToGetMinusOneAsToken)
{
    EXPECT_THROW(parser.parseInstructions(" -1"),
                 InstructionLexer::UnknownInstruction);
}

TEST_F(InstructionLexerTest, ParserShouldAbleToGet256AsToken)
{
    EXPECT_THROW(parser.parseInstructions(" 256"),
                 InstructionLexer::UnknownInstruction);
}

TEST_F(InstructionLexerTest, ParserShouldParseLdBInstruction)
{
    const Tokens expectedTokens{createTokenWithZeroValue(TokenType::Ld),
                                createTokenWithZeroValue(TokenType::B)};
    EXPECT_EQ(expectedTokens, parser.parseInstructions(" ld b,"));
}

TEST_F(InstructionLexerTest, ParserShouldParseRlcaInstruction)
{
    const Tokens expectedTokens{createTokenWithZeroValue(TokenType::Rlca)};
    EXPECT_EQ(expectedTokens, parser.parseInstructions(" rlca"));
}

TEST_F(InstructionLexerTest, ParserShouldParseRrcaInstruction)
{
    const Tokens expectedTokens{createTokenWithZeroValue(TokenType::Rrca)};
    EXPECT_EQ(expectedTokens, parser.parseInstructions(" rrca"));
}

TEST_F(InstructionLexerTest, ParserShouldParseDjnzInstruction)
{
    const Tokens expectedTokens{createTokenWithZeroValue(TokenType::Djnz)};
    EXPECT_EQ(expectedTokens, parser.parseInstructions(" djnz"));
}
