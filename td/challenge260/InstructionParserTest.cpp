#include "InstructionParser.hpp"

#include "gtest/gtest.h"

using namespace ::testing;

struct InstructionParserTest : public Test
{
  InstructionParser parser;
};

TEST_F(InstructionParserTest, ParserShouldDeclineUnknownInstruction)
{
  EXPECT_THROW(parser.parseInstructions("Instructions"), InstructionParser::UnknownInstruction);
}

TEST_F(InstructionParserTest, ParserShouldRejectInstuctionLd)
{
  const Tokens expectedTokens{TokenType::Ld, TokenType::A};
  parser.parseInstructions("ld a,");
}

TEST_F(InstructionParserTest, ParserShouldAcceptInstructionOut)
{
  const Tokens expectedTokens{TokenType::Out, TokenType::ZeroWithBrackets, TokenType::A};
  EXPECT_EQ(expectedTokens, parser.parseInstructions("out (0),a"));
}

TEST_F(InstructionParserTest, ParserShouldAcceptEmptyLine)
{
  const Tokens expectedTokens{};
  EXPECT_EQ(expectedTokens, parser.parseInstructions(""));
}

TEST_F(InstructionParserTest, ParserShouldAcceptInstructionOutWithWhitespaces)
{
  const Tokens expectedTokens{TokenType::Out, TokenType::ZeroWithBrackets, TokenType::A};
  EXPECT_EQ(expectedTokens, parser.parseInstructions(" \t    out (0),a"));
}

TEST_F(InstructionParserTest, ParserShouldAcceptTwoInstructions)
{
  const Tokens expectedTokens{TokenType::Out, TokenType::ZeroWithBrackets, TokenType::A,
                              TokenType::Out, TokenType::ZeroWithBrackets, TokenType::A};
  EXPECT_EQ(expectedTokens, parser.parseInstructions("out (0),a\nout (0),a"));
}

TEST_F(InstructionParserTest, ParserShouldThrowIfSecondInstructionIsInvalid)
{
  EXPECT_THROW(parser.parseInstructions("out (0),a\ninvalid"), InstructionParser::UnknownInstruction);
}

TEST_F(InstructionParserTest, ParserShouldAcceptTwoInstructionsWithEmptyLine)
{
  const Tokens expectedTokens{TokenType::Out, TokenType::ZeroWithBrackets, TokenType::A,
                              TokenType::Out, TokenType::ZeroWithBrackets, TokenType::A};
  EXPECT_EQ(expectedTokens, parser.parseInstructions("out (0),a\n\nout (0),a"));
}

TEST_F(InstructionParserTest, ParserShouldAbleToGetNumberAsToken)
{
  const Tokens expectedTokens{TokenType::Number8Bit};
  parser.parseInstructions("0");
}
