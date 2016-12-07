#pragma once

#include <string>
#include <vector>

namespace mb_led
{

class InstructionPreparer
{
public:
    void prepare(const std::vector<std::string>& rawInstructions);
    std::vector<std::string> getPreparedInstructions();

private:
    std::string removeWhitespacesFromEnds(const std::string& line);
    uint getLoopCount(std::string);
    void setLabel(const std::string& line);
    void setEndLabelRegExpr();
    void replaceLdbByLabel();

    std::string label;
    std::vector<std::string> labelContent;
    std::vector<std::string> preparedInstructions;
    std::vector<std::string> output;
};

}
