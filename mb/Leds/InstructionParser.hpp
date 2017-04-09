#pragma once

#include <string>
#include <vector>

#include "LedCommon.hpp"

namespace mb_led
{

using flatInstructions = std::vector<std::string>;

class InstructionParser
{
public:
    InstructionParser();
    std::vector<std::string> getFlatInstructions(const std::vector<std::string>& input);

private:
    void prework(const std::vector<std::string>& rawInstructions);
    unsigned getLoopCount(std::string);
    void setLabel(const std::string& line);
    void setEndLabelRegex();
    flatInstructions createFlatInstructions();

    InstructionRegexp regexMap;
    std::string label;
    std::vector<std::string> labelContent;
    std::vector<std::string> outOfLabelInstructions;
//    std::vector<std::string> flatInstructions;
};

}
