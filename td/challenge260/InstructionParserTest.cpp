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

  class MissingArgument : public std::runtime_error
  {
  public:
    MissingArgument(const std::string& msg) : std::runtime_error{msg}
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
    const auto trimmedInstruction = trimWhitespacesOnFront(instruction);
    const std::vector<std::string> acceptableInstructions{"out (0),a"};
    const std::vector<std::string> acceptableInstructionsWithArgument{"ld a,"};
    if (std::find(acceptableInstructions.begin(), acceptableInstructions.end(), trimmedInstruction) != acceptableInstructions.end())
    {
      return;
    }
    const auto instructionPosition = std::find_if(acceptableInstructionsWithArgument.begin(), acceptableInstructionsWithArgument.end(), [&](const auto& instructionTemplate)
          {
            return instructionTemplate == trimmedInstruction.substr(0, instructionTemplate.size());
          });
    if (instructionPosition != acceptableInstructions.end())
    {
      if (*instructionPosition == trimmedInstruction)
      {
        throw MissingArgument{"Missing argument for: " + instruction};
      }
    }
    throw UnknownInstruction{"Unknown instruction: " + instruction};
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