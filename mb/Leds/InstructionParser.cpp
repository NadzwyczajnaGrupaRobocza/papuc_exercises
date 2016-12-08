#include "InstructionParser.hpp"

#include <iostream>
#include <regex>

#include "LedCommon.hpp"

namespace mb_led
{

std::vector<std::string> InstructionParser::getFlatInstructions(const std::vector<std::string>& input)
{
    prework(input);
    createFlatInstructions();
    return flatInstructions;
}


void InstructionParser::prework(const std::vector<std::string>& rawInstructions)
{
    bool isInstructionInLabel{false};
    for(const auto& line : rawInstructions)
    {
        std::string instructionFromLine = removeWhitespacesFromEnds(line);
        switch (checkLineContent(instructionFromLine, InstructionRegexp))
        {
            case LineContent::empty:
            {
                break;
            }
            case LineContent::setRegisterA:
            case LineContent::updateLeds:
            case LineContent::rlca:
            case LineContent::rrca:
            {
                isInstructionInLabel ? labelContent.push_back(instructionFromLine)
                                     : outOfLabelInstructions.push_back(instructionFromLine);
                break;
            }
            case LineContent::setRegisterB:
            {
                uint loopCount = getLoopCount(instructionFromLine);
                std::vector<std::string> registerBLabels{loopCount, ldbPrefix};
                outOfLabelInstructions.insert(outOfLabelInstructions.end(),
                                            registerBLabels.begin(),
                                            registerBLabels.end());
                break;
            }
            case LineContent::label:
            {
                setLabel(instructionFromLine);
                setEndLabelRegex();
                isInstructionInLabel = true;
                break;
            }
            case LineContent::endLabel:
            {
                isInstructionInLabel = false;
                break;
            }
            case LineContent::unknown:
            {
                std::cout << "Unknown instruction ==>" 
                          << instructionFromLine 
                          << "<==" << std::endl;
                break;
            }
            default:
            {
                break;
            }
        }
    }
}

std::string InstructionParser::removeWhitespacesFromEnds(const std::string& line)
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

uint InstructionParser::getLoopCount(std::string line)
{
    const std::string stringValue = line.substr( ldbPrefix.length() );
    return static_cast<uint>(std::stoi(stringValue));
}

void InstructionParser::setLabel(const std::string& line)
{
    label = line.substr(0, line.length() - 1);
}

void InstructionParser::setEndLabelRegex()
{
    const std::string endLabel = "^djnz " + label + "$";
    InstructionRegexp["endLabel"] = std::regex{endLabel};
}

void InstructionParser::createFlatInstructions()
{
    for(auto instruction : outOfLabelInstructions)
    {
        if(instruction == ldbPrefix)
        {
            flatInstructions.insert(flatInstructions.end(),
                                    labelContent.begin(),
                                    labelContent.end());
        }
        else
        {
            flatInstructions.push_back(instruction);
        }
    }
}

}
