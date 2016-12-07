#include "LedCommon.hpp"

namespace mb_led
{

LineContent checkLineContent(const std::string& line)
{
    if (std::regex_search(line, InstructionRegexp["empty"]))
        return LineContent::empty;
    if (std::regex_search(line, InstructionRegexp["setRegisterA"]))
        return LineContent::setRegisterA;
    if (std::regex_search(line, InstructionRegexp["setRegisterB"]))
        return LineContent::setRegisterB;
    if (std::regex_search(line, InstructionRegexp["updateLeds"]))
        return LineContent::updateLeds;
    if (std::regex_search(line, InstructionRegexp["rlca"]))
        return LineContent::rlca;
    if (std::regex_search(line, InstructionRegexp["rrca"]))
        return LineContent::rrca;
    if (std::regex_search(line, InstructionRegexp["label"]))
        return LineContent::label;
    if (std::regex_search(line, InstructionRegexp["endLabel"]))
        return LineContent::endLabel;
    return LineContent::unknown;
}

}
