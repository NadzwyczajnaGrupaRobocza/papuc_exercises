//#include "InstructionParser.h"

#include <string>
#include <stdexcept>

#include "gtest/gtest.h"

class InstructionParser
{
public:
  class UnknownInstruction : public std::runtime_error
  {
  public:
    UnknownInstruction(const std::string& msg) : std::runtime_error{msg}
    {}
  };

  void parseInstructions(const std::string& instruction)
  {
    if (instruction.empty())
    {
      return;
    }
    const std::vector<std::string> acceptableInstructions{"ld a,", "out (0),a", ""};
    if (std::find(acceptableInstructions.begin(), acceptableInstructions.end(), instruction.substr(instruction.find_first_not_of(" \t"))) == acceptableInstructions.end())
    {
      throw UnknownInstruction{"Unknown instruction" + instruction};
    }
  }

};

using namespace ::testing;

struct InstructionParserTest : public Test
{
  InstructionParser parser;
};

TEST_F(InstructionParserTest, ParserShouldDeclineUnknownInstruction)
{
  EXPECT_THROW(parser.parseInstructions("Instructions"), InstructionParser::UnknownInstruction);
}

TEST_F(InstructionParserTest, ParserShouldAcceptInstuctionLd)
{
  EXPECT_NO_THROW(parser.parseInstructions("ld a,"));
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