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
    throw UnknownInstruction{"Unknown instruction" + instruction};
  }
};

TEST(InstructionParser, ParserShouldDeclineUnknownInstruction)
{
  InstructionParser parser;
  EXPECT_THROW(parser.parseInstructions("Instructions"), InstructionParser::UnknownInstruction);
}