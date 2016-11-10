#pragma once

enum class IntructionType
{
  LdA,
  OutA
};

struct Instruction
{
  using ValueType = unsigned;
  IntructionType type;
  ValueType value;
};

bool operator==(const Instruction& lhs, const Instruction& rhs)
{
  return lhs.type == rhs.type && lhs.value == rhs.value;
}

using Instructions = std::vector<Instruction>;