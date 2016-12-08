#pragma once

#include <vector>
#include <string>

namespace mb_led
{

class LedBlinker
{
public:
    void showAllLedsSets(const std::vector<uint>& ledsSequences);
private:
    void showSingleLedsSet(const uint& ledsBlinks);
};

}
