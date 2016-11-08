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
    if (instruction != "ld a," && instruction != "out (0),a")
    {
      throw UnknownInstruction{"Unknown instruction" + instruction};
    }
  }

};

TEST(InstructionParser, ParserShouldDeclineUnknownInstruction)
{
  InstructionParser parser;
  EXPECT_THROW(parser.parseInstructions("Instructions"), InstructionParser::UnknownInstruction);
}

TEST(InstructionParser, ParserShouldAcceptInstuctionLd)
{
  InstructionParser parser;
  EXPECT_NO_THROW(parser.parseInstructions("ld a,"));
}

TEST(InstructionParser, ParserShouldAcceptInstructionOut)
{
  InstructionParser parser;
  EXPECT_NO_THROW(parser.parseInstructions("out (0),a"));
}