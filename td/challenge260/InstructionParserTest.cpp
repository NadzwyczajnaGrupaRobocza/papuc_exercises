//#include "InstructionParser.h"

#include <string>
#include <stdexcept>
#include "boost/tokenizer.hpp"

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

  void parseInstructions(const std::string& instructions)
  {
    boost::tokenizer<boost::char_separator<char>> instructionTokenizer{instructions, boost::char_separator<char>{"\n"}};
    for (const auto&token : instructionTokenizer)
    {
      parseInstruction(token);
    }
  }
private:

  void parseInstruction(const std::string& instruction)
  {
    if (instruction.empty())
    {
      return;
    }
    const std::vector<std::string> acceptableInstructions{"ld a,", "out (0),a", ""};
    if (std::find(acceptableInstructions.begin(), acceptableInstructions.end(), trimWhitespacesOnFront(instruction)) == acceptableInstructions.end())
    {
      throw UnknownInstruction{"Unknown instruction" + instruction};
    }
  }

  std::string trimWhitespacesOnFront(const std::string& instruction)
  {
    return instruction.substr(instruction.find_first_not_of(" \t"));
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