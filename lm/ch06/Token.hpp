#pragma once
#include <iosfwd>
#include <string>
namespace calc
{
class Token
{
public:
    Token();
    Token(char);
    Token(char, double);
    Token(char, const std::string&);

    char typeId;
    double value;
    std::string id;
};

std::ostream& operator<<(std::ostream&, const Token&);
bool operator==(const Token& lhs, const Token& rhs);
}
