#include "LedBlinker.hpp"

#include <iostream>
#include <bitset>

namespace mb_led
{

void LedBlinker::showAllLedsSets(const std::vector<uint>& ledsSets)
{
    for( const auto& ledsSet : ledsSets)
    {
        showSingleLedsSet(ledsSet);
    }
}

void LedBlinker::showSingleLedsSet(const uint& value)
{
    if (value < 256)
    {
        std::string ledsSet = std::bitset<8>(value).to_string('.', '*');
        std::cout << ledsSet << std::endl;
    }
    else
    {
        throw std::out_of_range{"To high value"};
    }
}

}
