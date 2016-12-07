#pragma once

#include <regex>
#include <string>
#include <vector>

namespace mb_led
{

enum class LineContent : uint;

class InputParser
{
public:
    void getSetOfValuesFromInstructions(const std::vector<std::string>& inputInstructions);
    std::vector<uint> getValues();

private:
    std::string currentLabel;
    uint currentValue;
    std::vector<uint> outputValues;

    void moveBitsToLeft();
    void moveBitsToRight();
    void setCurrentValue(const std::string& instruction);
    void setCurrentLabel(const std::string& instruction);
    void setEndLabelRegExpr();
};

}
