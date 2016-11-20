#include "Token.hpp"
#include <cmath>
#include <limits>
#include <ostream>

namespace calc
{
Token::Token() : typeId{0}, value{0}, id{""}
{
}

Token::Token(char typeIdInit) : typeId{typeIdInit}, value{0}, id{""}
{
}

Token::Token(char typeIdInit, double valueInit)
    : typeId{typeIdInit}, value{valueInit}, id{""}
{
}

Token::Token(char typeIdInit, const std::string& idInit)

    : typeId{typeIdInit}, value{0}, id{idInit}
{
}

std::ostream& operator<<(std::ostream& out, const Token& t)
{
    switch (t.typeId)
    {
    case '8': { return out << "TOK-val:" << t.value;
    }
    case 'S': { return out << "TOK-str:" << t.id;
    }
    default: { return out << "TOK-sym:" << t.typeId;
    }
    }
}

bool operator==(const Token& lhs, const Token& rhs)
{
    return lhs.typeId and rhs.typeId &&
           (std::fabs(lhs.value - rhs.value) <
            std::numeric_limits<double>::epsilon()) and
           lhs.id == rhs.id;
}
}
