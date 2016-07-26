#include "Token.hpp"

namespace calc
{
Token::Token()
    : typeId{0}, value{0}
{
}

Token::Token(char typeIdInit)
    : typeId{typeIdInit}, value{0}
{
}

Token::Token(char typeIdInit, double valueInit)
    : typeId{typeIdInit}, value{valueInit}
{
}

}
