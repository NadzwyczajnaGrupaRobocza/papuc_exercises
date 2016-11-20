#include "LedController.hpp"

#include <bitset>
#include <algorithm>

LedController::LedController(std::ostream &stream) :
    out {stream}
{
}

void LedController::runProgram(const Instructions &instructions)
{
  for (const auto &instruction : instructions)
  {
    runInstruction(instruction);
  }
}

void LedController::runInstruction(const Instruction & instruction)
{
  switch (instruction.type)
  {
    case InstructionType::OutA:
      out << ledState;
      break;
    case InstructionType::LdA:
      ledState = getLedStateFromInteger(instruction.value);
      break;
  }
}

std::string LedController::getLedStateFromInteger(unsigned value)
{
  const std::bitset<8> bitValue {value};
  std::stringstream stream;
  stream << bitValue;
  auto text = stream.str();
  std::transform(text.cbegin(), text.cend(), text.begin(), [](const auto character)
  {
    if (character == '1')
    {
      constexpr auto ledOnChar = '*';
      return ledOnChar;
    }
    else
    {
      constexpr auto ledOffChar = '.';
      return ledOffChar;
    }
  });
  return text + '\n';
}