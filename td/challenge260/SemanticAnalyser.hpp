#pragma once

#include "Instruction.hpp"
#include "Token.hpp"

class SemanticAnalyser
{
public:
    class InvalidSemantic : public std::runtime_error
    {
    public:
        InvalidSemantic(const std::string& msg) : std::runtime_error{msg}
        {
        }
    };

    Instructions analyse(const Tokens& tokens);

private:
    static constexpr auto sizeOfInstruction = 3u;

    bool areTokensValidOutInstruction(Tokens::const_iterator begin);
    bool areTokensValidLdInstruction(Tokens::const_iterator begin);
};
