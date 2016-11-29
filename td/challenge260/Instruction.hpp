#pragma once

#include <vector>

enum class InstructionType
{
    LdA,
    LdB,
    OutA,
    Rlca,
    Rrca,
    Djnz,
    Label
};

struct Instruction
{
    using ValueType = unsigned char;
    InstructionType type;
    ValueType value;
};

inline bool operator==(const Instruction& lhs, const Instruction& rhs)
{
    return lhs.type == rhs.type && lhs.value == rhs.value;
}

using Instructions = std::vector<Instruction>;
