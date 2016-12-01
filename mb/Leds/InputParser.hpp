#pragma once

#include <regex>
#include <string>
#include <vector>

enum class LineContent : uint
{
    empty = 0,
    setRegisterA,
    setRegisterB,
    updateLeds,
    rlca,
    rrca,
    label,
    endLabel,
    unknown
};

class InputParser
{
public:
    InputParser();

    void getSetOfValuesFromInstructions(const std::vector<std::string>& inputInstructions);
    std::vector<uint> getValues();

private:
    const std::regex empty{"^$"};
    const std::regex setRegisterA{"^ld a,[[:digit:]]+$"};
    const std::regex setRegisterB{"^ld b,[[:digit:]]+$"};
    const std::regex updateLeds{"^out \\(0\\),a$"};
    const std::regex rlca{"^rlca$"};
    const std::regex rrca{"^rrca$"};
    const std::regex label{"^[a-zA-Z_]+:$"};
    std::regex endLabel{"^djnz$"};

    std::string currentLabel;
    const std::string instructionPrefix{"ld a,"};

    std::vector<uint> outputValues;
    uint currentValue;

    void moveBitsToLeft();
    void moveBitsToRight();
    LineContent checkLineContent(const std::string& line);
    void setCurrentValueFromInstruction(const std::string& instruction);
    std::string trimWhitespacesFromFrontAndBack(const std::string& line);
};
