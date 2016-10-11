#pragma once
#include <iosfwd>
namespace calc
{
class Token
{
public:
    Token();
    Token(char);
    Token(char, double);

    char typeId;
    double value;
};

std::ostream& operator<<(std::ostream&, const Token&);
bool operator==(const Token& lhs, const Token& rhs);
}
