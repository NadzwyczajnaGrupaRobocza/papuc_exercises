#include "SemanticAnalyser.hpp"

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
    Instructions instructions;
    if (areTokensValidLdInstruction(begin, end))
    {
        constexpr auto shiftToTokenWithValue = 1;
        instructions.push_back(
            {InstructionType::LdA, (begin + shiftToTokenWithValue)->value});
    }
    else if (areTokensValidOutInstruction(begin, end))
    {
        instructions.push_back({InstructionType::OutA, 0});
    }
    else
    {
        throw InvalidSemantic{"Invalid instruction"};
    }
    const auto& nextInstructions = analyse(begin + sizeOfInstruction, end);
    std::move(nextInstructions.begin(), nextInstructions.end(),
              std::back_inserter(instructions));
    return instructions;
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
