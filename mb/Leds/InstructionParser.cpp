#include "InstructionParser.hpp"

#include <iostream>
#include <regex>

#include <boost/algorithm/string/trim.hpp>

#include "LedCommon.hpp"

namespace mb_led
{

InstructionParser::InstructionParser()
{
    regexMap = initMap();
}

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
        std::string instructionFromLine = boost::algorithm::trim_copy(line);
        switch (checkLineContent(instructionFromLine, regexMap))
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
                unsigned loopCount = getLoopCount(instructionFromLine);
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

unsigned InstructionParser::getLoopCount(std::string line)
{
    const std::string stringValue = line.substr( ldbPrefix.length() );
    return stringToUnsigned(stringValue);
}

void InstructionParser::setLabel(const std::string& line)
{
    label = line.substr(0, line.length() - 1);
}

void InstructionParser::setEndLabelRegex()
{
    const std::string endLabel = "^djnz " + label + "$";
    regexMap["endLabel"] = std::regex{endLabel};
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
