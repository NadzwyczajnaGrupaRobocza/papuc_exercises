#pragma once

#include <iostream>
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

inline std::ostream& operator<<(std::ostream& out, InstructionType instruction)
{
    switch (instruction)
    {
    case InstructionType::Djnz: return out << "DJNZ";
    case InstructionType::Label: return out << "LABEL";
    case InstructionType::LdA: return out << "A";
    case InstructionType::LdB: return out << "B";
    case InstructionType::OutA: return out << "Out";
    case InstructionType::Rlca: return out << "Rlca";
    case InstructionType::Rrca: return out << "Rrca";
    }
    return out << "No known InstructionType";
}
