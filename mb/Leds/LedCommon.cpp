#include "LedCommon.hpp"

#include <fstream>
#include <iostream>

namespace mb_led
{

InstructionRegexp initMap()
{
    InstructionRegexp map = {
                     {"empty", std::regex{"^[ \t]*$"}},
                     {"setRegisterA", std::regex{"^ld a,[[:digit:]]+$"}},
                     {"setRegisterB", std::regex{"^ld b,[[:digit:]]+$"}},
                     {"updateLeds", std::regex{"^out \\(0\\),a$"}},
                     {"rlca", std::regex{"^rlca$"}},
                     {"rrca", std::regex{"^rrca$"}},
                     {"label", std::regex{"^[a-zA-Z_]+:$"}},
                     {"endLabel", std::regex{"^$"}}};
    return map;
}

LineContent checkLineContent(const std::string& line,
                             std::map<std::string, std::regex>& regexMap)
{
    if (std::regex_search(line, regexMap["empty"]))
        return LineContent::empty;
    if (std::regex_search(line, regexMap["setRegisterA"]))
        return LineContent::setRegisterA;
    if (std::regex_search(line, regexMap["setRegisterB"]))
        return LineContent::setRegisterB;
    if (std::regex_search(line, regexMap["updateLeds"]))
        return LineContent::updateLeds;
    if (std::regex_search(line, regexMap["rlca"]))
        return LineContent::rlca;
    if (std::regex_search(line, regexMap["rrca"]))
        return LineContent::rrca;
    if (std::regex_search(line, regexMap["label"]))
        return LineContent::label;
    if (std::regex_search(line, regexMap["endLabel"]))
        return LineContent::endLabel;
    return LineContent::unknown;
}

unsigned stringToUnsigned(std::string sValue)
{
    return static_cast<unsigned>(std::stoi(sValue));
}

std::vector<std::string> convertFileToStringVector(std::string fileName)
{
    std::vector<std::string> fileAsVector;
    std::ifstream inputFile{fileName};
    if( inputFile.is_open() )
    {
        std::cout << "Reading file " << fileName << std::endl;
        std::string line;
        while( getline(inputFile,line) )
        {
            fileAsVector.push_back(line);
        }
    }
    else
    {
        std::cout << "Unable to open file " << fileName;
    }
    return fileAsVector;
}


}
