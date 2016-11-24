#pragma once

#include <string>

class InstructionToLedBlinkConverter
{
public:
    InstructionToLedBlinkConverter();

    void convert(std::string& instruction);

private:
    std::string instructionPrefix;
    uint instructionPrefixLength;
    
    void convertInstructionToValue(std::string& line);
    void convertLineToLedSequence(std::string& line);
};
