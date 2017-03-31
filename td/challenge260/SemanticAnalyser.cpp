#include "SemanticAnalyser.hpp"

#include <algorithm>
#include <iterator>

template <int N>
Instruction::ValueType nthTokenValueGetter(Tokens::const_iterator it)
{
    std::advance(it, N - 1);
    return it->value;
}

const auto alwaysZeroValue =
    [](Tokens::const_iterator) -> Instruction::ValueType { return 0; };

SemanticAnalyser::SemanticAnalyser()
    : instructions{
          InstructionInfo{{TokenType::Out, TokenType::ZeroWithBracketsA},
                          InstructionType::OutA,
                          alwaysZeroValue},
          InstructionInfo{{TokenType::Ld, TokenType::A},
                          InstructionType::LdA,
                          nthTokenValueGetter<2>},
          InstructionInfo{{TokenType::Ld, TokenType::B},
                          InstructionType::LdB,
                          nthTokenValueGetter<2>},
          InstructionInfo{
              {TokenType::Rlca}, InstructionType::Rlca, alwaysZeroValue},
          InstructionInfo{
              {TokenType::Rrca}, InstructionType::Rrca, alwaysZeroValue},
          InstructionInfo{{TokenType::Djnz, TokenType::LabelRef},
                          InstructionType::Djnz,
                          nthTokenValueGetter<2>},
          InstructionInfo{{TokenType::Label},
                          InstructionType::Label,
                          nthTokenValueGetter<1>}}
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
    Instructions currentInstructions{
        convertInstructionInfoToInstruction(begin, instruction)};
    const auto& nextInstructions = analyse(begin + instruction.size, end);
    std::move(nextInstructions.begin(), nextInstructions.end(),
              std::back_inserter(currentInstructions));
    return currentInstructions;
}

Instruction SemanticAnalyser::convertInstructionInfoToInstruction(
    Tokens::const_iterator begin, InstructionInfo instructionInfo)
{
    return {instructionInfo.instruction, instructionInfo.getValue(begin)};
}

SemanticAnalyser::InstructionInfo
SemanticAnalyser::findInstruction(Tokens::const_iterator begin,
                                  Tokens::const_iterator end)
{
    for (const auto& instruction : instructions)
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
    if (end - begin > 0 &&
        static_cast<decltype(instruction.size)>(end - begin) >=
            instruction.size)
    {
        for (const auto nextExpectedToken : instruction.expectedTokens)
        {
            if (nextExpectedToken != (begin++)->type)
            {
                return false;
            }
        }
        return true;
    }
    return false;
}
