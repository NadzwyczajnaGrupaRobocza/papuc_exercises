#include "InstructionLexer.hpp"

#include <iostream>
#include <vector>
#include <utility>
#include <functional>
#include <regex>

#include "boost/tokenizer.hpp"
#include "boost/range/algorithm.hpp"

Tokens InstructionLexer::parseInstructions(const std::string& input)
{
    boost::tokenizer<boost::char_separator<char>> lineTokenizer{input, boost::char_separator<char>{"\n"}};
    Tokens tokens;
    for (const auto&line : lineTokenizer)
    {
      if (line.at(0) != ' ')
      {
	  throw UnknownInstruction("Invalid line: " + line);
      }
      boost::copy(parseLine(line), std::back_inserter(tokens));
    }
    return tokens;
}

Tokens InstructionLexer::parseLine(const std::string& line)
{
    boost::tokenizer<boost::char_separator<char>> instructionTokenizer{line, boost::char_separator<char>{", "}};
    Tokens tokens;
    for (const auto&token : instructionTokenizer)
    {
      boost::copy(parseInstruction(token), std::back_inserter(tokens));
    }
    return tokens;
}

const auto alwaysZeroValue = [](const std::string&) -> Token::ValueType
{
  return 0;
};

const auto convertToUnsigned = [](const std::string& text) -> Token::ValueType
{
  try
  {
    return std::stoi(text);
  }
  catch (const std::exception &)
  {
    return 0;
  }
};

Tokens InstructionLexer::parseInstruction(const std::string& instruction)
{
  const auto trimmedInstruction = trimWhitespacesOnFront(instruction);
  if (trimmedInstruction.empty())
  {
    return{};
  }
  using TextToTokens = std::vector<std::tuple<std::regex, TokenType, std::function<Token::ValueType(const std::string&)>>>;
  const TextToTokens acceptableInstructions{{std::regex{"out"}, TokenType::Out, alwaysZeroValue},
                                            {std::regex{"\\(0\\)"}, TokenType::ZeroWithBrackets, alwaysZeroValue},
                                            {std::regex{"ld"}, TokenType::Ld, alwaysZeroValue},
                                            {std::regex{"a"}, TokenType::A, alwaysZeroValue},
                                            {std::regex{"[0-9]{1,2}|1[0-9]{1,2}|2[0-4][0-9]|25[0-5]"}, TokenType::Number8Bit, convertToUnsigned}};
  const auto noArgumentInstructionPosition = std::find_if(acceptableInstructions.begin(), acceptableInstructions.end(), [&](const auto& tokenMap)
      {
        return std::regex_match(trimmedInstruction, std::get<0>(tokenMap));
      });
  if (noArgumentInstructionPosition != acceptableInstructions.end())
  {
    return {{std::get<1>(*noArgumentInstructionPosition), std::get<2>(*noArgumentInstructionPosition)(trimmedInstruction)}};
  }
  throw UnknownInstruction{"Unknown instruction: " + instruction};
}

std::string InstructionLexer::trimWhitespacesOnFront(const std::string& instruction)
{
  const auto firstRelevantCharPosition = instruction.find_first_not_of(" \t");
  if (firstRelevantCharPosition != std::string::npos)
  {
    return instruction.substr(firstRelevantCharPosition);
  }
  return {};
}
