#include "InputParser.hpp"

#include <iostream>

#include "LedCommon.hpp"

namespace mb_led
{

std::vector<uint> InputParser::getValues()
{
    return outputValues;
}

void InputParser::getSetOfValuesFromInstructions(const std::vector<std::string>& inputInstructions)
{
    for(const auto& instruction : inputInstructions)
    {
        switch (checkLineContent(instruction))
        {
            case LineContent::setRegisterA:
            {
                setCurrentValue(instruction);
                break;
            }
            case LineContent::updateLeds:
            {
                outputValues.push_back(currentValue);
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
                std::cout << "Unknown instruction ==>" 
                          << instruction 
                          << "<==" << std::endl;
                break;
            }
            default: break;
        }
    }
}

void InputParser::moveBitsToLeft()
{
    currentValue = (currentValue >= 128) ? (static_cast<uint8_t>(currentValue << 1) +1) :
                                           (static_cast<uint>(currentValue) << 1);
}

void InputParser::moveBitsToRight()
{
    currentValue = (currentValue % 2) ? (static_cast<uint8_t>(currentValue >> 1) + 128) :
                                        (static_cast<uint>(currentValue) >> 1);
}

void InputParser::setCurrentLabel(const std::string& line)
{
    currentLabel = line.substr( 0, line.length() - 1 );
}

void InputParser::setCurrentValue(const std::string& instruction)
{
    const std::string stringValue = instruction.substr( ldaprefix.length() );
    currentValue = static_cast<uint>( std::stoi(stringValue) );
}

}
