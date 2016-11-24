#include <iostream>

#include "InputParser.hpp"
#include "InstructionToLedBlinkConverter.hpp"
#include "LedBlinker.hpp"

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
