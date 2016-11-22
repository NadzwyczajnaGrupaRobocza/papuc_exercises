#pragma once

#include "Token.hpp"
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

    Tokens parseInstructions(const std::string&);

private:
    Tokens parseInstruction(const std::string&);
    Tokens parseLine(const std::string&);
    std::string trimWhitespacesOnFront(const std::string& instruction);
};
