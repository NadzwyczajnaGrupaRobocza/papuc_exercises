#include "InstructionParser.hpp"


#include <iostream>
#include <map>
#include "boost/tokenizer.hpp"
#include "boost/range/algorithm.hpp"

Tokens InstructionParser::parseInstructions(const std::string& instructions)

{
    boost::tokenizer<boost::char_separator<char>> instructionTokenizer{instructions, boost::char_separator<char>{"\n"}};
    Tokens tokens;
    for (const auto&token : instructionTokenizer)
    {
      boost::copy( parseInstruction(token), std::back_inserter(tokens));
    }
    return tokens;
}

Tokens InstructionParser::parseInstruction(const std::string& instruction)
{
  if (instruction.empty())
  {
    return{};
  }
  const auto trimmedInstruction = trimWhitespacesOnFront(instruction);
  const std::map<std::string, Token> acceptableInstructions{{"out (0),a", Token::OutA}, {"ld a,", Token::LdA}};
  const auto noArgumentInstructionPosition = acceptableInstructions.find(trimmedInstruction);
  if (noArgumentInstructionPosition != acceptableInstructions.end())
  {
    return {noArgumentInstructionPosition->second};
  }
  throw UnknownInstruction{"Unknown instruction: " + instruction};
}

std::string InstructionParser::trimWhitespacesOnFront(const std::string& instruction)
{
  return instruction.substr(instruction.find_first_not_of(" \t"));
}