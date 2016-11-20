#pragma once

enum class InstructionType
{
  LdA,
  OutA
};

struct Instruction
{
  using ValueType = unsigned;
  InstructionType type;
  ValueType value;
};

bool operator==(const Instruction& lhs, const Instruction& rhs)
{
  return lhs.type == rhs.type && lhs.value == rhs.value;
}

using Instructions = std::vector<Instruction>;