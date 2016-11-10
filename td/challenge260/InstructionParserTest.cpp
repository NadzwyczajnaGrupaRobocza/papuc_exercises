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
  EXPECT_NO_THROW(parser.parseInstructions("ld a,"));
}

TEST_F(InstructionParserTest, ParserShouldAcceptInstructionOut)
{
  const Tokens expectedTokens{Token::OutA};
  EXPECT_EQ(expectedTokens, parser.parseInstructions("out (0),a"));
}

TEST_F(InstructionParserTest, ParserShouldAcceptEmptyLine)
{
  const Tokens expectedTokens{};
  EXPECT_EQ(expectedTokens, parser.parseInstructions(""));
}

TEST_F(InstructionParserTest, ParserShouldAcceptInstructionOutWithWhitespaces)
{
  const Tokens expectedTokens{Token::OutA};
  EXPECT_EQ(expectedTokens, parser.parseInstructions(" \t    out (0),a"));
}

TEST_F(InstructionParserTest, ParserShouldAcceptTwoInstructions)
{
  const Tokens expectedTokens{Token::OutA, Token::OutA};
  EXPECT_EQ(expectedTokens, parser.parseInstructions("out (0),a\nout (0),a"));
}

TEST_F(InstructionParserTest, ParserShouldThrowIfSecondInstructionIsInvalid)
{
  EXPECT_THROW(parser.parseInstructions("out (0),a\ninvalid"), InstructionParser::UnknownInstruction);
}

TEST_F(InstructionParserTest, ParserShouldAcceptTwoInstructionsWithEmptyLine)
{
  const Tokens expectedTokens{Token::OutA, Token::OutA};
  EXPECT_EQ(expectedTokens, parser.parseInstructions("out (0),a\n\nout (0),a"));
}