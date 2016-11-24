#include <iostream>
#include <fstream>

#include "InputParser.hpp"
#include "InstructionToLedBlinkConverter.hpp"
#include "LedBlinker.hpp"

std::vector<std::string> convertFileToStringVector(std::string);

int main()
{
    std::string inputFile = "LedSequence.txt";
    auto convertedFile = convertFileToStringVector("LedSequence.txt");

    InputParser parser{};
    parser.changeInputIntoSetOfInstructions(convertedFile);
    std::vector<std::string> ledBlinks = parser.returnParsedFile();

    InstructionToLedBlinkConverter converter{};
    for(auto& instruction : ledBlinks)
    {
        converter.convert(instruction);
    }

    LedBlinker blinker{ledBlinks};
    blinker.showLeds();
    return 0;
}

std::vector<std::string> convertFileToStringVector(std::string fileName)
{
    std::vector<std::string> convertedFile;
    std::ifstream inputFile{fileName};
    if( inputFile.is_open() )
    {
        std::string line;
        while( getline(inputFile,line) )
        {
            convertedFile.push_back(line);
        }
        inputFile.close();
    }
    else
    {
        std::cout << "Unable to open file " << fileName;
    }
    return convertedFile;
}
