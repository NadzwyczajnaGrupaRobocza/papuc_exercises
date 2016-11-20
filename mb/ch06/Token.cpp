#include "Token.hpp"
#include <cmath>

Token::Token(char aKind) : kind{aKind}, value{0.0}
{
}

Token::Token(char aKind, double aValue) : kind{aKind}, value{aValue}
{
}

bool operator==(const Token& left, const Token& right)
{
    constexpr double epsilon{0.00001};
    return (left.kind == right.kind) &&
           (std::fabs(left.value - right.value) < epsilon);
}
