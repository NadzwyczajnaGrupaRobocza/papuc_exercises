#pragma once

#include <functional>

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

    SemanticAnalyser();

    Instructions analyse(const Tokens& tokens);

private:
    class InstructionInfo
    {
    public:
        using TokenTypes = std::vector<TokenType>;
        using ValueGetter =
            std::function<Instruction::ValueType(Tokens::const_iterator)>;
        InstructionInfo(TokenTypes tokens, InstructionType instructionInit,
                        ValueGetter valueGetter)
            : expectedTokens{std::move(tokens)}, instruction(instructionInit),
              getValue{valueGetter}
        {
        }
        const TokenTypes expectedTokens;
        const TokenTypes::size_type size = expectedTokens.size();
        const InstructionType instruction;
        const ValueGetter getValue;
    };
    using InstructionsInfo = std::vector<InstructionInfo>;

    Instructions analyse(Tokens::const_iterator, Tokens::const_iterator);
    InstructionInfo findInstruction(Tokens::const_iterator,
                                    Tokens::const_iterator);
    bool areTokensCreatesInstruction(Tokens::const_iterator,
                                     Tokens::const_iterator,
                                     const InstructionInfo&);
    Instruction convertInstructionInfoToInstruction(Tokens::const_iterator,
                                                    InstructionInfo);

    const InstructionsInfo instructions;
};
