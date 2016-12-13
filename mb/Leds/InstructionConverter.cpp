#include "InstructionConverter.hpp"

#include <iostream>

#include "LedCommon.hpp"

namespace mb_led
{

std::vector<unsigned> InstructionConverter::getLedsValues()
{
    return ledsValues;
}

void InstructionConverter::instructionsToLedsValues(const std::vector<std::string>& inputInstructions)
{
    for(const auto& instruction : inputInstructions)
    {
        InstructionRegexp regexMap = initMap();
        switch (checkLineContent(instruction, regexMap))
        {
            case LineContent::setRegisterA:
            {
                setLedValue(instruction);
                break;
            }
            case LineContent::updateLeds:
            {
                ledsValues.push_back(LedValue);
                break;
            }
            case LineContent::rlca:
            {
                moveBitsToLeft();
                break;
            }
            case LineContent::rrca:
            {
                moveBitsToRight();
                break;
            }
            case LineContent::empty:
            case LineContent::setRegisterB:
            case LineContent::label:
            case LineContent::endLabel:
            case LineContent::unknown:
            {
                std::cout << "Unknown instruction =>" 
                          << instruction 
                          << "<=" << std::endl;
                break;
            }
        }
    }
}

void InstructionConverter::moveBitsToLeft()
{
    LedValue = (LedValue >= 128) ? (static_cast<std::uint8_t>(LedValue << 1) +1) :
                                   (static_cast<uint8_t>(LedValue) << 1);
}

void InstructionConverter::moveBitsToRight()
{
    LedValue = (LedValue % 2) ? (static_cast<std::uint8_t>(LedValue >> 1) + 128) :
                                (static_cast<uint8_t>(LedValue) >> 1);
}

void InstructionConverter::setLedValue(const std::string& instruction)
{
    const std::string stringValue = instruction.substr( ldaprefix.length() );
    LedValue = static_cast<unsigned>( std::stoi(stringValue) );
}

}
