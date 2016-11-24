#pragma once

#include <vector>
#include <string>

enum class LineContent : uint
{
    empty = 0,
    setRegister = 1,
    updateLeds = 2,
    unknown = 99
};

class InputParser
{
public:
    InputParser();

    void changeInputIntoSetOfInstructions(const std::vector<std::string>& inputInstructions);
    std::vector<std::string> returnParsedFile();

private:
    std::vector<std::string> outputInstrunctions;
    std::string currentInstruction;
    

    LineContent checkLine(std::string line);
    std::string trimWhitespacesFromFrontAndBack(const std::string& line);
};
