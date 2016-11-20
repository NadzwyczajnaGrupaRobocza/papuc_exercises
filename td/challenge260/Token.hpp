#pragma once

#include <ostream>
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

inline std::ostream& operator<<(std::ostream & out, TokenType token)
{
  switch (token)
  {
    case TokenType::Ld:
      return out << "LD";
    case TokenType::Out:
      return out << "Out";
    case TokenType::A:
      return out << "A";
    case TokenType::ZeroWithBrackets:
      return out << "ZeroWithBrackets";
    case TokenType::Number8Bit:
      return out << "Number8Bit";
  }
  return out << "No known TokenType";
}
