#include "Token.hpp"
#include <ostream>

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

std::ostream& operator<<(std::ostream& out, const Token& t)
{
    if (t.typeId != '8')
    {
        return out << "TOK-s:" << t.typeId;
    }
    else
    {
        return out << "TOK-v:" << t.value;
    }
}

bool operator==(const Token& lhs, const Token& rhs)
{
    return lhs.typeId == rhs.typeId && lhs.value == rhs.value;
}
}
