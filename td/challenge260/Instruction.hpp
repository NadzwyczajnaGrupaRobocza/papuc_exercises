#pragma once

enum class IntructionType
{
  LdA,
  OutA
};

struct Instruction
{
  using ValueType = unsigned;
  InstructionType type,
  ValueType value;
};