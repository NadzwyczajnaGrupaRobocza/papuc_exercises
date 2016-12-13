#pragma once

#include <map>
#include <regex>
#include <string>

namespace mb_led
{

const std::string ldaprefix = "ld a,";
const std::string ldbPrefix = "ld b,";

using InstructionRegexp = std::map<std::string, std::regex>;

enum class LineContent : unsigned
{
    empty = 0,
    setRegisterA,
    setRegisterB,
    updateLeds,
    rlca,
    rrca,
    label,
    endLabel,
    unknown
};

InstructionRegexp initMap();

unsigned stringToUnsigned(std::string);

LineContent checkLineContent(const std::string& line,
                             std::map<std::string, std::regex>& regexMap);

std::vector<std::string> convertFileToStringVector(std::string);

}
