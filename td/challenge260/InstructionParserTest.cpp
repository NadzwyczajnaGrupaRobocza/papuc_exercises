#include "InstructionParser.hpp"

#include "gtest/gtest.h"

using namespace ::testing;

struct InstructionParserTest : public Test
{
  InstructionParser parser;

  Token createTokenWithZeroValue(TokenType type)
  {
    return {type, 0};
  }
};

TEST_F(InstructionParserTest, ParserShouldDeclineUnknownInstruction)
{
  EXPECT_THROW(parser.parseInstructions("Instructions"), InstructionParser::UnknownInstruction);
}

TEST_F(InstructionParserTest, ParserShouldRejectInstuctionLd)
{
  const Tokens expectedTokens{createTokenWithZeroValue(TokenType::Ld), createTokenWithZeroValue(TokenType::A)};
  parser.parseInstructions("ld a,");
}

TEST_F(InstructionParserTest, ParserShouldAcceptInstructionOut)
{
  const Tokens expectedTokens{createTokenWithZeroValue(TokenType::Out),
                              createTokenWithZeroValue(TokenType::ZeroWithBrackets),
                              createTokenWithZeroValue(TokenType::A)};
  EXPECT_EQ(expectedTokens, parser.parseInstructions("out (0),a"));
}

TEST_F(InstructionParserTest, ParserShouldAcceptEmptyLine)
{
  const Tokens expectedTokens{};
  EXPECT_EQ(expectedTokens, parser.parseInstructions(""));
}

TEST_F(InstructionParserTest, ParserShouldAcceptInstructionOutWithWhitespaces)
{
  const Tokens expectedTokens{createTokenWithZeroValue(TokenType::Out),
                              createTokenWithZeroValue(TokenType::ZeroWithBrackets),
                              createTokenWithZeroValue(TokenType::A)};
  EXPECT_EQ(expectedTokens, parser.parseInstructions(" \t    out (0),a"));
}

TEST_F(InstructionParserTest, ParserShouldAcceptTwoInstructions)
{
  const Tokens expectedTokens{createTokenWithZeroValue(TokenType::Out),
                              createTokenWithZeroValue(TokenType::ZeroWithBrackets),
                              createTokenWithZeroValue(TokenType::A),
                              createTokenWithZeroValue(TokenType::Out),
                              createTokenWithZeroValue(TokenType::ZeroWithBrackets),
                              createTokenWithZeroValue(TokenType::A)};
  EXPECT_EQ(expectedTokens, parser.parseInstructions("out (0),a\nout (0),a"));
}

TEST_F(InstructionParserTest, ParserShouldThrowIfSecondInstructionIsInvalid)
{
  EXPECT_THROW(parser.parseInstructions("out (0),a\ninvalid"), InstructionParser::UnknownInstruction);
}

TEST_F(InstructionParserTest, ParserShouldAcceptTwoInstructionsWithEmptyLine)
{
  const Tokens expectedTokens{createTokenWithZeroValue(TokenType::Out),
                              createTokenWithZeroValue(TokenType::ZeroWithBrackets),
                              createTokenWithZeroValue(TokenType::A),
                              createTokenWithZeroValue(TokenType::Out),
                              createTokenWithZeroValue(TokenType::ZeroWithBrackets),
                              createTokenWithZeroValue(TokenType::A)};
  EXPECT_EQ(expectedTokens, parser.parseInstructions("out (0),a\n\nout (0),a"));
}

TEST_F(InstructionParserTest, ParserShouldAbleToGet0AsToken)
{
  const Tokens expectedTokens{{TokenType::Number8Bit, 0}};
  EXPECT_EQ(expectedTokens, parser.parseInstructions("0"));
}

TEST_F(InstructionParserTest, ParserShouldAbleToGet255AsToken)
{
  const Tokens expectedTokens{{TokenType::Number8Bit, 255}};
  parser.parseInstructions("255");
}

TEST_F(InstructionParserTest, ParserShouldAbleToGetMinusOneAsToken)
{
  EXPECT_THROW(parser.parseInstructions("-1"), InstructionParser::UnknownInstruction);
}

TEST_F(InstructionParserTest, ParserShouldAbleToGet256AsToken)
{
  EXPECT_THROW(parser.parseInstructions("256"), InstructionParser::UnknownInstruction);
}

