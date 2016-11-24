#include "InputParser.hpp"

#include <regex>
#include <fstream>
#include <iostream>

InputParser::InputParser() {}

void InputParser::parseFile(std::string inputFile)
{
    convertFileToStringVector(inputFile);
    changeInputIntoSetOfInstructions();
}

std::vector<std::string> InputParser::returnParsedFile()
{
    return outputInstrunctions;
}

void InputParser::convertFileToStringVector(std::string fileName)
{
    std::ifstream inputFile{fileName};
    if( inputFile.is_open() )
    {
        std::string line;
        while( getline(inputFile,line) )
        {
            parsedInputFile.push_back(line);
        }
        inputFile.close();
    }
    else
    {
        std::cout << "Unable to open file " << fileName;
    }
}

void InputParser::changeInputIntoSetOfInstructions()
{
    for(auto& line : parsedInputFile)
    {
        switch (checkLine(line))
        {
            case LineContaint::empty: 
            {
                break;
            }
            case LineContaint::setRegister: 
            {
                trimWhitespacesFromFrontAndBack(line);
                currentInstruction = line;
                break;
            }
            case LineContaint::updateLeds: 
            {
                outputInstrunctions.push_back(currentInstruction);
                break;
                
            }
            case LineContaint::unknown:
            {
                std::cout << "Unknown instruction:" << line << std::endl;
                break;
            }
            default: break;
        }
    }
}

LineContaint InputParser::checkLine(std::string line)
{
    const std::regex empty{"^$"};
    const std::regex setRegister{"^[ \t]+ld a,[[:digit:]]+$"};
    const std::regex updateLeds{"^[ \t]+out \\(0\\),a$"};

    if (std::regex_search(line, empty))
        return LineContaint::empty;
    if (std::regex_search(line, setRegister))
        return LineContaint::setRegister;
    if (std::regex_search(line, updateLeds))
        return LineContaint::updateLeds;
    return LineContaint::unknown;
    
}

void InputParser::trimWhitespacesFromFrontAndBack(std::string& line)
{
    const std::string whitespace = " \t";
    
    const auto firstAlphaChar = line.find_first_not_of(whitespace);
    if (firstAlphaChar != std::string::npos)
    {
        const auto strEnd = line.find_last_not_of(whitespace);
        const auto strRange = strEnd - firstAlphaChar + 1;

        line = line.substr(firstAlphaChar, strRange);
    }
}
