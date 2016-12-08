#pragma once

#include <vector>
#include <string>

namespace mb_led
{

class LedBlinker
{
public:
    void showAllLedsSets(const std::vector<unsigned>& ledsSequences);
private:
    void showSingleLedsSet(const unsigned& ledsBlinks);
};

}
