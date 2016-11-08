#include "InstructionParser.hpp"

void InstructionParser::parseInstructions(const std::string& instructions)

{
    boost::tokenizer<boost::char_separator<char>> instructionTokenizer{instructions, boost::char_separator<char>{"\n"}};
    for (const auto&token : instructionTokenizer)
    {
      parseInstruction(token);
    }
}

void InstructionParser::parseInstruction(const std::string& instruction)
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

std::string InstructionParser::trimWhitespacesOnFront(const std::string& instruction)
{
  return instruction.substr(instruction.find_first_not_of(" \t"));
}