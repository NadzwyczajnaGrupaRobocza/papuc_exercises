#include "LedController.hpp"

#include <algorithm>
#include <bitset>

#include <iostream>

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
    if (wasLabelUsed)
    {
        instructionsFromLabel.push_back(instruction);
    }
    switch (instruction.type)
    {
    case InstructionType::OutA: out << ledState.to_string(); break;
    case InstructionType::LdA: ledState = instruction.value; break;
    case InstructionType::Rlca: ledState.rlca(); break;
    case InstructionType::Rrca: ledState.rrca(); break;
    case InstructionType::LdB: b = instruction.value; break;
    case InstructionType::Djnz: doDjnz(); break;
    case InstructionType::Label:
        instructionsFromLabel.clear();
        wasLabelUsed = true;
        break;
    }
}

void LedController::doDjnz()
{
    wasLabelUsed = false;
    if (--b)
    {
        for (const auto& instructionFromLabel : instructionsFromLabel)
        {
            runInstruction(instructionFromLabel);
        }
    }
}

std::string LedController::LedState::to_string() const
{
    return *this;
}

const LedController::LedState& LedController::LedState::
operator=(unsigned char value)
{
    ledState = value;
    return *this;
}

LedController::LedState::operator std::string() const
{
    const std::bitset<8> bitValue{ledState};
    constexpr auto ledOnChar = '*';
    constexpr auto ledOffChar = '.';
    constexpr auto lineEnding = '\n';
    return bitValue.to_string(ledOffChar, ledOnChar) + lineEnding;
}

void LedController::LedState::rlca()
{
    ledState =
        static_cast<char>((ledState << 1)) | ((ledState & 0b10000000) != 0);
}

void LedController::LedState::rrca()
{
    ledState = static_cast<char>((ledState >> 1) |
                                 (((ledState & 0b00000001) != 0) << 7));
}
