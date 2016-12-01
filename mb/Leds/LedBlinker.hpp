#pragma once

#include <vector>
#include <string>

class LedBlinker
{
public:
    LedBlinker();
    void showLedsBlinks(const std::vector<uint>& ledsSequences);
private:
    void showLedsSequence(const uint& ledsBlinks);
};

