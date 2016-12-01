#pragma once

#include <regex>
#include <string>
#include <vector>

enum class LineContent : uint
{
    empty = 0,
    setRegister = 1,
    updateLeds = 2,
    rlca = 3,
    rrca = 4,
//    label = ,
//    label_end = ,
    unknown = 99
};

class InputParser
{
public:
    InputParser();

    void changeInputIntoSetOfInstructions(const std::vector<std::string>& inputInstructions);
    std::vector<uint> returnParsedFileAsValues(); //MBB to zamienic

private:
    const std::regex empty{"^$"};
    const std::regex setRegister{"^ld a,[[:digit:]]+$"};
    const std::regex updateLeds{"^out \\(0\\),a$"};
    const std::regex rlca{"^rlca$"};
    const std::regex rrca{"^rrca$"};
    
    const std::string instructionPrefix{"ld a,"};

    std::vector<uint> intOutputInstrunctions;
    uint currentValue;

    void moveBitsToLeft();
    void moveBitsToRight();
    LineContent checkLine(const std::string& line);
    void setCurrentValueFromInstruction(const std::string& instruction);
    std::string trimWhitespacesFromFrontAndBack(const std::string& line);
};
