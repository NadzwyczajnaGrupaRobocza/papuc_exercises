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

    SemanticAnalyser();

    Instructions analyse(const Tokens& tokens);

private:
    class InstructionInfo
    {
    public:
        using Tokens = std::vector<TokenType>;
        using ValueGetter = std::function<Instruction::ValueType(
            Tokens::const_iterator)>;
        InstructionInfo(Tokens tokens, InstructionType instructionInit,
                        ValueGetter valueGetter)
            : expectedTokens{std::move(tokens)}, instruction(instructionInit),
              getValue{valueGetter}
        {
        }
        const Tokens expectedTokens;
        const Tokens::size_type size = expectedTokens.size();
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
    bool areTokensValidOutInstruction(Tokens::const_iterator begin,
                                      Tokens::const_iterator end);
    bool areTokensValidLdInstruction(Tokens::const_iterator begin,
                                     Tokens::const_iterator end);
    bool areTokensValidRlcaInstruction(Tokens::const_iterator begin,
                                       Tokens::const_iterator end);
    unsigned instructinoShif(InstructionType instruction)
    {
        switch (instruction)
        {
        case InstructionType::Rlca: return 1;
        case InstructionType::LdA:
        case InstructionType::OutA: return 2;
        }
        return 0;
    }

    const InstructionsInfo instructions;
};
