#pragma once

#include <string>
#include <vector>

namespace mb_led
{

class InstructionParser
{
public:
    std::vector<std::string> getFlatInstructions(const std::vector<std::string>& input);

private:
    void prework(const std::vector<std::string>& rawInstructions);
    std::string removeWhitespacesFromEnds(const std::string& line);
    unsigned getLoopCount(std::string);
    void setLabel(const std::string& line);
    void setEndLabelRegex();
    void createFlatInstructions();

    std::string label;
    std::vector<std::string> labelContent;
    std::vector<std::string> outOfLabelInstructions;
    std::vector<std::string> flatInstructions;
};

}
