#include "SemanticAnalyser.hpp"

const auto alwaysZeroValue = [](Tokens::const_iterator) { return 0 }

template <int N>
nthTokenValueCopier(Tokens::const_iterator it)
{
    for (int i = 0; i < N; ++i)
    {
        ++it;
    }
    return it->value;
}

SemanticAnalyser::SemanticAnalyser()
    : instructions{
          InstructionInfo{{TokenType::Out, TokenType::ZeroWithBracketsA},
                          InstructionType::OutA},
          InstructionInfo{{TokenType::Ld, TokenType::A}, InstructionType::LdA},
          InstructionInfo{{TokenType::Rlca}, InstructionType::Rlca}}
{
}

Instructions SemanticAnalyser::analyse(const Tokens& tokens)
{
    return analyse(tokens.cbegin(), tokens.cend());
}

Instructions SemanticAnalyser::analyse(Tokens::const_iterator begin,
                                       Tokens::const_iterator end)
{
    if (begin == end)
    {
        return {};
    }
    const auto instruction = findInstruction(begin, end);
    Instructions currentInstructions{instruction};
    const auto& nextInstructions = analyse(begin + instruction.size, end);
    std::move(nextInstructions.begin(), nextInstructions.end(),
              std::back_inserter(currentInstructions));
    return currentInstructions;
}

SemanticAnalyser::InstructionInfo
SemanticAnalyser::findInstruction(Tokens::const_iterator begin,
                                  Tokens::const_iterator end)
{
    for (const auto instruction : instructions)
    {
        if (areTokensCreatesInstruction(begin, end, instruction))
        {
            return instruction;
        }
    }
    throw InvalidSemantic{"Invalid instruction"};
}

bool SemanticAnalyser::areTokensCreatesInstruction(
    Tokens::const_iterator begin, Tokens::const_iterator end,
    const InstructionInfo& instruction)
{
    if (end - begin >= instruction.size)
    {
        auto nextExpectedToken = instruction.expectedTokens.cbegin();
        while ((begin++)->type == nextExpectedToken++)
            ;
        return nextExpectedToken == instruction.expectedTokens.cend();
    }
    return false;
}

bool SemanticAnalyser::areTokensValidOutInstruction(
    Tokens::const_iterator begin, Tokens::const_iterator end)
{
    constexpr auto sizeOfInstruction = 2;
    return end - begin >= sizeOfInstruction &&
           (begin++)->type == TokenType::Out &&
           (begin++)->type == TokenType::ZeroWithBracketsA;
}

bool SemanticAnalyser::areTokensValidLdInstruction(Tokens::const_iterator begin,
                                                   Tokens::const_iterator end)
{
    constexpr auto sizeOfInstruction = 2;
    return end - begin >= sizeOfInstruction &&
           (begin++)->type == TokenType::Ld && (begin++)->type == TokenType::A;
}

bool SemanticAnalyser::areTokensValidRlcaInstruction(
    Tokens::const_iterator begin, Tokens::const_iterator end)
{
    constexpr auto sizeOfInstruction = 1;
    return end - begin >= sizeOfInstruction &&
           (begin++)->type == TokenType::Rlca;
}
