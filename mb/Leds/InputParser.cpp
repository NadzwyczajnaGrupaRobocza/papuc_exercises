#include "InputParser.hpp"

#include <iostream>

InputParser::InputParser() {}

std::vector<uint> InputParser::getValues()
{
    return outputValues;
}

void InputParser::getSetOfValuesFromInstructions(const std::vector<std::string>& inputInstructions)
{
    for(const auto& instruction : inputInstructions)
    {
    std::string lineWithoutWS = trimWhitespacesFromFrontAndBack(instruction);
        switch (checkLineContent(lineWithoutWS))
        {
            case LineContent::empty: 
            {
                break;
            }
            case LineContent::setRegisterA: 
            {
                setCurrentValueFromInstruction(lineWithoutWS);
                break;
            }
            case LineContent::setRegisterB: 
            {
                //TO DO
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
            case LineContent::label:
            {
                //TO DO
                break;
            }
            case LineContent::endLabel:
            {
                //TO DO
                break;
            }
            case LineContent::unknown:
            {
                std::cout << "Unknown instruction:" << instruction << std::endl;
                break;
            }
            default: break;
        }
    }
}

LineContent InputParser::checkLineContent(const std::string& line)
{
    if (std::regex_search(line, setRegisterA))
        return LineContent::setRegisterA;
    if (std::regex_search(line, setRegisterB))
        return LineContent::setRegisterB;
    if (std::regex_search(line, updateLeds))
        return LineContent::updateLeds;
    if (std::regex_search(line, rlca))
        return LineContent::rlca;
    if (std::regex_search(line, rrca))
        return LineContent::rrca;
    if (std::regex_search(line, label))
        return LineContent::label;
    if (std::regex_search(line, endLabel))
        return LineContent::endLabel;
    if (std::regex_search(line, empty))
        return LineContent::empty;
    return LineContent::unknown;
    
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

void InputParser::setCurrentValueFromInstruction(const std::string& instruction)
{
    const std::string stringValue = instruction.substr( instructionPrefix.length() );
    currentValue = static_cast<uint>( std::stoi(stringValue) );
}

std::string InputParser::trimWhitespacesFromFrontAndBack(const std::string& line)
{
    const std::string whitespace = " \t";
    const auto firstAlphaChar = line.find_first_not_of(whitespace);
    if (firstAlphaChar != std::string::npos)
    {
        const auto strEnd = line.find_last_not_of(whitespace);
        const auto strRange = strEnd - firstAlphaChar + 1;
        return line.substr(firstAlphaChar, strRange);
    }
    return "";
}
