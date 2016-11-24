#include "LedBlinker.hpp"

#include <iostream>

LedBlinker::LedBlinker(const std::vector<std::string>& input)
    : ledsSequences{std::move( input )}
{}

void LedBlinker::showLeds()
{
    for( auto ledsBlinks : ledsSequences)
    {
        std::cout << ledsBlinks << std::endl; 
    }
}
