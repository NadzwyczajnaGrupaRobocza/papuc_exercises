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
  EXPECT_THROW(parser.parseInstructions("ld a,"), InstructionParser::MissingArgument);
}

TEST_F(InstructionParserTest, ParserShouldAcceptInstructionOut)
{
  EXPECT_NO_THROW(parser.parseInstructions("out (0),a"));
}

TEST_F(InstructionParserTest, ParserShouldAcceptEmptyLine)
{
  EXPECT_NO_THROW(parser.parseInstructions(""));
}

TEST_F(InstructionParserTest, ParserShouldAcceptInstructionOutWithWhitespaces)
{
  EXPECT_NO_THROW(parser.parseInstructions(" \t    out (0),a"));
}

TEST_F(InstructionParserTest, ParserShouldAcceptTwoInstructions)
{
  EXPECT_NO_THROW(parser.parseInstructions("out (0),a\nout (0),a"));
}

TEST_F(InstructionParserTest, ParserShouldThrowIfSecondInstructionIsInvalid)
{
  EXPECT_THROW(parser.parseInstructions("out (0),a\ninvalid"), InstructionParser::UnknownInstruction);
}

TEST_F(InstructionParserTest, ParserShouldAcceptTwoInstructionsWithEmptyLine)
{
  EXPECT_NO_THROW(parser.parseInstructions("out (0),a\n\nout (0),a"));
}