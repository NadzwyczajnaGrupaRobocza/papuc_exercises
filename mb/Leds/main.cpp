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

    try
    {
        InputParser parser{};
        parser.changeInputIntoSetOfInstructions(convertedFile);
        std::vector<uint> ledBlinksValues = parser.returnParsedFileAsValues();
//for(const auto& a : ledBlinksValues) std::cout << a << std::endl;
        LedBlinker blinker{};
        blinker.showLedsBlinks(ledBlinksValues);

        return 0;
    }
    catch (const std::logic_error& ex)
    {
        std::cout << "Catched exception: " << ex.what() << std::endl;
        return 1;
    }
}

std::vector<std::string> convertFileToStringVector(std::string fileName)
{
    std::vector<std::string> convertedFile;
    std::ifstream inputFile{fileName};
    if( inputFile.is_open() )
    {
        std::cout << "Reading file " << fileName << std::endl;
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
