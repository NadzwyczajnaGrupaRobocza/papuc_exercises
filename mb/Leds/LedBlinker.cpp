#include "LedBlinker.hpp"

#include <iostream>
#include <bitset>

namespace mb_led
{

LedBlinker::LedBlinker()
{}

void LedBlinker::showLedsBlinks(const std::vector<uint>& ledsSequences)
{
    for( const auto& ledsBlinks : ledsSequences)
    {
        showLedsSequence(ledsBlinks);
    }
}

void LedBlinker::showLedsSequence(const uint& value)
{
    if (value < 256)
    {
        std::string ledsBlinks = std::bitset<8>(value).to_string('.', '*');
        std::cout << ledsBlinks << std::endl;
    }
    else
    {
        throw std::out_of_range{"To high value"};
    }
}

}
