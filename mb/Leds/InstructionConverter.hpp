#pragma once

#include <regex>
#include <string>
#include <vector>

namespace mb_led
{

enum class LineContent : unsigned;

class InstructionConverter
{
public:
    void instructionsToLedsValues(const std::vector<std::string>& inputInstructions);
    std::vector<unsigned> getLedsValues();

private:
    unsigned LedValue;
    std::vector<unsigned> ledsValues;

    bool isMostSignificantBitSet();
    bool isLessSignificantBitSet();
    void moveBitsToLeft();
    void moveBitsToRight();
    void setLedValue(const std::string& instruction);
};

}
