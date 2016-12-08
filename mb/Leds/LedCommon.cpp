#include "LedCommon.hpp"

#include <fstream>
#include <iostream>

namespace mb_led
{

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
        inputFile.close();
    }
    else
    {
        std::cout << "Unable to open file " << fileName;
    }
    return fileAsVector;
}


}
