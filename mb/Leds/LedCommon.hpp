#pragma once

#include <map>
#include <regex>
#include <string>

namespace mb_led
{

const std::string ldaprefix = "ld a,";
const std::string ldbPrefix = "ld b,";

enum class LineContent : uint
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

static std::map<std::string, std::regex> InstructionRegexp {
    {"empty", std::regex{"^[ \t]*$"}},
    {"setRegisterA", std::regex{"^ld a,[[:digit:]]+$"}},
    {"setRegisterB", std::regex{"^ld b,[[:digit:]]+$"}},
    {"updateLeds", std::regex{"^out \\(0\\),a$"}},
    {"rlca", std::regex{"^rlca$"}},
    {"rrca", std::regex{"^rrca$"}},
    {"label", std::regex{"^[a-zA-Z_]+:$"}},
    {"endLabel", std::regex{"^$"}}};

LineContent checkLineContent(const std::string& line,
                             std::map<std::string, std::regex>& regexMap);

std::vector<std::string> convertFileToStringVector(std::string);

}
