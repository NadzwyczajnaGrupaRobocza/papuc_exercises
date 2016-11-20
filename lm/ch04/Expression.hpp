#pragma once

#include <string>
namespace lm
{
class Expression
{
public:
    Expression(const std::string&);
    double getResult();

private:
    const std::string& input;
};
}
