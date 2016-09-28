#include "Token.hpp"

Token::Token(char aKind)
    : kind {aKind}, value {0.0}
{
}

Token::Token(char aKind, double aValue)
    : kind {aKind}, value{aValue}
{
}
