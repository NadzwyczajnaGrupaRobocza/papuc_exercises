#include <iostream>

#include "LedCommon.hpp"
#include "InstructionParser.hpp"
#include "InstructionConverter.hpp"
#include "LedBlinker.hpp"

using namespace mb_led;

int main()
{

    std::string inputFile = "LedSequence.txt";
    const auto vectorizedFile = convertFileToStringVector("LedSequence.txt");

    InstructionParser parser{};
    const auto flatInstructions = parser.getFlatInstructions(vectorizedFile);
    InstructionConverter converter{};
    converter.instructionsToLedsValues(flatInstructions);
    std::vector<uint> ledBlinksValues = converter.getLedsValues();
    LedBlinker blinker{};
    blinker.showAllLedsSets(ledBlinksValues);

    return 0;
}
