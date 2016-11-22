#pragma once

#include <ostream>
#include <vector>

enum class TokenType
{
    Ld,
    A,
    B,
    Out,
    ZeroWithBrackets,
    Number8Bit,
    Rlca,
    Rrca,
    Djnz,
    Label,
    LabelRef
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

inline std::ostream& operator<<(std::ostream& out, TokenType token)
{
    switch (token)
    {
    case TokenType::Ld: return out << "LD";
    case TokenType::Out: return out << "Out";
    case TokenType::A: return out << "A";
    case TokenType::B: return out << "B";
    case TokenType::ZeroWithBrackets: return out << "ZeroWithBrackets";
    case TokenType::Number8Bit: return out << "Number8Bit";
    case TokenType::Rlca: return out << "Rlca";
    case TokenType::Rrca: return out << "Rrca";
    case TokenType::Djnz: return out << "Djnz";
    case TokenType::Label: return out << "Label";
    case TokenType::LabelRef: return out << "LabelRef";
    }
    return out << "No known TokenType";
}
