#pragma once

#include <vector>
#include <string>

class LedBlinker
{
public:
    LedBlinker(const std::vector<std::string>& input);
    void showLeds();
private:
    std::vector<std::string> ledsSequences;
};

