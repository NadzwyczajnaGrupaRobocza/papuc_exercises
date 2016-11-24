#include <iostream>

#include "InputParser.hpp"
#include "InstructionToLedBlinkConverter.hpp"
#include "LedBlinker.hpp"


//MBB to remove
void printVector( const std::vector<std::string>& vect )
{
    std::cout << "printing vector" << std::endl;
    for(auto element : vect)
    {
        std::cout << element << ":";
    }
}

int main()
{
    std::string inputFile = "LedSequence.txt";
    
    InputParser parser{};
    parser.parseFile(inputFile);
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
