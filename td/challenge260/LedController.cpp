#include "LedController.hpp"

#include <algorithm>
#include <bitset>

LedController::LedController(std::ostream& stream) : out{stream}
{
}

void LedController::runProgram(const Instructions& instructions)
{
    for (const auto& instruction : instructions)
    {
        runInstruction(instruction);
    }
}

void LedController::runInstruction(const Instruction& instruction)
{
    switch (instruction.type)
    {
    case InstructionType::OutA: out << ledState; break;
    case InstructionType::LdA:
        ledState = getLedStateFromInteger(instruction.value);
        break;
    case InstructionType::Rlca: break;
    case InstructionType::LdB: break;
    }
}

std::string LedController::getLedStateFromInteger(unsigned value)
{
    const std::bitset<8> bitValue{value};
    constexpr auto ledOnChar = '*';
    constexpr auto ledOffChar = '.';
    constexpr auto lineEnding = '\n';
    return bitValue.to_string(ledOffChar, ledOnChar) + lineEnding;
}
