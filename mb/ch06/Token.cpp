#include "Token.hpp"
#include <cmath>
#include <limits>

Token::Token(char aKind) : kind{aKind}, value{0.0}
{
}

Token::Token(char aKind, double aValue) : kind{aKind}, value{aValue}
{
}

bool operator==(const Token& left, const Token& right)
{
    return (left.kind == right.kind) &&
           (std::fabs(left.value - right.value) <
            std::numeric_limits<double>::epsilon());
}
