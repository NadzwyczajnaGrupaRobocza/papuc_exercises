#include "InputParser.hpp"

#include <regex>
#include <iostream>

InputParser::InputParser() {}


std::vector<std::string> InputParser::returnParsedFile()
{
    return outputInstrunctions;
}

void InputParser::changeInputIntoSetOfInstructions(const std::vector<std::string>& inputInstructions)
{
    for(const auto& instruction : inputInstructions)
    {
        switch (checkLine(instruction))
        {
            case LineContent::empty: 
            {
                break;
            }
            case LineContent::setRegister: 
            {
                currentInstruction = trimWhitespacesFromFrontAndBack(instruction);
                break;
            }
            case LineContent::updateLeds: 
            {
                outputInstrunctions.push_back(currentInstruction);
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

LineContent InputParser::checkLine(std::string line)
{
    const std::regex empty{"^[ \t]*$"};
    const std::regex setRegister{"^[ \t]+ld a,[[:digit:]]+[ \t]*$"};
    const std::regex updateLeds{"^[ \t]+out \\(0\\),a[ \t]*$"};

    if (std::regex_search(line, empty))
        return LineContent::empty;
    if (std::regex_search(line, setRegister))
        return LineContent::setRegister;
    if (std::regex_search(line, updateLeds))
        return LineContent::updateLeds;
    return LineContent::unknown;
    
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
