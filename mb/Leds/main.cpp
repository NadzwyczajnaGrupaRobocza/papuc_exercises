#include <iostream>
#include <fstream>

#include "InputParser.hpp"
#include "LedBlinker.hpp"

using namespace mb_led;

std::vector<std::string> convertFileToStringVector(std::string);

int main()
{

    std::string inputFile = "LedSequence.txt";
    auto fileAsVector = convertFileToStringVector("LedSequence.txt");

    InputParser parser{};
    parser.getSetOfValuesFromInstructions(fileAsVector);
    std::vector<uint> ledBlinksValues = parser.getValues();
    LedBlinker blinker{};
    blinker.showLedsBlinks(ledBlinksValues);

    return 0;
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
