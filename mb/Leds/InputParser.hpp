#pragma once

#include <vector>
#include <string>

enum class LineContaint : uint
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

    void parseFile(std::string inputFile);
    std::vector<std::string> returnParsedFile();
private:
    std::vector<std::string> parsedInputFile;
    std::vector<std::string> outputInstrunctions;
    std::string currentInstruction;
    
    void convertFileToStringVector(std::string inputFile);
    void changeInputIntoSetOfInstructions();
    LineContaint checkLine(std::string line);
    void trimWhitespacesFromFrontAndBack(std::string& line);
};
