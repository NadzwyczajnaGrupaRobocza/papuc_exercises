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
  EXPECT_THROW(parser.parseInstructions("Instructions"), InstructionLexer::UnknownInstruction);
}

TEST_F(InstructionLexerTest, ParserShouldRejectInstuctionLd)
{
  const Tokens expectedTokens{createTokenWithZeroValue(TokenType::Ld), createTokenWithZeroValue(TokenType::A)};
  parser.parseInstructions("ld a,");
}

TEST_F(InstructionLexerTest, ParserShouldAcceptInstructionOut)
{
  const Tokens expectedTokens{createTokenWithZeroValue(TokenType::Out),
                              createTokenWithZeroValue(TokenType::ZeroWithBrackets),
                              createTokenWithZeroValue(TokenType::A)};
  EXPECT_EQ(expectedTokens, parser.parseInstructions("out (0),a"));
}

TEST_F(InstructionLexerTest, ParserShouldAcceptEmptyLine)
{
  const Tokens expectedTokens{};
  EXPECT_EQ(expectedTokens, parser.parseInstructions(""));
}

TEST_F(InstructionLexerTest, ParserShouldAcceptInstructionOutWithWhitespaces)
{
  const Tokens expectedTokens{createTokenWithZeroValue(TokenType::Out),
                              createTokenWithZeroValue(TokenType::ZeroWithBrackets),
                              createTokenWithZeroValue(TokenType::A)};
  EXPECT_EQ(expectedTokens, parser.parseInstructions(" \t    out (0),a"));
}

TEST_F(InstructionLexerTest, ParserShouldAcceptTwoInstructions)
{
  const Tokens expectedTokens{createTokenWithZeroValue(TokenType::Out),
                              createTokenWithZeroValue(TokenType::ZeroWithBrackets),
                              createTokenWithZeroValue(TokenType::A),
                              createTokenWithZeroValue(TokenType::Out),
                              createTokenWithZeroValue(TokenType::ZeroWithBrackets),
                              createTokenWithZeroValue(TokenType::A)};
  EXPECT_EQ(expectedTokens, parser.parseInstructions("out (0),a\nout (0),a"));
}

TEST_F(InstructionLexerTest, ParserShouldThrowIfSecondInstructionIsInvalid)
{
  EXPECT_THROW(parser.parseInstructions("out (0),a\ninvalid"), InstructionLexer::UnknownInstruction);
}

TEST_F(InstructionLexerTest, ParserShouldAcceptTwoInstructionsWithEmptyLine)
{
  const Tokens expectedTokens{createTokenWithZeroValue(TokenType::Out),
                              createTokenWithZeroValue(TokenType::ZeroWithBrackets),
                              createTokenWithZeroValue(TokenType::A),
                              createTokenWithZeroValue(TokenType::Out),
                              createTokenWithZeroValue(TokenType::ZeroWithBrackets),
                              createTokenWithZeroValue(TokenType::A)};
  EXPECT_EQ(expectedTokens, parser.parseInstructions("out (0),a\n\nout (0),a"));
}

TEST_F(InstructionLexerTest, ParserShouldAbleToGet0AsToken)
{
  const Tokens expectedTokens{{TokenType::Number8Bit, 0}};
  EXPECT_EQ(expectedTokens, parser.parseInstructions("0"));
}

TEST_F(InstructionLexerTest, ParserShouldAbleToGet255AsToken)
{
  const Tokens expectedTokens{{TokenType::Number8Bit, 255}};
  parser.parseInstructions("255");
}

TEST_F(InstructionLexerTest, ParserShouldAbleToGetMinusOneAsToken)
{
  EXPECT_THROW(parser.parseInstructions("-1"), InstructionLexer::UnknownInstruction);
}

TEST_F(InstructionLexerTest, ParserShouldAbleToGet256AsToken)
{
  EXPECT_THROW(parser.parseInstructions("256"), InstructionLexer::UnknownInstruction);
}
