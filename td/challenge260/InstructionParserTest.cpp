//#include "InstructionParser.h"

#include <string>

#include "gtest/gtest.h"

class InstructionParser
{
public:
  void parseInstructions(const std::string &)
  {

  }
};

TEST(InstructionParser, ParserShouldAcceptAnyIntruction)
{
  InstructionParser parser;
  parser.parseInstructions("Instructions");
}