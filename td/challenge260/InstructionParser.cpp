#include "InstructionParser.hpp"


#include <iostream>
#include <vector>
#include <utility>
#include <regex>
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
  using TextToTokens = std::vector<std::pair<std::regex, Token>>;
  const TextToTokens acceptableInstructions{{std::regex{"out"}, Token::Out},
                                            {std::regex{"\\(0\\)"}, Token::ZeroWithBrackets},
                                            {std::regex{"ld"}, Token::Ld},
                                            {std::regex{"a"}, Token::A}};
  const auto noArgumentInstructionPosition = std::find_if(acceptableInstructions.begin(), acceptableInstructions.end(), [&](const auto& tokenMap)
      {
        return std::regex_match(trimmedInstruction, tokenMap.first);
      });
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