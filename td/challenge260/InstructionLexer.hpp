#pragma once

#include "Token.hpp"

#include <map>
#include <regex>
#include <stdexcept>
#include <string>

class InstructionLexer
{
public:
    class UnknownInstruction : public std::runtime_error
    {
    public:
        UnknownInstruction(const std::string& msg) : std::runtime_error{msg}
        {
        }
    };

    class UnknownLabel : public std::runtime_error
    {
    public:
        UnknownLabel(const std::string& msg) : std::runtime_error{msg}
        {
        }
    };

    Tokens parseInstructions(const std::string&);

private:
    Tokens parseInstruction(const std::string&);
    Tokens parseLine(const std::string&);
    Tokens parseLabel(const std::string&);
    std::string trimWhitespacesOnFront(const std::string&);
    bool regexMatcher(const std::string&, const std::regex&);
    Token::ValueType getLabelValue(const std::string&);
    Token::ValueType getExistingLabelValue(const std::string&);
    const std::string getUint8RegexWithPrefix(const std::string&);

    std::map<std::string, Token::ValueType> labels;
    Token::ValueType nextLabelValue{0};
};
