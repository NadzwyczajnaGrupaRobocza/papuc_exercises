#pragma once

#include <regex>
#include <string>
#include <vector>

namespace mb_led
{

enum class LineContent : uint;

class InstructionConverter
{
public:
    void instructionsToLedsValues(const std::vector<std::string>& inputInstructions);
    std::vector<uint> getLedsValues();

private:
    uint LedValue;
    std::vector<uint> ledsValues;

    void moveBitsToLeft();
    void moveBitsToRight();
    void setLedValue(const std::string& instruction);
};

}
