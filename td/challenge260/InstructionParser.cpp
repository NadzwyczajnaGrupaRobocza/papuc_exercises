#include "InstructionParser.hpp"


#include <iostream>
#include <map>
#include "boost/tokenizer.hpp"
#include "boost/range/algorithm.hpp"

Tokens InstructionParser::parseInstructions(const std::string& instructions)

{
    boost::tokenizer<boost::char_separator<char>> instructionTokenizer{instructions, boost::char_separator<char>{"\n, "}};
    Tokens tokens;
    for (const auto&token : instructionTokenizer)
    {
      boost::copy( parseInstruction(token), std::back_inserter(tokens));
    }
    return tokens;
}

Tokens InstructionParser::parseInstruction(const std::string& instruction)
{
  const auto trimmedInstruction = trimWhitespacesOnFront(instruction);
  if (trimmedInstruction.empty())
  {
    return{};
  }
  const std::map<std::string, Token> acceptableInstructions{{"out", Token::Out}, {"(0)", Token::ZeroWithBrackets}, {"ld", Token::Ld}, {"a", Token::A}};
  const auto noArgumentInstructionPosition = acceptableInstructions.find(trimmedInstruction);
  if (noArgumentInstructionPosition != acceptableInstructions.end())
  {
    return {noArgumentInstructionPosition->second};
  }
  throw UnknownInstruction{"Unknown instruction: " + instruction};
}

std::string InstructionParser::trimWhitespacesOnFront(const std::string& instruction)
{
  const auto firstRelevantCharPosition = instruction.find_first_not_of(" \t");
  if (firstRelevantCharPosition != std::string::npos)
  {
    return instruction.substr(firstRelevantCharPosition);
  }
  return {};
}