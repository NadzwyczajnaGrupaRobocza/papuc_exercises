#include "InstructionPreparer.hpp"

#include <iostream>
#include <regex>

#include "LedCommon.hpp"

namespace mb_led
{

void InstructionPreparer::prepare(const std::vector<std::string>& rawInstructions)
{
    bool isInstructionInLabel{false};
    for(const auto& line : rawInstructions)
    {
        std::string instructionFromLine = removeWhitespacesFromEnds(line);
        switch (checkLineContent(instructionFromLine))
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
                                     : preparedInstructions.push_back(instructionFromLine);
                break;
            }
            case LineContent::setRegisterB:
            {
                uint loopCount = getLoopCount(instructionFromLine);
                std::vector<std::string> registerBLabels{loopCount, "label"};
                preparedInstructions.insert(preparedInstructions.end(),
                                            registerBLabels.begin(),
                                            registerBLabels.end());
                break;
            }
            case LineContent::label:
            {
                setLabel(instructionFromLine);
                setEndLabelRegExpr();
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

    replaceLdbByLabel();

}

std::vector<std::string> InstructionPreparer::getPreparedInstructions()
{
    return output;
}


std::string InstructionPreparer::removeWhitespacesFromEnds(const std::string& line)
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

uint InstructionPreparer::getLoopCount(std::string line)
{
    const std::string stringValue = line.substr( ldbPrefix.length() );
    return static_cast<uint>(std::stoi(stringValue));
}

void InstructionPreparer::setLabel(const std::string& line)
{
    label = line.substr(0, line.length() - 1);
}

void InstructionPreparer::setEndLabelRegExpr()
{
    InstructionRegexp["endLabel"] = std::regex{"^djnz " + label + "$"};
}

void InstructionPreparer::replaceLdbByLabel() //MBB rename
{
    for(auto aaa : preparedInstructions)
    {
        if(aaa == "label")
        {
            output.insert(output.end(),
                          labelContent.begin(),
                          labelContent.end());
        }
        else
        {
            output.push_back(aaa);
        }
    }
}

}
