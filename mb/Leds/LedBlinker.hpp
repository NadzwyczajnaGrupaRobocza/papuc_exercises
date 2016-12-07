#pragma once

#include <vector>
#include <string>

namespace mb_led
{

class LedBlinker
{
public:
    LedBlinker();
    void showLedsBlinks(const std::vector<uint>& ledsSequences);
private:
    void showLedsSequence(const uint& ledsBlinks);
};

}
