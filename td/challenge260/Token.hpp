#pragma once

#include <vector>

enum class TokenType
{
  Ld,
  A,
  Out,
  ZeroWithBrackets,
  Number8Bit
};

struct Token
{
  using ValueType = unsigned;
  TokenType type;
  ValueType value;
};

inline bool operator==(const Token& lhs, const Token& rhs)
{
  return lhs.type == rhs.type && lhs.value == rhs.value;
}

using Tokens = std::vector<Token>;